#include "Header.h"

void hat_for_ex1(pupil *info1, int size, int *ms1)
{
	if (size)
	{
		int k = 0, i = 0;
		printf("\n");
		while (i++ < 22) printf(" ");
		printf("������������\n");

		//������� ������� ������� �������
		printf(" ");
		while (k++ < 53) printf("_");

		//����� "�����" �������
		printf("\n|���\t\t\t");
		printf("�������\t\t\t");
		printf("����� |\n|");
		while (k-- > 1) printf("_");//������� ������ ������� �����
		printf("|");

		//���������� ������� ����������� � ��������
		for (i = 0; i < size; i++)
		{
			printf("\n|%-23s", info1[ms1[i]].imya);
			printf("%-24s", info1[ms1[i]].familia);
			printf("%-2d%-1c   |", info1[ms1[i]].clas, info1[ms1[i]].letter);
		}
		printf("\n|");
		while (k++ < 53) printf("_");;//������� ������ ������� �������
		puts("|");
	}
}