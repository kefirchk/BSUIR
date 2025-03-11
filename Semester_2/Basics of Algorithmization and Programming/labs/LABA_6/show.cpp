#include "Header.h"                       //����������� ����������

void show(floor* tailFloor)               //������� ��������� ���������� � ���������� �����
{
	if (!tailFloor)                       //�������� �� ������� �������
	{
		printf("%c[%d;%dm\n����� �����!%c[%dm\n", 27, 1, 31, 27, 0);
		return;
	}
	floor* pointerFloor = tailFloor;      //��������� �� ����� 
	rooms* pointerRoom = tailFloor->room; //��������� �� �������
	people* pointerHuman = NULL;          //��������� �� �����
	puts("�������� ����:");
	printf("�������� �����:");
	while (pointerFloor)                  //����� �������� ������
	{
		printf(" %d", pointerFloor->numberOfFloor); //����� ���������� �����
		pointerFloor = pointerFloor->next_floor;    //������� � ���������� �����
	}
	printf("\n");                         //����� ������
	pointerFloor = tailFloor;             //��������� �� ������
	int floorNumber = input_int();        //����� ������� ������ �����
	while (pointerFloor)                  //���� �� ������ ���������� �����
	{
		if (pointerFloor && pointerFloor->numberOfFloor == floorNumber) //���� ���� ������
		{
			int k = 0;                    //�������
			printf(" ");
			while (k++ < 69) printf("_"); //������� ������� ������� �������
			printf("\n|���\t\t|�������        |���������      |������    |�������   |\n|"); //����� "�����"
			k = 66;
			while (k-- > 1)               //���������� ������� ������� �������
			{
				if (k == 10 || k == 20 || k == 35 || k == 50) printf("|");
				printf("_");
			}
			pointerRoom = pointerFloor->room;     //��������� ��������� �� ������ ������
			while (pointerRoom)                   //���� �� ��������
			{
				pointerHuman = pointerRoom->human;//��������� �� ������� ��������
				while (pointerHuman)              //���� �� �����
				{
					printf("|\n|%-15s|%-15s|%-15s|%-10d|%-10d", pointerHuman->name, pointerHuman->surname,
						pointerHuman->faculty, pointerHuman->group, pointerRoom->numberOfRoom);
					pointerHuman = pointerHuman->next_person;       //������� � ���������� ��������
					if (pointerHuman == pointerRoom->human) break;  //���� ����� �� ������� �������
				}
				pointerRoom = pointerRoom->next_room;               //������� � ��������� �������
			}
			printf("|\n|");
			while (k++ < 65)                                        //������� ������ ������� �������
			{
				if (k == 16 || k == 31 || k == 46 || k == 56) printf("|");
				printf("_");
			}
			puts("|");
			return;
		}
		pointerFloor = pointerFloor->next_floor;                    //������� � ���������� �����
	}
	if (!pointerFloor) 
		printf("%c[%d;%dm\n���� ����!%c[%dm\n", 27, 1, 31, 27, 0);
}