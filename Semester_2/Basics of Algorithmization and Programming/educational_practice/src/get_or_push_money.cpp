#include "Header.h" //����������� ����������

int get_push_fun(int choice, int sum, info* &pointer, int k); //������� ��������� ����� ����� �� ����� 

void get_or_push_money(info* tail, info* head, char* fileName, FILE* &f, int choice)//������� ����������/������ ����� 
{
	info* pointer = tail;                   //��������� �� ������� �������
	file_in_str(tail, head, fileName, f);   //����� ������� �������� ���������� �� ����� � �������
	if (pointer = input_PIN(tail))          //����� ������� ����� � ������� ������
	{
		int temp = 0, k = currency_choice();//��������� ����������; ����� ������� ������ ������
		temp = get_push_fun(choice, sum_choice(), pointer, k); //����� ������� ��������� ����� ����� �� �����
		if (!temp && !choice)               //���� ������������ �������� ������� �� ����� (�������� ������ ����� �� �����)
			printf("%c[%d;%dm������������ �������� ������� �� �������!%c[%dm\n", 27, 1, 31, 27, 0);
		else replace_file(tail, fileName, f); //����� ������� ������ �����
		return;
	}
	else return;
}

int get_push_fun(int choice, int sum, info* &pointer, int k) //������� ��������� ����� ����� �� ����� 
{
	if (choice)                                       //���������� �����
		pointer->cash[k].dollar += sum;               //��������� ����� �� �����
	else                                              //������ ����� �� �����
	{
		if (pointer->cash[k].dollar -= sum) return 1; //���� ����� ���������� �� ����� ��� ������ ��������� �����
		else pointer->cash[k].dollar += sum;          //���� ����� ������������
	}
	return 0;
}