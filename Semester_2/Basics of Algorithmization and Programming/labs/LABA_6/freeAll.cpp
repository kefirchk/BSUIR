#include "Header.h"                          //подключение библиотеки

void freeAll(floor* &tailFloor, people* &tailHuman, people* &tailDeleted) //функция освобождения памяти от всех видов списков
{
	if (!tailFloor) return;             //если общежитие пусто и на него не выделялась память
	floor* pointer1 = tailFloor;        //указатель по этажам
	rooms* pointer2 = NULL;             //указатель по комнатам
	people* pointer3 = NULL;            //указатель по людям
	while (pointer1)
	{
		while (pointer2)
		{
			pointer2 = tailFloor->room; //начинаем с хвоста
			while (pointer3)
			{
				pointer3 = tailFloor->room->human;                             //установка указателя на входной элемент
				tailFloor->room->human = tailFloor->room->human->next_person;  //свдиг хвоста
				free(pointer3);                                                //освобождение памяти
			}
			tailFloor->room = tailFloor->room->next_room;                      //сдвиг указателя на хвост по комнатам
			free(pointer2);                                                    //освобождение памяти от указателя на комнату
		}
		tailFloor = tailFloor->next_floor;                                     //сдвиг хвостового указателя на этаж
		free(pointer1);                                                        //освобождение памяти от уделяемого этажа
		pointer1 = tailFloor;                                                  //стали на новый этаж
	}
	pointer3 = tailHuman;                                                      //указатель на хвост очереди людей на заселение
	while (pointer3)                                                           //цикл по удалению очереди
	{
		tailHuman = tailHuman->next_person;                                    //сдвиг хвоста
		free(pointer3);                                                        //освобождение памяти
		pointer3 = tailHuman;                                                  //передвинулись на новый элемент
	}
	pointer3 = tailDeleted;                                                    //указатель на хвост очереди выселенных людей
	while (pointer3)                                                           //цикл по удалению очереди выселенных людей
	{
		tailDeleted = tailDeleted->next_person;                                //свдиг хвоста
		free(pointer3);                                                        //освобождение памяти
		pointer3 = tailDeleted;                                                //новый удаляемый элемент
	}
}