#include "Header.h"                          //����������� ����������

void freeAll(floor* &tailFloor, people* &tailHuman, people* &tailDeleted) //������� ������������ ������ �� ���� ����� �������
{
	if (!tailFloor) return;             //���� ��������� ����� � �� ���� �� ���������� ������
	floor* pointer1 = tailFloor;        //��������� �� ������
	rooms* pointer2 = NULL;             //��������� �� ��������
	people* pointer3 = NULL;            //��������� �� �����
	while (pointer1)
	{
		while (pointer2)
		{
			pointer2 = tailFloor->room; //�������� � ������
			while (pointer3)
			{
				pointer3 = tailFloor->room->human;                             //��������� ��������� �� ������� �������
				tailFloor->room->human = tailFloor->room->human->next_person;  //����� ������
				free(pointer3);                                                //������������ ������
			}
			tailFloor->room = tailFloor->room->next_room;                      //����� ��������� �� ����� �� ��������
			free(pointer2);                                                    //������������ ������ �� ��������� �� �������
		}
		tailFloor = tailFloor->next_floor;                                     //����� ���������� ��������� �� ����
		free(pointer1);                                                        //������������ ������ �� ���������� �����
		pointer1 = tailFloor;                                                  //����� �� ����� ����
	}
	pointer3 = tailHuman;                                                      //��������� �� ����� ������� ����� �� ���������
	while (pointer3)                                                           //���� �� �������� �������
	{
		tailHuman = tailHuman->next_person;                                    //����� ������
		free(pointer3);                                                        //������������ ������
		pointer3 = tailHuman;                                                  //������������� �� ����� �������
	}
	pointer3 = tailDeleted;                                                    //��������� �� ����� ������� ���������� �����
	while (pointer3)                                                           //���� �� �������� ������� ���������� �����
	{
		tailDeleted = tailDeleted->next_person;                                //����� ������
		free(pointer3);                                                        //������������ ������
		pointer3 = tailDeleted;                                                //����� ��������� �������
	}
}