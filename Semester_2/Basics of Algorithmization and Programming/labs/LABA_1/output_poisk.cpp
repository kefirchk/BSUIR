#include "Header.h"   //����������� ����������

void output_poisk(int t, pcopy *info2) //������� ������ ���������� ������ ��������������
{
	if (!t) //���� �������������� �� �������
	{
		puts("\n�������������� �� �������");
		return;
	}
	int k = 0;        //�������
	printf("\n");     //������� �� ����� ������
	while (k++ < 5) printf(" ");
	printf("�������������\n");

	//���������� ������� ����������� � ��������
	int flag = 0; //������
	for (int i = 0; i < t; i++)
	{
		int p = i; //������� ��� ��������, ��� �� ������ ������� ����� ��� ����������
		while ((--p) > -1) if (info2[i].number == info2[p].number && info2[i].bukva == info2[p].bukva) flag = 1; //���� �������� + �������� �� ���������� �������� ������
		if (!flag) //���� ������ ��������� � �� ���� ����������� �����
		{
			k = 0; //��������� ��������
			printf(" ");
			while (k++ < 21) printf("_"); //������� ��������� ������� ������� �����
			printf("\n|%10d%-11c|\n", info2[i].number, info2[i].bukva);
			printf("|");
			k = 22;
			while (k-- > 1) printf("_"); //������� ��������� ������ ������� �����
			printf("|");
			printf("\n|%-21s|", info2[i].name); //����� �����
			printf("\n|%-21s|\n", info2[i].surname); //����� �������
			for (int j = i + 1; j < t; j++)
			{
				if (info2[i].number == info2[j].number && info2[i].bukva == info2[j].bukva) { //���� ������ �������� ���������
					printf("|");
					while (k++ < 21) printf(" ");
					printf("|\n|%-21s|", info2[j].name); //����� ����� �������������
					printf("\n|%-21s|\n", info2[j].surname); //����� ������� �������������
					k = 0; //��������� ��������
				}
			}
			printf("|");
			while (k++ < 21) printf("_");;//������� ������ ������� �������
			puts("|");
		}
		flag = 0; //��������� ������
	}
}