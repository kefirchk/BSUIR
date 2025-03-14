#include "all_functions.h"                                      //����������� ����������

float* algo_with_output(int* array, float** matrix, float* result)               //������� ��������� ������� ������ � ������ �� ����� ����������
{
	int stroka = 0, stolb = 0;                                  //���������� ����������, ��� stroka - ������ ������ �������� ��������
	int flag = 0; int povtor = 1;                               //stolb - ������ ������� �������� ��������, min - ������� �������
	float min = 0;                                              //povtor � flag - ������������� ����������
	for (int i = 0; i < array[0]; i++)                          //����� ���������, ��������������� ������� ������
		for (int j = 0; j < array[1]; j++)                        
			if ((i + j) % 2 == 0 && matrix[i][j] > 0)           //������� ��� �������� �������
			{
				flag++;                                         //���������� ���������� flag �� 1 
				if (flag == 1)                                  //������� ��� ���������� flag
				{
					min = matrix[i][j];                         //��������� ���������� �������� ��� ���������� min
					stroka = i+1;                               //��������� ���������� �������� ������ ������
					stolb = j+1;                                //��������� ���������� �������� ������ �������
				}
				if (flag > 1 && matrix[i][j] == min) povtor++;  //�������� �� ������ ������� ��������� �������
				if (min > matrix[i][j])                         //��������� ���������
				{
					min = matrix[i][j];                         //��� ���������� ������� ����������� ������������ �������� �������� ���������� min
					stroka = i+1;                               //������������ ������ ������ �������� 
					stolb = j+1;                                //������������ ������ ������� ��������
				}
			}
	if (min > 0)                                                //������� ��� ���������� min
	{
		if (!(result = (float*)malloc(3 * sizeof(float))))  //��������� ������ ��� ��������� �� ������ + �������� �� ��������� ������
		{
			printf("��� ��������� ������!");                         //����� �� ����� ������
			exit(0);                                                 //���������� ���������
		}
		result[0] = min;
		result[1] = stroka;
		result[2] = stolb;
		if (povtor > 1) printf("\n����� ������� �� ����. ����� � ������� �� %d", povtor);             //������� ��� ������ ������ �� �����
	}
	else printf("\n������� ��������� �� �������");                                                    //���� �� ���� ������� ���������� ���������, �� ��������� �����                                                                                
	return result;
}