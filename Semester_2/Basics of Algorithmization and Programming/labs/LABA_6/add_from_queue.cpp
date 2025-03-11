#include "Header.h"                        //����������� ����������

void add_from_queue(floor*& headFloor, floor*& tailFloor, people** tailHuman, people** headHuman, int* ms) //������� ���������� �������� �� ������� �� ��������� � ���������
{
	if (!*tailHuman && !*headHuman)        //���� ������� �� ��������� �����
	{
		printf("%c[%d;%dm\n������� �� ��������� �����!%c[%dm\n", 27, 1, 31, 27, 0);
		return;
	}
	int floorNumber, roomNumber, flag = 1; //�������, ��� �������� ������� �������� � ����� ������� ��� �� ������� �� ���������
	do
	{
		puts("\n������� ����� ����� ��� ���������:");
		floorNumber = input_int();         //����� ������� ����� ������ �����, �� ������� ��������� �������� ��������
		puts("������� ����� ������� ��� ���������:(<100)");
		roomNumber = input_int();          //����� ������� ����� ������ �������, � ������� ��������� �������� ��������
		if (floorNumber < 1 || floorNumber > ms[0] || roomNumber < 1 || roomNumber > ms[1]) 
			printf("%c[%d;%dm\n������!%c[%dm\n", 27, 1, 31, 27, 0);
		else break;
	} while (1);
	people* person = *headHuman;           //��������� �� ������������ ��������
	if (fun_add(headFloor, tailFloor, person, ms, floorNumber, roomNumber)) //���� 1, �������� ������� ��������, ����� ������� ��� �� ������� �� ���������
	{
		printf("%c[%d;%dm\n������� �������!%c[%dm\n", 27, 1, 32, 27, 0);
		if (*headHuman == *tailHuman) *headHuman = *tailHuman = NULL;       //� ������� ��� ���� ������������ �������
		else *headHuman = (*headHuman)->previous_person;                    //������������� ������
		free(person);                                                       //������������ ������
	}
}