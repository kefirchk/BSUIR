#include "Headers.h"                              //����������� ����������

char* memory_s(int &n, char* &str_s)              //������� ��������� ������ ��� ������ s-��������
{
	str_s = (char*)malloc((n + 1)* sizeof(char)); //��������� ������
	if (str_s == NULL)                            //�������� �� ������� ���������
	{
		printf("������ �� ��������!");            //����� ������ �� ������
		exit(1);                                  //���������� ���������
	}
	return str_s;                                 //����������� ��������
}