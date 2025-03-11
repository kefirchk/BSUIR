/*
* 
*		 << SPY-EYE >>
* Developed by Alexei Klimovich
*		   22.10.2023
* 
*/

#include "Libs.h"
#include "SpyEye.h"

// ====================================================================
// Объявление глобальных переменных
// --------------------------------------------------------------------
static SpyEye spyEye;			   // объект шпионской съемки
static atomic<bool> toExit(false); // флажок на выход из программы
static bool isVisiable = true;     // скрыта ли консоль
static HHOOK hook;				   // хук для клавиатуры
//static thread photoThread;		   // поток для фото
static thread videoThread;		   // поток для видео
// ====================================================================


// ====================================================================
// Обработчик для хука клавиатуры
// --------------------------------------------------------------------
LRESULT CALLBACK keyboardHookHandler(int code, WPARAM wParam, LPARAM lParam)
{
	if (toExit)				  // если установлен признак завершения программы
		PostQuitMessage(0);   // отправить сигнал завершения обработчика клавиатуры
	if (code == HC_ACTION)    // если была нажата какая-либо клавиша на клавиатуре
	{
		PKBDLLHOOKSTRUCT pKey = (PKBDLLHOOKSTRUCT)lParam;  // получаем нажатую клавишу
		if (wParam == WM_KEYDOWN && (pKey->vkCode == 50 || pKey->vkCode == 49)) // нажали на '1' или '2'
		{
			if (spyEye.isActive)            // если съемка велась
			{
				spyEye.getConsole().show(); // показать консоль
				isVisiable = true;		    // установить признак видимой консоли
				spyEye.isActive = false;    // установь признак окончания съемки
				videoThread.detach();
			}
			else                            // если съемка не велась
			{
				spyEye.getConsole().hide();	// спрятать консоль
				isVisiable = false;		    // установить признак невидимой консоли
				spyEye.isActive = true;     // установить признак активной съемки
				if (pKey->vkCode == 49)     // если была нажата '1' (сделать фото)
				{
					spyEye.startSpyPhoto();
					//thread newThread(&SpyEye::startSpyPhoto, &spyEye);  // создаем поток для фото
					//photoThread.swap(newThread);						// отдаем поток для фото глобальному потоку для фото
				}
				if (pKey->vkCode == 50)     // если была нажата '2' (запись видео)
				{
					thread newThread(&SpyEye::startSpyVideo, &spyEye);  // создаем поток для видео
					videoThread.swap(newThread);						// отдаем поток для видео глобальному потоку для видео
				}
			}
		}
		if (wParam == WM_KEYDOWN && pKey->vkCode == 51)     // нажали на '3' (скрыть/показать консоль)
		{
			if (!isVisiable) spyEye.getConsole().show();    // если консоль невидима, то показать консоль
			else spyEye.getConsole().hide();			    // если консоль видима, то спрятать консоль
			isVisiable = isVisiable == true ? false : true; // изменить признак видимости консоли на противоположный
		}
	}
	return CallNextHookEx(NULL, code, wParam, lParam);      // передать управление следующему хуку в цепочке
}

// ====================================================================
// Обработчик для потока menuThread
// --------------------------------------------------------------------
void menuHandler()
{
	string command;            // команда для выполнения
	while (!toExit)            // пока не установлен признак выхода из программы
	{
		cout << "SPY-EYE > ";  // вывести приглашение для ввода очередной команды
		getline(cin, command); // получить очередную команду
		if (command == "photo" || command == "video")  // если очередная команда "photo" или "video"
			isVisiable = false;                        // устанавливаем признак невидимости консоли
		toExit = spyEye.executeCommand(command);       // выполнить команду
	}
}

// ====================================================================
// Главная функция
// --------------------------------------------------------------------
int main() 
{
	spyEye.help();                  // вывод доступных команд
	system("pause");                // пауза
	system("cls");                  // очистка консоли
	spyEye.printLogo();             // вывод лого программы
	thread menuThread(menuHandler); // создать поток для меню программы

	MSG message;                    // очередное сообщение от системы
	if (!(hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHookHandler, NULL, 0)))  // установка хука для клавиатуры
	{
		cout << "Error: cannot set hook" << endl;  // вывод сообщения об ошибке
		exit(EXIT_FAILURE);                        // аварийный выход из программы
	}

	while (!toExit)                                // пока не установлен признак выхода из программы
		GetMessage(&message, NULL, 0, 0);          // получить очередное сообщение от системы
	spyEye.isActive = false;                       // установить признак окончания скрытой съемки

	UnhookWindowsHookEx(hook);     // отвязать обработчик
	if(menuThread.joinable())
		menuThread.join();         // присоединяем поток menuThread к главному потоку
	//if (photoThread.joinable())
	//	photoThread.join();		   // присоединяем поток photoThread к главному потоку
	if(videoThread.joinable())
		videoThread.join();		   // присоединяем поток videoThread к главному потоку
	system("pause");			   // пауза
	return 0;
}