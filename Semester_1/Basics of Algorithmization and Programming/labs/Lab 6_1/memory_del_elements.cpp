#include "Headers.h"                                     //����������� ����������

char* memory_del_elements(int n, char* str_del)           //������� ��������� ������ ��� ������ ��������� ���������
{
	str_del = (char*)malloc((n + 1) * sizeof(char));     //��������� ������ ��� ������ ��������� ���������
	if (str_del == NULL)                                 //�������� �� ��������� ������
	{
		puts("������ �� ��������!");
		exit(1);                                         //���������� ���������
	}
	return str_del;                                  
}