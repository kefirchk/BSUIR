#include <stdio.h>                                          //����������� ����������
#include <stdlib.h>

float* algo(int &n, float** matrix, int &flag, float* array)//������� ��������� ������� ������
{
	float sumDio = 0, sumDown = 0, sumUp = 0;               //���������� ����������
	for (int i = 0; i < n; i++)                             //���� �� ������ �����, ������������ � ������������� �����
	{
		if (matrix[i][0] < 0)                               //������ �� �������
		{
			if (i > 0)
				for (int k = 1; k <= i; k++)
					sumDown = sumDown + matrix[i][i - k];   //���������� ����� ��������� ���� ������� ���������
			for (int k = 1; k < n - i; k++)
				sumUp = sumUp + matrix[i][i + k];           //���������� ����� ��������� ���� ������� ���������
			sumDio = sumDio + matrix[i][i];                 //���������� ����� ��������� ������� ���������
		}
		if (matrix[i][0] >= 0) flag++;                      //���������� ��������
	}
	if (flag == n)                                          //������� ������ ������ �� �����
	{
		printf("\n�����, ������������ � �������������� ��������, ���.\n"); //����� ������, ���� ����������� �������
	}                                      
	if (!(array = (float*)malloc(3 * sizeof(float))))       //��������� ������ ��� ������
	{                                                       //�������� �� ��, ��������� �� ������
		printf("��� ��������� ������!");                    //����� ������ �� �����
		exit(0);                                            //���������� ���������
	}
	array[0] = sumDio;                                      //������������ ��������
	array[1] = sumDown;
	array[2] = sumUp;
	return array;                                           //���������� ������
}

