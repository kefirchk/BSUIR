#include "Header.h"

void hat_for_ex2(pupil *info1, int size, int *ms2) //������� ������ ���������� ������ ������������� �� ������������ �������
{
	if (size)
	{
		int k = 0;    //c������
		printf("\n");
		while (k++ < 12) printf(" ");
		printf("������������ � ������������ �������\n");
		k = 0;

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
		int temp = 0;     //��������� ����������, ��� ����� �� ������ �������� ��������� �� ������������� �������
		for (int i = 0; i < size; i++)
		{
			int j = i;    //�������
			while(--j >= temp) //��������, ��� ����� ������������ ��������� ������ �������
			{   
				if (j && info1[ms2[j]].letter == info1[ms2[i]].letter && !strcmp(info1[ms2[j]].imya, info1[ms2[i]].imya) && !strcmp(info1[ms2[j]].familia, info1[ms2[i]].familia))
				{
					temp = i;
					printf("\n|");
					while (k++ < 53) printf("_");
					printf("|");
					k = 0;
				}
			}
			printf("\n|%-23s", info1[ms2[i]].imya); //����� �����
			printf("%-24s", info1[ms2[i]].familia); //����� �������
			printf("%-2d%-1c   |", info1[ms2[i]].clas, info1[ms2[i]].letter); //����� ������ � ����� ������ 
		}
		printf("\n|");
		while (k++ < 53) printf("_");;//������� ������ ������� �������
		puts("|");
	}
}