#include "Headers.h"                                               //����������� ����������

char recurs_stroki(char* &new_str)                  //������� ���������� ���� ���������� �� �� ������������� � ������ � ������� �����������
{                                    
	static int j;
	char letter = 0;
	letter = new_str[j];
	if(new_str[++j]!='\0') recurs_stroki(new_str);
	else return letter;
	puts(new_str);
}