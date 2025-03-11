#include "Header.h" //����������� ����������

void output_table(int n, pupil *info1) //������� ������ ��������� ���������� � ��������
{
	int k = 0; int i = 0;

	//����� ��������� �������
	while (i++ < 20) printf(" ");
	printf("����� ����������\n");

	//������� ������� ������� �������
	printf(" ");
	while (k++ < 53) printf("_");

	//����� "�����" �������
	printf("\n|���\t\t\t");
	printf("�������\t\t\t");
	printf("����� |\n|");
	while (k-- > 1) printf("_");//������� ������ ������� �������
	printf("|");

	//���������� ������� ����������� � ��������
	for (int i = 0; i < n; i++)
	{
		printf("\n|%-23s", info1[i].imya);
		printf("%-24s", info1[i].familia);
		printf("%-2d%-1c   |", info1[i].clas, info1[i].letter);
	}
	printf("\n|");
	while (k++ < 53) printf("_");; //������� ������ ������� �������
	puts("|");
}