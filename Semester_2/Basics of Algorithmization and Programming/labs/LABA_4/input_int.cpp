#include "Header.h" //����������� ����������

int input_int(int choice)       //������� ����� ���������� ����� ��� ���������� ����� ��������
{
	int k, n, f = 0; char symbol; //������������� ���������� ��� �������� � �����
	do
	{
		if (f++) puts("������!");
		rewind(stdin);                              //������ ������
		if (!choice) printf("������� ���������� �����: ");
		k = scanf_s("%d%c", &n, &symbol);           //���� ��������
		if (choice == 0 && k && n > 0 && symbol == '\n') break;
		if (choice == 1 && k && n >= 0 && n <= 4 && symbol == '\n') break;
		if (choice == 2 && k && n < 120 && n > 0 && symbol == '\n') break;
	} while (1);                //���� ���������� ����� � �������� �� ������������ �����
	return n;                   //������� ���������� ����� ��� ���������� �����
}