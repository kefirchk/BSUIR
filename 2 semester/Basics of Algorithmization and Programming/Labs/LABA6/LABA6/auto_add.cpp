#include "Header.h"

void auto_add(int* ms, floor* tailFloor, floor* headFloor, people* tailHuman, people* headHuman)
{
	floor* ptrFloor = NULL, *newFloor = NULL;
	rooms* ptrRoom = NULL;
	people* ptrHuman = NULL;
	people* person = NULL; //указатель на человека, которого засел€етс€
	int flag = 0;
	while (1)
	{
		puts("\n¬ыберете вариант заселени€:"
			"\n1 - «аселить человека из очереди на заселение"
			"\n2 - «аселить человека отдельно");
		char c = _getch();
		int i;
		if (c == '1')
		{
			person = headHuman;
		}
		else
		{
			input_person_info(person); //ввод информации о человеке
		}
		for (i = 1; i <= ms[0]; i++)
		{
			if (ptrFloor)
			{
				if (i != ptrFloor->numberOfFloor)
				{
					newFloor = memory1();
					ptrFloor->previous_floor->next_floor = newFloor;
					newFloor->previous_floor = ptrFloor->previous_floor;
					ptrFloor->previous_floor = newFloor;
					newFloor->next_floor = ptrFloor;

					newFloor->numberOfFloor = 1;                //вносим информацию о номере этажа
					newFloor->room->numberOfRoom = 1;           //вносим информацию о номере комнаты
					newFloor->room->countOfPeople += 1;         //увеличиваем количество людей в комнате
					newFloor->allPlaces = ms[1] * ms[2];        //количество всех мест на этаже
					newFloor->freePlaces = ms[1] * ms[2] - 1;   //количество свободных мест на этаже
					copy_info(newFloor->room->human, person);   //копирование информации в конечную структуру
					newFloor->room->human->next_person =
						newFloor->room->human->previous_person = newFloor->room->human; //замыкаем элемент сам на себ€
					flag = 1; //человек заселен
					break;
				}
				if (ptrFloor->freePlaces) break;
				ptrFloor = ptrFloor->next_floor;
			}
			else break;
		}
		if (!flag && ptrFloor)          //нашелс€ этаж со свободными местами
		{
			ptrRoom = ptrFloor->room;
			while (ptrRoom)
			{

				ptrRoom = ptrRoom->next_room;
			}
		}
		else if (!flag && !ptrFloor)    //
		{

		}
		else if (!flag && !ptrFloor && i > ms[0])
		{

		}
		break;
	}
}