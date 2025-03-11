#include "Header.h"     //����������� ����������

int del_in_file(FILE *&f, info *&tail, info* &head, char* fileName)  //������� �������������� �� �������� �������� �� ����� � �������
{
	info* element = NULL;                     //��������� �� ��������� �������
	if (file_in_str(tail, head, fileName, f)) //����� ������� ������ ���������� �� ����� � ���������
	{
		if (element = input_PIN(tail))        //����� ������� ����� � ������� ������
		{
			del_person(&tail, &head, element);    //����� ������� �������� �������� �� �������
			replace_file(tail, fileName, f);      //����� ������� ������ �����
		}
	}
	else printf("%c[%d;%dm���� ����%c[%dm\n", 27, 1, 32, 27, 0);
	return 0;
}

void del_person(info** tail, info** head, info* &element) //������� �������� �������� �� �������
{
	info* pointer = *tail, *prev_pointer = *tail;         //��������� ��� ������ �������, ��������� �� ���������� ������� �� ��������� � pointer
	if (element)
	{
		if (!*tail || !*head)                             //������� �� �������
		{
			puts("���� ������ �����!");
			return;
		}
		if (*tail && *tail == *head)                      //� ������� ���� �������
		{
			free(*tail);                                  //���������� ������
			*head = *tail = NULL;                         //��������� ����������
			return;
		}
		while (pointer && pointer != element)             //���� �� �������, ���� �� ����� ��������� �������
		{
			prev_pointer = pointer;                       //��������� ��������� prev-pointer �� ���������� �������
			pointer = pointer->next;                      //��������� ��������� pointer �� ��������� �������
		}
		if (pointer)                                      //���� ������� ��������� �������
		{
			if (*tail == pointer) *tail = pointer->next;  //���� ��������� ������� - ��� ����� �������
			if (*head == pointer) *head = prev_pointer;   //���� ��������� ������� - ��� ������ �������
			else
			{
				prev_pointer = pointer->next;             //����� ��������
				free(pointer);                            //�������� ��������
			}
		}
	}
	else return;
}