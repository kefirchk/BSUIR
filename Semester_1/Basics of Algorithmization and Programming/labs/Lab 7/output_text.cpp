#include "Headers.h"                              //����������� ����������

void output_text(char** str, int &n)              //������� ������ �� ����� ���������� ������
{
	puts("\n��������� �����:");                   //����� ������
	for (int i = 0; i < n; i++)                   //���� �� i ��� ����� ������
	{
		printf("\n");                             //������� �� ����� ������
		for (int j = 0; (*(*(str + i) + j)) != '\0'; j++)   //���� ��� ������ ������ �����������
		{
			printf("%c", (*(*(str + i) + j)));    //����� ���������� �������
		}
	}
	printf("\n");                                 //������� �� ����� ������                     
}