#include "Header.h"        //����������� ����������

int input_int(int choice)  //������� ����� ���������� �����
{
	int value, k, f = 0;   //value - ������� ����������, k - ��������� ����������, f - ������
	char c;                //� - ��������� ���������� ��� �������� ������������ �����
	do { 
		if (f++) puts("������!");
		rewind(stdin);     //������� ������
		k = scanf_s("%d%c", &value, &c);  //���� �������
		if (choice && k > 1 && c == '\n' && value < 120 && value > 0) break; //�������� �� ���� ��������
		if (!choice && k > 1 && c == '\n' && value > -1 && value < 5) break; //�������� �� ���� ���������� ������
	} while (1);
	return value;
}