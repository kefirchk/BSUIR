#include "Header.h"                       //подключение библиотеки

void show(floor* tailFloor)               //функция просмотра информации о заселенных людях
{
	if (!tailFloor)                       //проверка на пустоту очереди
	{
		printf("%c[%d;%dm\nЭтажи пусты!%c[%dm\n", 27, 1, 31, 27, 0);
		return;
	}
	floor* pointerFloor = tailFloor;      //указатель на этажи 
	rooms* pointerRoom = tailFloor->room; //указатель на комнаты
	people* pointerHuman = NULL;          //указатель на людей
	puts("Выберите этаж:");
	printf("Непустые этажи:");
	while (pointerFloor)                  //вывод непустых этажей
	{
		printf(" %d", pointerFloor->numberOfFloor); //вывод очередного этажа
		pointerFloor = pointerFloor->next_floor;    //переход к следующему этажу
	}
	printf("\n");                         //новая строка
	pointerFloor = tailFloor;             //указатель на начало
	int floorNumber = input_int();        //вызво функции выбора этажа
	while (pointerFloor)                  //цикл по поиску требуемого этажа
	{
		if (pointerFloor && pointerFloor->numberOfFloor == floorNumber) //если этаж найден
		{
			int k = 0;                    //счетчик
			printf(" ");
			while (k++ < 69) printf("_"); //рисовка верхней границы таблицы
			printf("\n|Имя\t\t|Фамилия        |Факультет      |Группа    |Комната   |\n|"); //вывод "шапки"
			k = 66;
			while (k-- > 1)               //подрисовка верхней границы таблицы
			{
				if (k == 10 || k == 20 || k == 35 || k == 50) printf("|");
				printf("_");
			}
			pointerRoom = pointerFloor->room;     //установка указателя на начало комнат
			while (pointerRoom)                   //цикл по комнатам
			{
				pointerHuman = pointerRoom->human;//установка на первого человека
				while (pointerHuman)              //цикл по людям
				{
					printf("|\n|%-15s|%-15s|%-15s|%-10d|%-10d", pointerHuman->name, pointerHuman->surname,
						pointerHuman->faculty, pointerHuman->group, pointerRoom->numberOfRoom);
					pointerHuman = pointerHuman->next_person;       //переход к следующему человеку
					if (pointerHuman == pointerRoom->human) break;  //если стали на входной элемент
				}
				pointerRoom = pointerRoom->next_room;               //переход к следующей комнате
			}
			printf("|\n|");
			while (k++ < 65)                                        //рисовка нижней границы таблицы
			{
				if (k == 16 || k == 31 || k == 46 || k == 56) printf("|");
				printf("_");
			}
			puts("|");
			return;
		}
		pointerFloor = pointerFloor->next_floor;                    //переход к следующему этажу
	}
	if (!pointerFloor) 
		printf("%c[%d;%dm\nЭтаж пуст!%c[%dm\n", 27, 1, 31, 27, 0);
}