#include "Header.h"                 //подключение библиотеки
//функция поиска человека в общежитии
int search_person(floor* &pointerFloor, floor* &choosenFloor, rooms*& pointerRoom_prev, people* person, int floorNumber, int roomNumber)
{
	rooms* pointerRoom = NULL;      //указатель по комнатам
	people* pointerHuman = NULL;    //указатель по людям
	while (pointerFloor && pointerFloor->numberOfFloor != floorNumber)  //цикл по поиску нужного этажа
		pointerFloor = pointerFloor->next_floor;
	if (pointerFloor)               //этаж найден
	{
		pointerRoom = pointerRoom_prev = pointerFloor->room;            //начальное положение указателя на комнаты
		while (pointerRoom && pointerRoom->numberOfRoom != roomNumber)  //цикл по поиску нужной комнаты
		{
			pointerRoom_prev = pointerRoom;                             //установка указателя на предыдущую комнату
			pointerRoom = pointerRoom->next_room;                       //переход к следующей комнате
		}
		if (pointerRoom)            //комната найдена
		{
			pointerHuman = pointerRoom->human;  //начальное положение указателя по людям
			while (pointerHuman)                //цикл по поиску человека
			{
				if (!strcmp(pointerHuman->name, person->name) && !strcmp(pointerHuman->surname, person->surname)
					&& !strcmp(pointerHuman->faculty, person->faculty) && pointerHuman->group == person->group) break;
				pointerHuman = pointerHuman->next_person;         //переход к следующему человеку 
				if (pointerHuman == pointerRoom->human) return 0; //если вернулись на точку входа
			}
		}
		else {
			printf("%c[%d;%dmКомната не найдена!%c[%dm\n", 27, 1, 31, 27, 0);
			return 0; }
	}
	else {
		printf("%c[%d;%dmЭтаж не найден!%c[%dm\n", 27, 1, 31, 27, 0);
		return 0; }
	choosenFloor->room = pointerRoom;
	choosenFloor->room->human = pointerHuman;
	return 1;
}