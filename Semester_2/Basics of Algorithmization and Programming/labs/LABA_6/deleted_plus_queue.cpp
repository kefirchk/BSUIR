#include "Header.h"                                 //����������� ����������

void deleted_plus_queue(people** headHuman, people** tailHuman, people* person)  //������� ���������� �������� � ������ ���������� �����
{
	if (person)                                     //���� ������� ������������� ��� ������
	{
		if (!*tailHuman && !*headHuman)             //���� ������� ���� �����
		{
			*tailHuman = *headHuman = person;       //����������� ������� ���������� �� ����� � ������
		}
		else
		{
			person->next_person = *tailHuman;       //������� �������� � ����� �������
			(*tailHuman)->previous_person = person; //��������� ������ ����� ����������
			(*tailHuman) = person;                  //������������� ������
		}
	}
}