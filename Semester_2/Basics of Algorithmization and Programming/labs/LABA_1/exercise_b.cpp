#include "Header.h"                 //����������� ����������

int exercise_b(pupil *info1, int size, int *ms1, int *ms2) //������� ������ ������������� � ������������ �������
{
	int flag = 0, flag1 = 0, flag2 = 0;  //flag, flag1, flag2 - ������
	int k = 0; //������� ��� ������� ��������
	for (int i = 0; i < size; i++)      //���� �� i (i-� ������� ������������ � ������� j-��)
	{
		for (int j = 0; j < size; j++)  //���� �� j (������� j-� ������� ��� ��������� � i-�)
		{
			if (!strcmp(info1[ms1[i]].familia, info1[ms1[j]].familia) && info1[ms1[i]].letter != info1[ms1[j]].letter && info1[ms1[i]].clas == info1[ms1[j]].clas)     //���� 0, �� ������ ������� ���������
			{
				if (!flag1)          //���� 0, �� ������ ������� ���������� � ������ ���
				{
					//if (!flag2) printf("\n������������ � ������������ �������:");
					ms2[k++] = i;
					//printf("\n%s %s (%d ������) - ", info[ms1[i]].imya, info[ms1[i]].familia, info[ms1[i]].clas);
					flag2 = 1;       //������� ���� �� ���� ���� ���������� �������
				}
				//if (flag2 && flag1) printf(", "); //��������� �������
				//if (j != i) printf("%s %s", info[ms1[j]].imya, info[ms1[j]].familia);
				if (j != i) ms2[k++] = j;
				flag1 = 1;           //������������ ������� ��� ����������
			}
		}
		flag1 = 0;                   //���������� � ���������� ��������, ����� ��������� ����� ��������
	}
	if (!flag2) puts("\n���������� ������� � ������������ ������� �� �������");
	printf("\n");
	return k;
}