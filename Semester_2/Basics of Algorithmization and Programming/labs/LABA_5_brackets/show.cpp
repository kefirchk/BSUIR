#include "Header.h"    //����������� ����������

void show(stack *head) //������� ��������� ��������� �����
{
	if (!head)         //���� ���� ����
	{
		puts("\n���� ����");
		return;
	}
	puts("\n����:");
	do 
	{
		printf("%c\n", head->bracket);  //����� ���������� �������� �������� �����
		head = head->next;              //������� � ���������� �������� �����
	} while (head);    //���� ���� �� ����
}