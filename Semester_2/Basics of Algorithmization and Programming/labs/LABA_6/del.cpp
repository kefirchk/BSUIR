#include "Header.h"                        //поключение библиотеки

people* menu_del(floor *&headFloor, floor *&tailFloor) //функция меню выселения человека из общежития
{
	people* person = NULL;                 //указатель на выселяемого человека 
	if (!tailFloor || !headFloor)          //проверка на пустоту очереди
	{
		printf("%c[%d;%dm\nЭтажи пусты!%c[%dm\n", 27, 1, 31, 27, 0);
		return NULL;
	}
	printf("\nВведите номер этажа для выселения: ");
	int floorNumber = input_int();         //вызов функции ввода этажа
	printf("Введите номер комнаты: ");
	int roomNumber = input_int();          //вызов функции ввода комнаты
	input_person_info(person);             //вызов функции ввода информации о человеке
	if (fun_del(tailFloor, headFloor, person, floorNumber, roomNumber))  //вызов функции удаления человека из общежития
	{
		printf("%c[%d;%dm\nЧеловек выселен!%c[%dm\n", 27, 1, 32, 27, 0);
		return person;                     //вернуть удаляемого человека
	}
	else return NULL;
}

int fun_del(floor* &tailFloor, floor* &headFloor, people* person, int floorNumber, int roomNumber)    //функция удаления человека из общежития
{
	floor *pointerFloor = tailFloor, *choosenFloor = tailFloor; //указатель для прохода по этажам и на выбранный этаж
	rooms* pointerRoom = NULL, *pointerRoom_prev = NULL;        //указатели для прохода по комнатам и на предыдущую комнату
	people* pointerHuman = NULL;                                //указатель для прохода по людям
	if (search_person(pointerFloor, choosenFloor, pointerRoom_prev, person, floorNumber, roomNumber)) //вызов функции поиска человека
	{  
		pointerRoom = choosenFloor->room;                       //установка начальных значений указателей
		pointerHuman = choosenFloor->room->human;
	    if (tailFloor == headFloor && headFloor == choosenFloor) tailFloor = headFloor = NULL; //если единственный этаж
		if (pointerHuman && pointerHuman->next_person == pointerHuman && pointerHuman->previous_person == pointerHuman)
		{ //в кольце только один элемент
			if (pointerFloor->room == choosenFloor->room) pointerFloor->room = pointerRoom->next_room; //если удаляем на хвосте
			else if (choosenFloor->room == headFloor->room) headFloor->room = pointerRoom_prev;        //если удаляем на голове
			else pointerRoom_prev->next_room = pointerRoom->next_room;                                 //обход элемента
			free(pointerHuman); pointerHuman = NULL;            //освобождение памяти и обнуление указателей
			free(pointerRoom); pointerRoom = NULL;              //освобождение памяти и обнуление указателей
			pointerFloor->freePlaces += 1;                      //увеличение кол-ва свободных мест
			if (pointerRoom && (choosenFloor->next_floor || choosenFloor->previous_floor)) //если комната не была единственной
			{
				if(pointerFloor->previous_floor)pointerFloor->previous_floor->next_floor = pointerFloor->next_floor; //обход элемента
				if(pointerFloor->next_floor)pointerFloor->next_floor->previous_floor = pointerFloor->previous_floor; //обход элемента
				free(pointerFloor);                             //освобождение памяти от комнаты
				pointerFloor = NULL;                            //обнуление указателя
			}
			return 1;                                           //1 - значит, что удалили человека
		}
		if (pointerFloor->room == choosenFloor->room) pointerFloor->room = pointerFloor->room->next_room; //изменение точки входа (для комнат)
		if (pointerHuman == pointerFloor->room->human) pointerRoom->human = pointerHuman->next_person;    //изменение точки входа (в кольце)
		pointerHuman->previous_person->next_person = pointerHuman->next_person;                           //обход элемента
		pointerHuman->next_person->previous_person = pointerHuman->previous_person;                       //обход элемента
		free(pointerHuman);                                                                               //освобождение памяти
		if (!pointerRoom->human)                                    //была удалена точка входа
		{
			pointerRoom_prev->next_room = pointerRoom->next_room;   //изменение точки входа
			free(pointerRoom);                                      //освобождение памяти
			pointerRoom = NULL;                                     //зануление указателя
		}
		if (!pointerFloor->room)                                    //удалена точка входа (для комнат)
		{
			if (tailFloor == pointerFloor) tailFloor = pointerFloor->next_floor;     //если мы находимся на хвосте
			if (pointerFloor == headFloor) headFloor = headFloor->previous_floor;    //если мы находимся на голове 
			pointerFloor->previous_floor->next_floor = pointerFloor->next_floor;     //обход элемента
			pointerFloor->next_floor->previous_floor = pointerFloor->previous_floor;
			free(pointerFloor);                                     //освобождение памяти
			pointerFloor = NULL;                                    //зануление указателя
		}
		pointerFloor->freePlaces += 1;                              //увеличение числа свободных мест
		return 1;                                                   //1 - человек удален 
	}
	else return 0;
}