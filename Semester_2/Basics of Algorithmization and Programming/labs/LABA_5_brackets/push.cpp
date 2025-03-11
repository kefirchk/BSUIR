#include "Header.h"  //����������� ����������

void push(stack **h, char c, int i) //������� ���������� �������� �� �������� �����
{
	stack *pointer;
	if (!(pointer = (stack*)calloc(1, sizeof(stack))))
	{
		puts("\n��� ��������� ������");
		return;
	}
	pointer->index = i;    //������� ��������� ������ ������ � ���� 
	pointer->bracket = c;  //������� ��������� ������ � ����
	pointer->next = (*h);  //���������� ����� ������ ������� �����
	*h = pointer;          //����� ������� ���������� �������� �����
}