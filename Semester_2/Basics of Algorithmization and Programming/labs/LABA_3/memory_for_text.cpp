#include "Header.h"    //����������� ����������

char** memory_for_text(char **&str, int size) //������� ��������� ������ ��� �������� �����
{
	str = (char**)calloc(size, sizeof(char*));
	if (!str)          //���� ������ �� ��������
	{
		puts("Memory allocation error!\n");
		return 0;
	}
	for (int i = 0; i < size; i++)
	{
		str[i] = (char*)calloc(n2+1, sizeof(char)); //��������� ������ ��� �������� �����
		if (!str[i])   //���� ������ �� ��������
		{
			while (--i >= 0) free(str[i]); //������������ ������ �� ���������� ������� ������� ��������� ������ ��� ������
			free(str); //������������ ������ �� ��������� �� ������ ���������� �� ������
			puts("Memory allocation error!\n");
			return 0;
		}

	}
	return str;        //������� ��������� �� ������ ����������
}