#include "Headers.h"                                       //����������� ���������

char* memory_for_new_str(int num, char* &new_str)          //������� ��������� ������ ��� ������ new_str
{
	if (!(new_str = (char*)malloc((num+1) * sizeof(char))))//��������� ������ + �������� �� ��������� ������
	{
		printf("��� ��������� ������!");                   //����� �� ����� ������, ���� ������ �� ����������
		exit(0);                                           //���������� ���������
	}
	return new_str;                                        //����������� �������� new_str
}