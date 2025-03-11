#include "Header.h"                   //����������� ����������

void show_balance(info* tail, info* head, FILE* f, char* fileName)
{
	info* pointer = tail;             //��������� ��� ������� �� �������
	if (!file_in_str(tail, head, fileName, f)) //����� ������� �������� ���������� �� ����� � ������� 
	{ puts("���� ����"); return; }
	if (pointer = input_PIN(tail))    //����� ������� ����� � ������� ������
	{
		int k = 0;                    //�������
		printf(" ");
		while (k++ < 75) printf("_"); //������� ������� ������� �������
		k = 71;
		printf("\n|���\t\t|�������\t|�������   |����      |���. �����|���. �����|\n|"); //����� "�����" �������
		while (k-- > 1)                                                                 //���� �� ���������� ������� ������� �������
		{
			if (k == 10 || k == 20 || k == 30 || k == 40 || k == 55) printf("|");
			printf("_");
		}
		printf("|");
		printf("\n|%-15s|%-15s|%-10d|%-10d|%-10d|%-10d|\n|",                            //���������� ������� �����������
			pointer->name, pointer->surname, pointer->cash[0].dollar, 
			pointer->cash[1].euro, pointer->cash[2].RUB, pointer->cash[3].BYN);
		while (k++ < 70)                                                                //������� ������ ������� �������
		{
			if (k == 16 || k == 31 || k == 41 || k == 51 || k == 61) printf("|");
			printf("_");
		}
		puts("|");
	}
	else return;
}