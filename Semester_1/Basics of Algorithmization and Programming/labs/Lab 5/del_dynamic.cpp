#include "all_functions.h"

void del_dynamic(float** matrix, int* array) 
{
	for (int i = 0; i < array[0]; i++) free(matrix[i]);//������ ������ �� ���������� ��� ������
	free(matrix);                                      //������������ ������ �� ��������� �� ������ ����������  
	free(array);                                       //������������ ������ �� ������� �������� �������� �������
}