#include "Headers.h"                                        //����������� ���������

char** memory_for_str(int n, int size, char** str)          //������� ��������� ������ ��� �����
{
	if (!(str = (char**)malloc(n * sizeof(char*))))         //��������� ������ + �������� �� ��������� ������
	{
		printf("��� ��������� ������!");                    //����� �� ����� ������
		exit(0);                                            //���������� ���������
	}
	for (int i = 0; i < n; i++)                             //���� ��� ��������� ������ ��� ������
	{
		*(str + i) = (char*)malloc((size+1) * sizeof(char));//��������� ������ ��� �������� �����
		if (NULL == (*(str + i)))                           //�������� �� ��������� ������
		{
			free(str);                                      //������������ ������ �� ���������� �� ������
			printf("��� ��������� ������!");                //����� ������ �� �����
			exit(0);                                        //���������� ���������
		}
	}
	return str;                                             //����������� �������� str
}