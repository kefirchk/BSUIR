#include "Header.h"                        //подключение библиотеки

void add_from_queue(floor*& headFloor, floor*& tailFloor, people** tailHuman, people** headHuman, int* ms) //функция добавления человека из очереди на заселение в общежитие
{
	if (!*tailHuman && !*headHuman)        //если очередь на заселение пуста
	{
		printf("%c[%d;%dm\nОчередь на заселение пуста!%c[%dm\n", 27, 1, 31, 27, 0);
		return;
	}
	int floorNumber, roomNumber, flag = 1; //признак, что человека удалось заселить и можно удалять его из очереди на заселение
	do
	{
		puts("\nВведите номер этажа для заселения:");
		floorNumber = input_int();         //вызов функции ввода номера этажа, на который требуется заселить человека
		puts("Введите номер комнаты для заселения:(<100)");
		roomNumber = input_int();          //вызов функции ввода номера комнаты, в которую требуется заселить человека
		if (floorNumber < 1 || floorNumber > ms[0] || roomNumber < 1 || roomNumber > ms[1]) 
			printf("%c[%d;%dm\nОшибка!%c[%dm\n", 27, 1, 31, 27, 0);
		else break;
	} while (1);
	people* person = *headHuman;           //указатель на добавляемого человека
	if (fun_add(headFloor, tailFloor, person, ms, floorNumber, roomNumber)) //если 1, человека удалось заселить, можно удалять его из очереди на заселение
	{
		printf("%c[%d;%dm\nЧеловек заселен!%c[%dm\n", 27, 1, 32, 27, 0);
		if (*headHuman == *tailHuman) *headHuman = *tailHuman = NULL;       //в очереди был один единственный элемент
		else *headHuman = (*headHuman)->previous_person;                    //корректировка головы
		free(person);                                                       //освобождение памяти
	}
}