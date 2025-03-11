#include "Header.h"                 //����������� ����������
//������� ������ �������� � ���������
int search_person(floor* &pointerFloor, floor* &choosenFloor, rooms*& pointerRoom_prev, people* person, int floorNumber, int roomNumber)
{
	rooms* pointerRoom = NULL;      //��������� �� ��������
	people* pointerHuman = NULL;    //��������� �� �����
	while (pointerFloor && pointerFloor->numberOfFloor != floorNumber)  //���� �� ������ ������� �����
		pointerFloor = pointerFloor->next_floor;
	if (pointerFloor)               //���� ������
	{
		pointerRoom = pointerRoom_prev = pointerFloor->room;            //��������� ��������� ��������� �� �������
		while (pointerRoom && pointerRoom->numberOfRoom != roomNumber)  //���� �� ������ ������ �������
		{
			pointerRoom_prev = pointerRoom;                             //��������� ��������� �� ���������� �������
			pointerRoom = pointerRoom->next_room;                       //������� � ��������� �������
		}
		if (pointerRoom)            //������� �������
		{
			pointerHuman = pointerRoom->human;  //��������� ��������� ��������� �� �����
			while (pointerHuman)                //���� �� ������ ��������
			{
				if (!strcmp(pointerHuman->name, person->name) && !strcmp(pointerHuman->surname, person->surname)
					&& !strcmp(pointerHuman->faculty, person->faculty) && pointerHuman->group == person->group) break;
				pointerHuman = pointerHuman->next_person;         //������� � ���������� �������� 
				if (pointerHuman == pointerRoom->human) return 0; //���� ��������� �� ����� �����
			}
		}
		else {
			printf("%c[%d;%dm������� �� �������!%c[%dm\n", 27, 1, 31, 27, 0);
			return 0; }
	}
	else {
		printf("%c[%d;%dm���� �� ������!%c[%dm\n", 27, 1, 31, 27, 0);
		return 0; }
	choosenFloor->room = pointerRoom;
	choosenFloor->room->human = pointerHuman;
	return 1;
}