#include "Headers.h"                               //����������� ����������

int lenght_strok(int n, char** str)      //������� ���������� ������ ����� ��� ������ new_str  
{
	static int num, i;                                       //������ ������ new_str
	int j;
	for (j = 0; (*(*(str + i) + j)) != '\0'; j++); //���� �� j ��� ���������� ����� ��������� ������
	num = num + j + 1;                             //���������� ������� ������
	i++;                                     //���������� ������� ������ �� 1, ��� ��� ��� j=0 ������ ������ �� ������������� ��� ��� �������� ����� �������
	if(i < n)lenght_strok(i, str);
	else return num;                         //����������� �������� num              
}