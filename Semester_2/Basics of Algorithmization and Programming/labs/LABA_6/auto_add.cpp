#include "Header.h"

void auto_add(int* ms, floor* tailFloor, floor* headFloor, people* tailHuman, people* headHuman)
{
	floor* ptrFloor = NULL, *newFloor = NULL;
	rooms* ptrRoom = NULL;
	people* ptrHuman = NULL;
	people* person = NULL; //��������� �� ��������, �������� ����������
	int flag = 0;
	while (1)
	{
		puts("\n�������� ������� ���������:"
			"\n1 - �������� �������� �� ������� �� ���������"
			"\n2 - �������� �������� ��������");
		char c = _getch();
		int i;
		if (c == '1')
		{
			person = headHuman;
		}
		else
		{
			input_person_info(person); //���� ���������� � ��������
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

					newFloor->numberOfFloor = 1;                //������ ���������� � ������ �����
					newFloor->room->numberOfRoom = 1;           //������ ���������� � ������ �������
					newFloor->room->countOfPeople += 1;         //����������� ���������� ����� � �������
					newFloor->allPlaces = ms[1] * ms[2];        //���������� ���� ���� �� �����
					newFloor->freePlaces = ms[1] * ms[2] - 1;   //���������� ��������� ���� �� �����
					copy_info(newFloor->room->human, person);   //����������� ���������� � �������� ���������
					newFloor->room->human->next_person =
						newFloor->room->human->previous_person = newFloor->room->human; //�������� ������� ��� �� ����
					flag = 1; //������� �������
					break;
				}
				if (ptrFloor->freePlaces) break;
				ptrFloor = ptrFloor->next_floor;
			}
			else break;
		}
		if (!flag && ptrFloor)          //������� ���� �� ���������� �������
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