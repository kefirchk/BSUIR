#include "Headers.h"                   //����������� ����������

void recurs_stroki(char* &new_str)     //������� ���������� ���� � ������ � ������� ��������
{
	static int j;                      //�������
 	if ((*(new_str+j)) != '\0')        //������ �� ������
	{
		j++;
		recurs_stroki(new_str);        //��������
	}
	else return;
	printf("%c", new_str[--j]);        //����� ��������
}