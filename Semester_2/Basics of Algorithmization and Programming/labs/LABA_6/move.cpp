#include "Header.h"                                      //����������� ����������

void move(floor*& headFloor, floor*& tailFloor, int* ms) //������� ����������� ��������
{
	people* person = NULL;            //��������� �� ������������� ��������
	rooms* pointerRoom_prev = NULL;   //��������� �� ���������� ������� �� ��������� � ���, � ������� ������ ��������� �������
	if (!headFloor || !tailFloor)     //������� �� ������ ��� �� �������
	{
		printf("%c[%d�%dm\n��������� �����!%c[%dm\n", 27, 1, 31, 27, 0);
		return;
	}
	printf("������� ����� �����, �� ������� ������ ����� �������: ");
	int oldFloorNumber = input_int(); //����� ������� ����� �����
	printf("������� ����� �������, � ������� ������ ����� �������: ");
	int oldRoomNumber = input_int();  //����� ������� ����� �������
	input_person_info(person);        //����� ������� ����� ���������� � ��������

	floor* pointerFloor = tailFloor, *choosenFloor = tailFloor;  //��������� �� �����, ��������� �� ��������� ����
	if (search_person(pointerFloor, choosenFloor, pointerRoom_prev, person, oldFloorNumber, oldRoomNumber)) //����� ������� ������ ��������
	{
		printf("������� ����� �����, ���� ��������� ���������� ��������: ");
		int newFloorNumber = input_int(); //����� ������� ����� ������ ������ �����
		printf("������� ����� �������, ���� ��������� ���������� �������� ");
		int newRoomNumber = input_int();  //����� ������� ����� ������ ����� �������

		if (fun_add(headFloor, tailFloor, person, ms, newFloorNumber, newRoomNumber)) //����� ������� ���������� �������� � �������
		{
			fun_del(tailFloor, headFloor, person, oldFloorNumber, oldRoomNumber);     //����� ������� �������� �������� �� ������ �������
			printf("%c[%d;%dm\n������� ���������!%c[%dm\n", 27, 1, 32, 27, 0);
		}
	}
}