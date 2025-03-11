#include "Header.h"                        //���������� ����������

people* menu_del(floor *&headFloor, floor *&tailFloor) //������� ���� ��������� �������� �� ���������
{
	people* person = NULL;                 //��������� �� ����������� �������� 
	if (!tailFloor || !headFloor)          //�������� �� ������� �������
	{
		printf("%c[%d;%dm\n����� �����!%c[%dm\n", 27, 1, 31, 27, 0);
		return NULL;
	}
	printf("\n������� ����� ����� ��� ���������: ");
	int floorNumber = input_int();         //����� ������� ����� �����
	printf("������� ����� �������: ");
	int roomNumber = input_int();          //����� ������� ����� �������
	input_person_info(person);             //����� ������� ����� ���������� � ��������
	if (fun_del(tailFloor, headFloor, person, floorNumber, roomNumber))  //����� ������� �������� �������� �� ���������
	{
		printf("%c[%d;%dm\n������� �������!%c[%dm\n", 27, 1, 32, 27, 0);
		return person;                     //������� ���������� ��������
	}
	else return NULL;
}

int fun_del(floor* &tailFloor, floor* &headFloor, people* person, int floorNumber, int roomNumber)    //������� �������� �������� �� ���������
{
	floor *pointerFloor = tailFloor, *choosenFloor = tailFloor; //��������� ��� ������� �� ������ � �� ��������� ����
	rooms* pointerRoom = NULL, *pointerRoom_prev = NULL;        //��������� ��� ������� �� �������� � �� ���������� �������
	people* pointerHuman = NULL;                                //��������� ��� ������� �� �����
	if (search_person(pointerFloor, choosenFloor, pointerRoom_prev, person, floorNumber, roomNumber)) //����� ������� ������ ��������
	{  
		pointerRoom = choosenFloor->room;                       //��������� ��������� �������� ����������
		pointerHuman = choosenFloor->room->human;
	    if (tailFloor == headFloor && headFloor == choosenFloor) tailFloor = headFloor = NULL; //���� ������������ ����
		if (pointerHuman && pointerHuman->next_person == pointerHuman && pointerHuman->previous_person == pointerHuman)
		{ //� ������ ������ ���� �������
			if (pointerFloor->room == choosenFloor->room) pointerFloor->room = pointerRoom->next_room; //���� ������� �� ������
			else if (choosenFloor->room == headFloor->room) headFloor->room = pointerRoom_prev;        //���� ������� �� ������
			else pointerRoom_prev->next_room = pointerRoom->next_room;                                 //����� ��������
			free(pointerHuman); pointerHuman = NULL;            //������������ ������ � ��������� ����������
			free(pointerRoom); pointerRoom = NULL;              //������������ ������ � ��������� ����������
			pointerFloor->freePlaces += 1;                      //���������� ���-�� ��������� ����
			if (pointerRoom && (choosenFloor->next_floor || choosenFloor->previous_floor)) //���� ������� �� ���� ������������
			{
				if(pointerFloor->previous_floor)pointerFloor->previous_floor->next_floor = pointerFloor->next_floor; //����� ��������
				if(pointerFloor->next_floor)pointerFloor->next_floor->previous_floor = pointerFloor->previous_floor; //����� ��������
				free(pointerFloor);                             //������������ ������ �� �������
				pointerFloor = NULL;                            //��������� ���������
			}
			return 1;                                           //1 - ������, ��� ������� ��������
		}
		if (pointerFloor->room == choosenFloor->room) pointerFloor->room = pointerFloor->room->next_room; //��������� ����� ����� (��� ������)
		if (pointerHuman == pointerFloor->room->human) pointerRoom->human = pointerHuman->next_person;    //��������� ����� ����� (� ������)
		pointerHuman->previous_person->next_person = pointerHuman->next_person;                           //����� ��������
		pointerHuman->next_person->previous_person = pointerHuman->previous_person;                       //����� ��������
		free(pointerHuman);                                                                               //������������ ������
		if (!pointerRoom->human)                                    //���� ������� ����� �����
		{
			pointerRoom_prev->next_room = pointerRoom->next_room;   //��������� ����� �����
			free(pointerRoom);                                      //������������ ������
			pointerRoom = NULL;                                     //��������� ���������
		}
		if (!pointerFloor->room)                                    //������� ����� ����� (��� ������)
		{
			if (tailFloor == pointerFloor) tailFloor = pointerFloor->next_floor;     //���� �� ��������� �� ������
			if (pointerFloor == headFloor) headFloor = headFloor->previous_floor;    //���� �� ��������� �� ������ 
			pointerFloor->previous_floor->next_floor = pointerFloor->next_floor;     //����� ��������
			pointerFloor->next_floor->previous_floor = pointerFloor->previous_floor;
			free(pointerFloor);                                     //������������ ������
			pointerFloor = NULL;                                    //��������� ���������
		}
		pointerFloor->freePlaces += 1;                              //���������� ����� ��������� ����
		return 1;                                                   //1 - ������� ������ 
	}
	else return 0;
}