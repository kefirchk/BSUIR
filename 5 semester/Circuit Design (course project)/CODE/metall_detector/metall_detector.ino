/*
  Название: Микропроцессорное устройство для обнаружения металлических объектов
  Разработчик: студент группы 150501 Климович А.Н.
  Дата: 01.12.2023
  Все права защищены (c) 2023 Алексей Климович
*/

#include <LiquidCrystal_I2C.h>     // Подключаем библиотеку для работы с LCD дисплеем по шине I2C
#include "iarduino_RTC.h"          // Подключаем библиотеку для работы с модулем RTC

// =======================================================================
// ---------------ПОДКЛЮЧЕНИЕ ЭЛЕМЕНТОВ К МИКРОКОНТРОЛЛЕРУ----------------
// =======================================================================
#define RED_LED 8                  // Номер контакта красного светодиода (D8)
#define BLUE_LED 7                 // Номер контакта синего светодиода (D7)
#define YELLOW_LED 6               // Номер контакта желтого светодиода (D6)
#define CALIBRATE_BUTTON_GND 2     // Номер контакта кнопки калибровки для выходящего сигнала (D2)
#define CALIBRATE_BUTTON 3         // Номер контакта кнопки калибровки для входящего сигнала (D3)
#define REGULATOR 3                // Номер контакта потенциометра для изменения чувствительности устройства и настройки RTC (А3)
#define BLUE_BUTTON 9              // Номер контакта синей кнопки (D9)
#define WHITE_BUTTON 10            // Номер контакта белой кнопки (D10)
#define PIEZO_SOUND 4              // Номер контакта пьезоизлучателя (D4)  
#define PIN_RST 11                 // Номер контакта сброса модуля RTC (D11)
#define PIN_DAT 12                 // Номер контакта ввода/вывода последовательных данных RTC (D12)
#define PIN_CLK 13                 // Номер контакта входа тактовой частоты последовательных данных RTC (D13)

// =======================================================================
// ------------------------------КОНСТАНТЫ--------------------------------
// =======================================================================
#define SOUND_DELAY 20             // Задержка между воспроизведениями
#define SOUND_DURATION 30          // Продолжительность одного воспроизведения
#define SOUND_FREQUENCY 3000       // Частота воспроизводимого звука
#define STATIC_MODE 1              // Статический режим поиска
#define DYNAMIC_MODE 0             // Динамический режим поиска
#define DEFAULT_BAUD 9600          // Скорость передачи данных по умолчанию
#define DYNAMIC_TIMER_INTERVAL 300 // Время срабатывания таймера динамического режима сброса частоты
#define LONG_PRESS_DURATION 1000   // Время долгого ужержания кнопки калибровки
#define FREQUENCY_RST_CONST 0.5    // Коэффициент в формуле плавного сброса частоты в динамическом режиме

// =======================================================================
// -------------------МАКРОСЫ УСТАНОВКИ/ОЧИСТКИ БИТОВ---------------------
// =======================================================================
#define SET(x,y) (x |=(1<<y))     
#define CLR(x,y) (x &= (~(1<<y)))
#define CHK(x,y) (x & (1<<y))
#define TOG(x,y) (x^=(1<<y))

// =======================================================================
// -----------------------ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ---------------------------
// =======================================================================
float sensitivity = 1000.0;               // Чувствительность устройства
unsigned long t0 = 0;                     // Время последнего срабатывания Timer 1
unsigned long dynamic_timer;              // Таймер динамического режима для плавного сброса частоты
int t = 0;                                // Время между прерываниями
unsigned char tflag = 0;                  // Флаг готовности к изменению
int start_frequency = 0;                  // Начальная частота
float f = 0;                              // Значение измерения
unsigned int FTW = 0;                     // Частота генератора писка
unsigned int PCW = 0;                     // Фаза генератора писка
unsigned long count_timer = 0;            // Счетный таймер
unsigned int currentMenu = BLUE_BUTTON;   // Текущее меню (по умолчанию - меню поиска металлических объектов)
unsigned int mode = 1;                    // Режим работы устройства (статический - 1, динамический - 0)
unsigned int cursorRow = 1;               // Положение курсора в меню RTC
unsigned long pressStartTime = 0;         // Время начала удержания красной кнопки для смены режимов
LiquidCrystal_I2C lcd(0x27, 20, 4);       // Создание объекта дисплея LCD
iarduino_RTC rtc(RTC_DS1302,              // Создания объекта модуля RTC DS1302, и указываем пины(RST, CLK, DAT)
                 PIN_RST, 
                 PIN_CLK, 
                 PIN_DAT); 

// =======================================================================

// Функция предустановки режимов работы контактов, инициализации переменных и дисплея 
void setup()
{
  rtc.begin();          // Инициализация работы модуля RTC
  lcd.init();           // Инициируем работу с LCD дисплеем
  lcd.backlight();      // Включаем подсветку LCD дисплея
  lcd.clear();          // Очищаем дисплей
  setupPins();          // Настройка режимов работы контактов микроконтроллера
  showMainMenu();       // Отображение главного меню

  // Установка счетчика 1 на счет на контакте D5
  TCCR1A = 0;           // Устанавливаем значение в регистре TCCR1A в 0
  TCCR1B = 0x07;        // Установка внешнего тактового источника на выводе T1. Тактирование происходит по фронту
  SET(TIMSK1, OCF1A);   // Включить прерывание Timer1 overflow

  // OCF1A: Output Compare Flag 1A - Флаг 1A совпадения выхода
  // Бит OCF1A устанавливается при совпадении состояния таймера/счетчика1 и содержимого регистра OCR1A (Output Compare Register 1A).
  // Бит OCF1A аппаратно очищается при обработке соответствующего вектора прерывания.
 }

// Главная бесконечная функция программы
void loop()
{
  int pressedButton = getPressedButton();   // Получение нажатой кнопки
  if(pressedButton > 0)                     // Если была нажата кнопка
  {
    if((pressedButton == WHITE_BUTTON) && 
       ((currentMenu == BLUE_BUTTON) || (currentMenu == WHITE_BUTTON && cursorRow == 3)))
    {
      switchMenu();                         // Смена меню
    }
    else if(currentMenu == WHITE_BUTTON)
      timeMenu(pressedButton);              // Выполнить функцию в меню RTC
  }
  if (digitalRead(CALIBRATE_BUTTON) == LOW) // Нажата красная кнопка калибровки
  {
    if (pressStartTime == 0)
      pressStartTime = millis();            // Начинаем отсчет времени удержания кнопки
    else 
    {
      if (millis() - pressStartTime > LONG_PRESS_DURATION) // Длинное удержание кнопки
      {
        mode = mode == STATIC_MODE ? DYNAMIC_MODE : STATIC_MODE; // Смена режимов работы устройства
        pressStartTime = 0;       // Сбрасываем время удержания кнопки, если кнопка долго нажата
      }
    }
  } 
  else
    pressStartTime = 0;           // Сбрасываем время удержания кнопки, если кнопка не нажата

  if (tflag)                      // Установлен признак готовности к изменениями
  {
    if (mode == STATIC_MODE)    // Выбран статический режим 
      staticMode();
    if (mode == DYNAMIC_MODE)   // Выбран динамический режим 
      dynamicMode();
    f = f * 0.85 + absf(t - start_frequency) * 0.15;  // Фильтруем сигнал 
    sensitivity = map(analogRead(REGULATOR), 0, 1023, 10, 2000);  // Внешнее изменение чувствительности
    if(currentMenu == BLUE_BUTTON)                    // Если выбрано главное меню
    {
      printSensitivity();    // Вывод чувствительности
      printFrequency();      // Вывод частоты
      printMetalScale();     // Вывод шкалы приближения к металлу
    }
    float clf = f * sensitivity;  // Конвертация изменения частоты в звук
    if (clf > 10000)
      clf = 10000;
    FTW = clf;
    tflag = 0;                    // Сброс признака готовности к изменениям
  }

  if (millis() > count_timer)     // Если сработал счетный таймер
  {
    count_timer += 10;
    PCW += FTW;
    if (PCW & 0x8000)             // Если фаза достигнула макс. значения
    {
      PCW &= 0x7fff;
      if(currentMenu == BLUE_BUTTON)    // Если выбрано главное меню
      {
        tone(PIEZO_SOUND, SOUND_FREQUENCY, SOUND_DURATION); // Воспроизвести звук
        digitalWrite(BLUE_LED, HIGH);   // Включить светодиод
        delay(SOUND_DELAY);             // Задержка между воспроизведением и выключением для плавности
      }
    }
    noTone(PIEZO_SOUND);                // Выключить пьезоизлучатель
    digitalWrite(BLUE_LED, LOW);        // Выключаем светодиод
  }
}

// Обработчик прерывания от Timer 1
ISR(TIMER1_COMPA_vect)
{
  OCR1A += 1000;      // Срабатывает каждые 1000 импульсов с генератора, регистр сравнения A выхода таймера/счетчика1 - OCR1AH и OCR1AL - (Timer/Counter1 Output Compare Register)
  t = micros() - t0;  // Запоминаем время между прерываниями
  t0 += t;            // Изменяем время последнего срабатывания Timer 1
  tflag = 1;          // Устанока признака готовности к изменениям
}

// Функция устанавки режима работы указанных контактов
void setupPins()
{
  // Установка режима работы контакта для пьезоизлучателя
  pinMode(PIEZO_SOUND, OUTPUT);
  
  // Установка режима работы контакта для кнопки калибровки
  pinMode(CALIBRATE_BUTTON, INPUT_PULLUP);
  pinMode(CALIBRATE_BUTTON_GND, OUTPUT);
  digitalWrite(CALIBRATE_BUTTON_GND, LOW);

  // Установка режима работы контакта для красного светодиода
  pinMode(RED_LED, OUTPUT);
  for(int i = 0; i < 3; ++i)
  {
     digitalWrite(RED_LED, HIGH);   // зажигаем светодиод
     delay(500);                    // ждем секунду
     digitalWrite(RED_LED, LOW);    // выключаем светодиод
     delay(500);                    // ждем секунду
  }
  digitalWrite(RED_LED, HIGH); // включаем светодиод

  // Установка режима работы контакта для синего светодиода
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(BLUE_LED, HIGH); // выключаем светодиод

  // Установка режима работы контакта для желтого светодиода
  pinMode(YELLOW_LED, OUTPUT);
  digitalWrite(YELLOW_LED, HIGH); // выключаем светодиод
}

// Функция модуля для типа float
float absf(float f)
{
  return f < 0.0 ? -f : f;
}

// Функция статического режима
void staticMode()
{
  digitalWrite(YELLOW_LED, HIGH);              // Включить светодиод
  if (digitalRead(CALIBRATE_BUTTON) == LOW)    // Нажата кнопка сброса частоты
    start_frequency = t;                       // Запомнить текущую частоту
}

// Функция динамического режима
void dynamicMode()
{
  digitalWrite(YELLOW_LED, LOW);  // Выключаем светодиод
  if (millis() - dynamic_timer > DYNAMIC_TIMER_INTERVAL)
  {
    // Запоминаем срабатывание таймера
    dynamic_timer = millis();

    // Плавно сбрасываем частоту
    start_frequency = start_frequency * FREQUENCY_RST_CONST + (1 - FREQUENCY_RST_CONST) * t; 
  }
}

// Функция смены меню
void switchMenu()
{
  if(currentMenu == WHITE_BUTTON) currentMenu = BLUE_BUTTON;
  else currentMenu = WHITE_BUTTON;
  switch(currentMenu)
  {
    case BLUE_BUTTON:
      showMainMenu();  // Отображение главного меню
      break;
    case WHITE_BUTTON: 
      showTimeMenu();  // Отображение меню времени
      break;
  }
}

// Функция показа главного меню для поиска металлических объектов
void showMainMenu()
{
  lcd.clear();                        // Очистка экрана
  lcd.setCursor(0, 0);                // Установка курсора в позицию (0, 0)
  lcd.print("---- Main Menu -----");  // Вывод строки
  lcd.setCursor(0, 1);                // Установка курсора в позицию (0, 1)
  lcd.print("                    ");  // Вывод строки
  lcd.setCursor(0, 2);                // Установка курсора в позицию (0, 2)
  lcd.print("Frequency: ");           // Вывод строки пояснения
  printFrequency();                   // Вывод частоты
  lcd.setCursor(0, 3);                // Установка курсора в позицию (0, 3)
  lcd.print("Sensitivity: ");         // Вывод строки пояснения
  printSensitivity();                 // Вывод чувствительности
}

// Функция вывода частоты
void printFrequency()
{
  lcd.setCursor(11, 2);               // Установка курсора в позицию (11, 2)
  lcd.print("         ");             // Очистка строки
  lcd.setCursor(11, 2);               // Установка курсора в позицию (11, 2)
  lcd.print(f);                       // Вывод частоты
}

// Функция вывода чувствительности
void printSensitivity()
{
  lcd.setCursor(13, 3);               // Установка курсора в позицию (13, 3)
  lcd.print("       ");               // Очистка строки
  lcd.setCursor(13, 3);               // Установка курсора в позицию (13, 3)
  lcd.print(sensitivity);             // Вывод чувствительности
}

// Функция вывода шкалы приближения металлических объектов
void printMetalScale()
{
  lcd.setCursor(0, 1);                // Установка курсора в позицию (0, 1)
  lcd.print("                    ");  // Очистка строки
  lcd.setCursor(0, 1);                // Установка курсора в позицию (0, 1)
  int squares = (int)f;               // Подсчет количества вывода прямоугольников на шкалу
  if(f > 20)
    squares = 20;                     // Корректировка вычисленного значения
  for(int i = 0; i < squares; ++i)
    lcd.print(char(255));             // Вывод очередного прямоугольника
}

// Функция вывода меню RTC модуля
void showTimeMenu()
{
  lcd.clear();                        // Очистка экрана
  lcd.setCursor(0, 0);                // Установка курсора в позицию (0, 0)
  lcd.print("---- Time Menu -----");  // Вывод строки
  
  lcd.setCursor(0, 1);                // Установка курсора в позицию (0, 1)
  lcd.print("> Time: ");              // Вывод строки
  lcd.print(rtc.gettime("H:i, D"));   // Вывод времени
  
  lcd.setCursor(0, 2);                // Установка курсора в позицию (0, 2)
  lcd.print("  Date: ");              // Вывод строки
  lcd.print(rtc.gettime("d.m.y"));    // Вывод даты
  
  lcd.setCursor(0, 3);                // Установка курсора в позицию (0, 3)
  lcd.print("  ------ Back ------");  // Вывод строки

  cursorRow = 1;                      // Установка начального значения курсора
}

// Функция меню RTC
void timeMenu(int pressedButton)
{
  delay(200);                         // Задержка, чтобы уменьшить дребезг нажатия кнопок
  if(pressedButton == BLUE_BUTTON)    // Нажата кнопка движения по строкам меню
  {
    lcd.setCursor(0, cursorRow);      // Установка курсора в позицию (0, cursorRow)
    lcd.print("  ");                  // Очистка курсора '>'
    cursorRow += cursorRow == 3 ? -(cursorRow - 1) : 1;  // Вычисление новой позиции курсора
    lcd.setCursor(0, cursorRow);      // Установка курсора в позицию (0, cursorRow)
    lcd.print("> ");                  // Вывод курсора
  }
  else if(pressedButton == WHITE_BUTTON)  // Нажата кнопка выбора
  {
    if(cursorRow == 1)       // Изменение времени
    {
      setHours();            // Изменение часов
      setMinutes();          // Изменение минут
      setWeekDay();          // Изменение дня недели
      printTime();           // Печать времени
    }
    else if(cursorRow == 2)  // Изменение даты
    {
      setMonthDay();         // Изменение дня месяца
      setMonth();            // Изменение месяца
      setYear();             // Изменение года
      printDate();           // Печать даты
    }    
  }
}

// Вывод времени
void printTime()
{
  lcd.setCursor(8, 1);              // Установка курсора в позицию (8, 1)
  lcd.print("              ");      // Очистка строки
  lcd.setCursor(8, 1);              // Установка курсора в позицию (8, 1)
  lcd.print(rtc.gettime("H:i, D")); // Получение времени
}

// Вывод даты
void printDate()
{
  lcd.setCursor(8, 2);              // Установка курсора в позицию (8, 2)
  lcd.print("              ");      // Очистка строки
  lcd.setCursor(8, 2);              // Установка курсора в позицию (8, 2)
  lcd.print(rtc.gettime("d.m.y"));  // Получение даты
}

// Установка часов
void setHours()
{
  int pressedButton = 0;            // Нажатая кнопка
  do
  {
    delay(10);                      // Задержка для плавности изменения
    int hours = map(analogRead(REGULATOR), 0, 1023, 0, 24);
    if(hours == 24)
      hours = 0;
    rtc.settime(rtc.gettime("s"),  // Секунды
                rtc.gettime("i"),  // Минуты
                hours,             // Часы
                rtc.gettime("d"),  // День месяца
                rtc.gettime("m"),  // Месяц
                rtc.gettime("y"),  // Год
                rtc.gettime("D")); // День недели
    printTime();                   // Вывод времени 
    pressedButton = getPressedButton();   // Получения нажатой кнопки
  } while(pressedButton != WHITE_BUTTON); // Пока не подтвердили изменения
}

// Установка минут
void setMinutes()
{
  int pressedButton = 0;           // Нажатая кнопка
  do
  {
    delay(10);                     // Задержка для плавности изменения
    int minutes = map(analogRead(REGULATOR), 0, 1023, 0, 60);
    if(minutes == 60)              // Корректировка выбранного значения
      minutes = 0;
    rtc.settime(rtc.gettime("s"),  // Секунды
                minutes,           // Минуты
                rtc.gettime("H"),  // Часы
                rtc.gettime("d"),  // День месяца
                rtc.gettime("m"),  // Месяц
                rtc.gettime("y"),  // Год
                rtc.gettime("D")); // День недели
    printTime();                   // Вывод времени
    pressedButton = getPressedButton();   // Получение нажатой кнопки
  } while(pressedButton != WHITE_BUTTON); // Пока не подтвердили изменения
}

// Установка дня месяца
void setMonthDay()
{
  int pressedButton = 0;           // Нажатая кнопка
  do
  {
    delay(10);                     // Задержка для плавности изменения
    int monthDay = map(analogRead(REGULATOR), 0, 1023, 1, 32);
    if(monthDay == 32)             // Корректировка выбранного значения
      monthDay = 1;
    rtc.settime(rtc.gettime("s"),  // Секунды
                rtc.gettime("i"),  // Минуты
                rtc.gettime("H"),  // Часы
                monthDay,          // День месяца
                rtc.gettime("m"),  // Месяц
                rtc.gettime("y"),  // Год
                rtc.gettime("D")); // День недели
    printDate();                   // Вывод даты
    pressedButton = getPressedButton();   // Получение нажатой кнопки
  } while(pressedButton != WHITE_BUTTON); // Пока не подтвердили изменения
}

// Установка месяца
void setMonth()
{
  int pressedButton = 0;           // Нажатая кнопка
  do
  {
    delay(10);                     // Задержка для плавности изменения
    int month = map(analogRead(REGULATOR), 0, 1023, 1, 13);
    if(month == 13)                // Корректировка выбранного значения
      month = 1;
    rtc.settime(rtc.gettime("s"),  // Секунды
                rtc.gettime("i"),  // Минуты
                rtc.gettime("H"),  // Часы
                rtc.gettime("d"),  // День месяца
                month,             // Месяц
                rtc.gettime("y"),  // Год
                rtc.gettime("D")); // День недели
    printDate();                   // Вывод даты
    pressedButton = getPressedButton();   // Получение нажатой кнопки
  } while(pressedButton != WHITE_BUTTON); // Пока не подтвердили изменения
}

// Установка года
void setYear()
{
  int pressedButton = 0;           // Нажатая кнопка
  do
  {
    delay(10);                     // Задержка для плавности изменения
    int year = map(analogRead(REGULATOR), 0, 1023, 0, 100);
    if(year == 100)                // Корректировка выбранного значения
      year = 99;
    rtc.settime(rtc.gettime("s"),  // Секунды
                rtc.gettime("i"),  // Минуты
                rtc.gettime("H"),  // Часы
                rtc.gettime("d"),  // День месяца
                rtc.gettime("m"),  // Месяц
                year,              // Год
                rtc.gettime("D")); // День недели
    printDate();                   // Вывод даты
    pressedButton = getPressedButton();   // Получение нажатой кнопки
  } while(pressedButton != WHITE_BUTTON); // Пока не подтвердили изменения
}

// Установка дня недели
void setWeekDay()
{
  int pressedButton = 0;           // Нажатая кнопка
  do
  {
    delay(10);                     // Задержка для плавности изменения
    int weekDay = map(analogRead(REGULATOR), 0, 1023, 0, 7);
    if(weekDay == 7)               // Корректировка выбранного значения
      weekDay = 6;
    rtc.settime(rtc.gettime("s"),  // Секунды
                rtc.gettime("i"),  // Минуты
                rtc.gettime("H"),  // Часы
                rtc.gettime("d"),  // День месяца
                rtc.gettime("m"),  // Месяц
                rtc.gettime("y"),  // Год
                weekDay);          // День недели
    printTime();                   // Вывод времени
    pressedButton = getPressedButton();    // Получение нажатой кнопки
  } while(pressedButton != WHITE_BUTTON);  // Пока не подтвердили изменения
}

// Функция получения нажатой кнопки
int getPressedButton()
{
  int pressedButton = 0;                      // Нажатая кнопка
  pressedButton = digitalRead(BLUE_BUTTON);   // Статус нажатия синей кнопки
  if(pressedButton > 0)
    return BLUE_BUTTON;
  pressedButton = digitalRead(WHITE_BUTTON);  // Статус нажатия белой кнопки
  if(pressedButton > 0)
    return WHITE_BUTTON;
  return 0;
}
