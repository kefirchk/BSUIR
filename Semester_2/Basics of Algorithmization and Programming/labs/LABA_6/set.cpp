#include "Header.h"                                   //����������� ����������

void set(people** tailHuman, people** headHuman)      //������� ���������� ����� �� ������� �� ���������
{
	people* newHuman = NULL, *person = NULL, *pointerHuman = *tailHuman;  //��������� �� ����-����������� ��������, ���������� ��������, ������� �������
	printf("\n");                                     //����� ������
	input_person_info(person);                        //����� ������� ����� ���������� � ��������
	newHuman = memory3();                             //����� ������� ��������� ������ ��� ��������

	if (!*tailHuman && !*headHuman)                   //������� ��� �� �������
	{
		*tailHuman = *headHuman = newHuman;           //��������� ���������� �� ����� � ������
	    strcpy_s(newHuman->name, person->name);       //����������� ���������� � �����
		strcpy_s(newHuman->surname, person->surname); //����������� �������
		strcpy_s(newHuman->faculty, person->faculty); //����������� ����������
		newHuman->group = person->group;              //����������� ������ ������
	}
	else                                              //������� ��� �������
	{
		newHuman->next_person = *tailHuman;           //������� �������� � ����� �������
		(*tailHuman)->previous_person = newHuman;     //������ ��������� ���������
		(*tailHuman) = newHuman;                      //������������� ������
		strcpy_s(newHuman->name, person->name);       //����������� ��������� ������
		strcpy_s(newHuman->surname, person->surname);
		strcpy_s(newHuman->faculty, person->faculty);
		newHuman->group = person->group;
	}
	printf("%c[%d;%dm\n������� �������� � ������� �� ���������!%c[%dm\n", 27, 1, 32, 27, 0);
}