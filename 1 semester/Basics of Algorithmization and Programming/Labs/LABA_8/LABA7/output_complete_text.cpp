#include "Headers.h"                             //����������� ����������

void output_complete_text(char** str, int n)     //������� ������ ��������������� ����
{
	printf("\n��������������� �����:\n");        //����� ������
	for (int i = 0; i < n; i++)                  //���� ��� ������ ���������������� ������ �� �������
	{
		printf("\n");                            //������� �� ����� ������
		for (int j = 0; (*(*(str+i)+j)) != '\0'; j++)  //���� ��� ������������� ������ ������
			printf("%c", (*(*(str+i)+j)));       //����� ���������� �������
	}
	printf("\n");                                //������� �� ����� ������
}