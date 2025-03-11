#include "Header.h"                                      //подлкючение библиотеки

void move(floor*& headFloor, floor*& tailFloor, int* ms) //функция переселения человека
{
	people* person = NULL;            //указатель на переселяемого человека
	rooms* pointerRoom_prev = NULL;   //указатель на предыдущую комнату по отношению к той, в которой сейчас проживает человек
	if (!headFloor || !tailFloor)     //очередь из этажей еще не создана
	{
		printf("%c[%dп%dm\nОбщежитие пусто!%c[%dm\n", 27, 1, 31, 27, 0);
		return;
	}
	printf("Введите номер этажа, на котором сейчас живет человек: ");
	int oldFloorNumber = input_int(); //вызов функции ввода этажа
	printf("Введите номер комнаты, в которой сейчас живет человек: ");
	int oldRoomNumber = input_int();  //вызов функции ввода комнаты
	input_person_info(person);        //вызов функции ввода информации о человеке

	floor* pointerFloor = tailFloor, *choosenFloor = tailFloor;  //указатель на этажи, указатель на выбранный этаж
	if (search_person(pointerFloor, choosenFloor, pointerRoom_prev, person, oldFloorNumber, oldRoomNumber)) //вызов функции поиска человека
	{
		printf("Введите номер этажа, куда требуется переселить человека: ");
		int newFloorNumber = input_int(); //вызов функции ввода номера нового этажа
		printf("Введите номер комнаты, куда требуется переселить человека ");
		int newRoomNumber = input_int();  //вызов функции ввода номера новой комнаты

		if (fun_add(headFloor, tailFloor, person, ms, newFloorNumber, newRoomNumber)) //вызов функции добавления человека в комнату
		{
			fun_del(tailFloor, headFloor, person, oldFloorNumber, oldRoomNumber);     //вызов функции удаления человека из старой комнаты
			printf("%c[%d;%dm\nЧеловек переселен!%c[%dm\n", 27, 1, 32, 27, 0);
		}
	}
}