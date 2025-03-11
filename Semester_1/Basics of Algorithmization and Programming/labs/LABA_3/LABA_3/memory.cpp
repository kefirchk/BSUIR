#include <stdio.h>                                //����������� ���������
#include <stdlib.h>
#include "functions.h"

int *memory(int n)                                //������� ��������� ������ ��� ������
{
	int *array;                                   //���������� �������
	array = (int *)malloc(n * sizeof(int));       //��������� ������
	if (NULL == array)                            //�������, ���� ������ �� ��������
	{
		printf("��� ��������� ������!");          //����� ������
		free(array);                              //������������ �������
		return NULL;                              //���������� �������� NULL
	}
	func2(n, array);                              //����� ������� ����� ��������� �������
	return array;                                 //���������� ������
}