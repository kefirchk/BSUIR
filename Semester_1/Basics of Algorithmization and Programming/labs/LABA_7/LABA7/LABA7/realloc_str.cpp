#include "Headers.h"                                           //����������� ����������

void realloc_str(int n, char** &str, int &size)                //������� ����������������� ������
{
	int j;                                                     //�������
	for (int i = 0; i < n; i++)                                //���� �� i ��� ������ �� �������
	{
		for (j = 0; (*(*(str + i) + j)) != '\0'; j++);         //���������� �������� ����� ������
		str = (char**)realloc(str, n * sizeof(char*));         //����������������� ������
		(*(str+i)) = (char*)realloc((*(str+i)), (j+1) * sizeof(char)); 
		(*(*(str + i) + j)) = '\0';                            //������������ � ����� ������ ������� \0
	}
}