#include "Header.h"       //подключение библиотек

void menu_add(floor*& headFloor, floor*& tailFloor, int *ms) //функция подменю заселения человека в общежитие
{
	int floorNumber, roomNumber;   //номера этажа и комнаты соответственно
	while(1)
	{
		printf("\nВведите номер этажа для заселения: ");
		floorNumber = input_int(); //ввод номера этажа
		printf("Введите номер комнаты для заселения: ");
		roomNumber = input_int();  //ввод номера комнаты
		if (floorNumber < 1 || floorNumber > ms[0] || roomNumber < 1 || roomNumber > ms[1]) //если допущена ошибка 
			printf("%c[%d;%dm\nОшибка!%c[%dm\n", 27, 1, 31, 27, 0);
		else break;
	}
	people* person = NULL;         //указатель на человека, которого заселяется
	input_person_info(person);     //вызов функции ввода информации о человеке
	if (fun_add(headFloor, tailFloor, person, ms, floorNumber, roomNumber)) //вызов функции добавления человека в общежитие 
		printf("%c[%d;%dm\nЧеловек заселен!%c[%dm\n", 27, 1, 32, 27, 0);
}

int fun_add(floor*&headFloor, floor*&tailFloor, people* person, int *ms, int floorNumber, int roomNumber) //функция заселения
{
	if (!headFloor || !tailFloor)                   //очередь из этажей еще не создана
	{
		floor* newFloor = memory1();                //выделение памяти под этаж
		newFloor->room = memory2();                 //выделение памяти под комнату
		newFloor->room->human = memory3();          //выделение памяти под человека
		headFloor = newFloor;                       //указатель на голову очереди
		tailFloor = newFloor;                       //указатель на хвост очереди
		newFloor->numberOfFloor = floorNumber;      //вносим информацию о номере этажа
		newFloor->room->numberOfRoom = roomNumber;  //вносим информацию о номере комнаты
		newFloor->room->countOfPeople += 1;         //увеличиваем количество людей в комнате
		newFloor->allPlaces = ms[1] * ms[2];        //количество всех мест на этаже
		newFloor->freePlaces = ms[1] * ms[2] - 1;   //количество свободных мест на этаже
		copy_info(newFloor->room->human, person);   //копирование информации в конечную структуру
		newFloor->room->human->next_person = 
			newFloor->room->human->previous_person = newFloor->room->human; //замыкаем элемент сам на себя
		return 1;
	}
	else
	{
		floor *pointerFloor = tailFloor;             //указатель для прохода по этажам, этажи расставлены в порядке возрастания
		while (pointerFloor && floorNumber > pointerFloor->numberOfFloor) //поиск вводимого этажа или большего, чем вводимый
			pointerFloor = pointerFloor->next_floor; //переход к следующему элементу

		if (pointerFloor && floorNumber == pointerFloor->numberOfFloor) //если нашелся требуемый этаж
		{
			rooms* pointerRoom = pointerFloor->room, 
				*pointerRoom_prev = pointerRoom; //указатель на рассматриваемую комнату и указатель на предыдущий элемент
			//комнаты расставлены в порядке возрастания их номеров в очереди
			while (pointerRoom && roomNumber > pointerRoom->numberOfRoom) //пока не найдена требуемая комната или больше по номеру, чем вводимая
			{
				pointerRoom_prev = pointerRoom;       //запоминаем адрес предыдущего элемента
				pointerRoom = pointerRoom->next_room; //переход к следующему элементу 
			}
			if (pointerRoom && roomNumber == pointerRoom->numberOfRoom) //если нашлась требуемая комната
			{
				people* pointerHuman = pointerRoom->human; //указатель для обхода жильцов
				if (pointerHuman)                          //если в комнате кто-то проживает
				{
					int i;                                 //индекс 
					for (i = 1;; i++)                      //цикл по людям, проживающих в комнате (считаем количество жильцов)
					{
						pointerHuman = pointerHuman->next_person;      //переход к следующему человеку
						if (pointerHuman == pointerRoom->human) break; //если обходя кольцо, вернулись в точку входа
					}
					if (i >= ms[2]) //если количество жильцов больше или равно максимального
					{
						printf("%c[%d;%dm\nВ комнате нет свободных мест!%c[%dm\n", 27, 1, 31, 27, 0);
						return 0;
					}
					else            //вставка элемента сразу после элемента "точка входа"
					{
						people* newHuman = memory3(); //выделение памяти под человека
						//В - входная точка; Э - элемент, следующий за В; N - новый элемент 
						newHuman->next_person = pointerRoom->human->next_person;    // N->Э 
						pointerRoom->human->next_person = newHuman;                 // В->N->Э
						newHuman->previous_person = pointerRoom->human;             // В<-N
						newHuman->next_person->previous_person = newHuman;          // N<-Э

						copy_info(newHuman, person); 	 //копирование введенных данных
						pointerRoom->countOfPeople += 1; //увеличиваем количество жильцов в комнате
						pointerFloor->freePlaces -= 1;   //уменьшение количеств свободных мест на этаже
						return 1;
					}
				}
			}
			else //если требуемой комнаты не найдено
			{//вставка комнаты перед той, на которую сейчас указывает pointerRoom
				rooms* newRoom = memory2();             //выделение памяти под комнату
				newRoom->human = memory3();             //выделение памяти под человека
				newRoom->next_room = pointerRoom;       //вставка элемента
				pointerRoom_prev->next_room = newRoom; 
				newRoom->numberOfRoom = roomNumber;     //вносим информацию о номере комнате
				copy_info(newRoom->human, person);      //копирование введенных данных
				newRoom->countOfPeople += 1;            //увеличиваем количество жильцов в комнате
				pointerFloor->freePlaces -= 1;          //уменьшаем количество свободных мест
				return 1;
			}
		}
		else //если не нашелся требуемый этаж
		{
			floor* newFloor = memory1();              //выделение памяти под этаж
			newFloor->room = memory2();               //выделение памяти под комнату
			newFloor->room->human = memory3();        //выделение памяти под человека
			if (pointerFloor)                         //если этаж нужно вставить перед хвостом очереди
			{
				newFloor->next_floor = pointerFloor;  //вставка этажа
				newFloor->previous_floor = pointerFloor->previous_floor;
				if(tailFloor!=pointerFloor)           //чтобы не было ошибки при pointerFloor->previous_floor = NULL
					pointerFloor->previous_floor->next_floor = newFloor;
				pointerFloor->previous_floor = newFloor;
				tailFloor = newFloor;                 //корректировка хвоста
			}
			else //вводимый этаж больше по номеры всех предыдущих
			{
				pointerFloor = headFloor;             //перемещаемся на голову
				pointerFloor->next_floor = newFloor;  //вставка элемента после головы
				newFloor->previous_floor = headFloor;
				headFloor = newFloor;                 //корректировка головы
				newFloor->room->human->next_person =  //замыкаем элемент сам на себе
					newFloor->room->human->previous_person = newFloor->room->human;
			}
			newFloor->numberOfFloor = floorNumber;    //вносим данные о номере этаже
			newFloor->room->numberOfRoom = roomNumber;//вносим данные о номере комнаты
			newFloor->allPlaces = ms[1] * ms[2];      //вносим данные о кол-ве всех мест на этаже
			newFloor->freePlaces = ms[1] * ms[2] - 1; //вносим данные о кол-ве свободных мест на этаже
			copy_info(newFloor->room->human, person); //копирование данных о человеке
			newFloor->room->countOfPeople += 1;       //увеличение количества жильцов в комнате
			return 1;
		}
	}
}