#include "Header.h"       //����������� ���������

void menu_add(floor*& headFloor, floor*& tailFloor, int *ms) //������� ������� ��������� �������� � ���������
{
	int floorNumber, roomNumber;   //������ ����� � ������� ��������������
	while(1)
	{
		printf("\n������� ����� ����� ��� ���������: ");
		floorNumber = input_int(); //���� ������ �����
		printf("������� ����� ������� ��� ���������: ");
		roomNumber = input_int();  //���� ������ �������
		if (floorNumber < 1 || floorNumber > ms[0] || roomNumber < 1 || roomNumber > ms[1]) //���� �������� ������ 
			printf("%c[%d;%dm\n������!%c[%dm\n", 27, 1, 31, 27, 0);
		else break;
	}
	people* person = NULL;         //��������� �� ��������, �������� ����������
	input_person_info(person);     //����� ������� ����� ���������� � ��������
	if (fun_add(headFloor, tailFloor, person, ms, floorNumber, roomNumber)) //����� ������� ���������� �������� � ��������� 
		printf("%c[%d;%dm\n������� �������!%c[%dm\n", 27, 1, 32, 27, 0);
}

int fun_add(floor*&headFloor, floor*&tailFloor, people* person, int *ms, int floorNumber, int roomNumber) //������� ���������
{
	if (!headFloor || !tailFloor)                   //������� �� ������ ��� �� �������
	{
		floor* newFloor = memory1();                //��������� ������ ��� ����
		newFloor->room = memory2();                 //��������� ������ ��� �������
		newFloor->room->human = memory3();          //��������� ������ ��� ��������
		headFloor = newFloor;                       //��������� �� ������ �������
		tailFloor = newFloor;                       //��������� �� ����� �������
		newFloor->numberOfFloor = floorNumber;      //������ ���������� � ������ �����
		newFloor->room->numberOfRoom = roomNumber;  //������ ���������� � ������ �������
		newFloor->room->countOfPeople += 1;         //����������� ���������� ����� � �������
		newFloor->allPlaces = ms[1] * ms[2];        //���������� ���� ���� �� �����
		newFloor->freePlaces = ms[1] * ms[2] - 1;   //���������� ��������� ���� �� �����
		copy_info(newFloor->room->human, person);   //����������� ���������� � �������� ���������
		newFloor->room->human->next_person = 
			newFloor->room->human->previous_person = newFloor->room->human; //�������� ������� ��� �� ����
		return 1;
	}
	else
	{
		floor *pointerFloor = tailFloor;             //��������� ��� ������� �� ������, ����� ����������� � ������� �����������
		while (pointerFloor && floorNumber > pointerFloor->numberOfFloor) //����� ��������� ����� ��� ��������, ��� ��������
			pointerFloor = pointerFloor->next_floor; //������� � ���������� ��������

		if (pointerFloor && floorNumber == pointerFloor->numberOfFloor) //���� ������� ��������� ����
		{
			rooms* pointerRoom = pointerFloor->room, 
				*pointerRoom_prev = pointerRoom; //��������� �� ��������������� ������� � ��������� �� ���������� �������
			//������� ����������� � ������� ����������� �� ������� � �������
			while (pointerRoom && roomNumber > pointerRoom->numberOfRoom) //���� �� ������� ��������� ������� ��� ������ �� ������, ��� ��������
			{
				pointerRoom_prev = pointerRoom;       //���������� ����� ����������� ��������
				pointerRoom = pointerRoom->next_room; //������� � ���������� �������� 
			}
			if (pointerRoom && roomNumber == pointerRoom->numberOfRoom) //���� ������� ��������� �������
			{
				people* pointerHuman = pointerRoom->human; //��������� ��� ������ �������
				if (pointerHuman)                          //���� � ������� ���-�� ���������
				{
					int i;                                 //������ 
					for (i = 1;; i++)                      //���� �� �����, ����������� � ������� (������� ���������� �������)
					{
						pointerHuman = pointerHuman->next_person;      //������� � ���������� ��������
						if (pointerHuman == pointerRoom->human) break; //���� ������ ������, ��������� � ����� �����
					}
					if (i >= ms[2]) //���� ���������� ������� ������ ��� ����� �������������
					{
						printf("%c[%d;%dm\n� ������� ��� ��������� ����!%c[%dm\n", 27, 1, 31, 27, 0);
						return 0;
					}
					else            //������� �������� ����� ����� �������� "����� �����"
					{
						people* newHuman = memory3(); //��������� ������ ��� ��������
						//� - ������� �����; � - �������, ��������� �� �; N - ����� ������� 
						newHuman->next_person = pointerRoom->human->next_person;    // N->� 
						pointerRoom->human->next_person = newHuman;                 // �->N->�
						newHuman->previous_person = pointerRoom->human;             // �<-N
						newHuman->next_person->previous_person = newHuman;          // N<-�

						copy_info(newHuman, person); 	 //����������� ��������� ������
						pointerRoom->countOfPeople += 1; //����������� ���������� ������� � �������
						pointerFloor->freePlaces -= 1;   //���������� ��������� ��������� ���� �� �����
						return 1;
					}
				}
			}
			else //���� ��������� ������� �� �������
			{//������� ������� ����� ���, �� ������� ������ ��������� pointerRoom
				rooms* newRoom = memory2();             //��������� ������ ��� �������
				newRoom->human = memory3();             //��������� ������ ��� ��������
				newRoom->next_room = pointerRoom;       //������� ��������
				pointerRoom_prev->next_room = newRoom; 
				newRoom->numberOfRoom = roomNumber;     //������ ���������� � ������ �������
				copy_info(newRoom->human, person);      //����������� ��������� ������
				newRoom->countOfPeople += 1;            //����������� ���������� ������� � �������
				pointerFloor->freePlaces -= 1;          //��������� ���������� ��������� ����
				return 1;
			}
		}
		else //���� �� ������� ��������� ����
		{
			floor* newFloor = memory1();              //��������� ������ ��� ����
			newFloor->room = memory2();               //��������� ������ ��� �������
			newFloor->room->human = memory3();        //��������� ������ ��� ��������
			if (pointerFloor)                         //���� ���� ����� �������� ����� ������� �������
			{
				newFloor->next_floor = pointerFloor;  //������� �����
				newFloor->previous_floor = pointerFloor->previous_floor;
				if(tailFloor!=pointerFloor)           //����� �� ���� ������ ��� pointerFloor->previous_floor = NULL
					pointerFloor->previous_floor->next_floor = newFloor;
				pointerFloor->previous_floor = newFloor;
				tailFloor = newFloor;                 //������������� ������
			}
			else //�������� ���� ������ �� ������ ���� ����������
			{
				pointerFloor = headFloor;             //������������ �� ������
				pointerFloor->next_floor = newFloor;  //������� �������� ����� ������
				newFloor->previous_floor = headFloor;
				headFloor = newFloor;                 //������������� ������
				newFloor->room->human->next_person =  //�������� ������� ��� �� ����
					newFloor->room->human->previous_person = newFloor->room->human;
			}
			newFloor->numberOfFloor = floorNumber;    //������ ������ � ������ �����
			newFloor->room->numberOfRoom = roomNumber;//������ ������ � ������ �������
			newFloor->allPlaces = ms[1] * ms[2];      //������ ������ � ���-�� ���� ���� �� �����
			newFloor->freePlaces = ms[1] * ms[2] - 1; //������ ������ � ���-�� ��������� ���� �� �����
			copy_info(newFloor->room->human, person); //����������� ������ � ��������
			newFloor->room->countOfPeople += 1;       //���������� ���������� ������� � �������
			return 1;
		}
	}
}