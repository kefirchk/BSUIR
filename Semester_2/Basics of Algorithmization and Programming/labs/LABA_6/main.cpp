//Лаборраторная работа №6. "Динамические структуры данных.  Очередь, кольцо."

//8. Разработать программу, моделирующую общежитие, 
//организованную по принципу списка (двунаправленной очереди), 
//элемент которой – этаж общежития, который содержит следующую информацию:
//номер этажа, общее количество мест на этаже, количество свободных мест и 
//указатель на однонаправленную очередь, элемент которой - номер комнаты и 
//указатель на двунаправленное кольцо, содержащее информацию о проживающих в комнате людях.  
//Организовать следующие режимы работы программы: поиск свободного места в общежитии, 
//заселение, перемещение из комнаты в комнату, выселение. 

#include "Header.h"               //подключение библиотеки

int main()
{
	SetConsoleCP(1251);           //русификация консолио
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");
	floor *headFloor = NULL, *tailFloor = NULL;      //указатели на хвост и голову двунаправленной очереди этажей
	people* tailHuman = NULL, *headHuman = NULL;     //указатели на хвост и голову двунаправленной очереди людей, стоящих на очереди на заселение в общежтитие
	people* tailDeleted = NULL, *headDeleted = NULL; //указатели на хвост и голову соответственно списка выселенных людей
	people* person = NULL;                           //указатель на удаленного человека
	int *ms = input_basic_info(); //вызов функции ввода количества этажей, количества комнат на этаже, количества жильцов в одной комнате соответственно
	do
	{
		while (1)
		{
			instructions();       //вызов функции вывода инструкций работы программы
			switch (char c = _getch())
			{
			case '1': add_from_queue(headFloor, tailFloor, &tailHuman, &headHuman, ms); break;  //вызов функции заселения из очереди на общежитие
			case '2': menu_add(headFloor, tailFloor, ms); break; //вызов функции подменю для заселения человека в общежитие
			case '3': person = menu_del(headFloor, tailFloor);   //вызов функции подменю для выселения человека из общежития
				if(person)deleted_plus_queue(&headDeleted, &tailDeleted, person); break;
			case '4': check_free_places(tailFloor, ms); break;   //вызов функции проверки общежития на количество свободных мест
			case '5': move(headFloor, tailFloor, ms); break;     //вызов функции переселения человека из одной комнаты в другую
			case '6': set(&tailHuman, &headHuman); break;        //вызов функции, которая ставит человека на очередь на общежитие
			case '7': show(tailFloor); break;                    //вызов функции просмотра заселенных людей на этаже
			case '8': ms = input_basic_info(); break;            //вызов функции замены начальных данных
			case '9': output_deleted(tailDeleted); break;        //вызов функции вывода списка выселеных людей
			case '0': freeAll(tailFloor, tailHuman, tailDeleted);//выход из программы
				return 0;
			case 'd': freeAll(tailFloor, tailHuman, tailDeleted);  
				puts("\nОчистка завершена!"); break; //очистка всех динамических структур данных
			default: printf("%c[%d;%dm\nОшибка выбора операции! Повторите ввод%c[%dm\n", 27, 1, 31, 27, 0); continue;
			}
			break;
		}
		//if(headFloor)printf("\nГолова: %s %s", headFloor->room->human->name, headFloor->room->human->surname);
		//if(tailFloor)printf("\nХвост: %s %s\n", tailFloor->room->human->name, tailFloor->room->human->surname);
	} while (offer());
	freeAll(tailFloor, tailHuman, tailDeleted);                  //вызов фукнции очисти всех созданных списков
	return 0;
}