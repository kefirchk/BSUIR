#include <stdio.h>                                            //����������� ���������
#include <stdlib.h>

float** giveMemory(int n, float** matrix)                     //������� ��������� ������
{
	if (!(matrix = (float**)malloc(n * sizeof(float*))))      //��������� ������ + �������� �� ��������� ������
	{
		printf("��� ��������� ������!");                      //����� �� ����� ������
		exit(0);                                              //�������������� ���������� ���������, ���� ������ �� ��������
	}
	int i;
	for (i = 0; i < n; i++)                                   //���� ��� ��������� ������ ��� ������
	{                                               
		*(matrix + i) = (float*)malloc(n * n * sizeof(float));
		if (NULL == (*(matrix + i)))                          //�������� �� ��������� ������
		{
			printf("��� ��������� ������!");                  //����� ������ �� �����
			exit(0);                                          //���������� �������� NULL
		}
	}
	return matrix;                                            //���������� ��������
}