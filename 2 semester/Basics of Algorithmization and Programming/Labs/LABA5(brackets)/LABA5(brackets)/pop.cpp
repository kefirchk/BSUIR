#include "Header.h" //����������� ����������

char pop(stack **head) //������� �������� ���������� �������� ����� (� ������� �����)
{
	stack *old_head, info;  //��������������� ��������� � ���������
	old_head = *head;       //���������� ��������� �� ������� �����      
	info = **head;          //���������� ���������� ������� �����
	*head = (*head)->next;  //��������� ����������� "����" �� �����
	free(old_head);         //������� ������� � ������� �����
	return info.bracket;    //���������� �� ����������, ��� �������
}