#include "Headers.h"                            //����������� ����������

void clean_memory(char** &str, int &n, char* new_str, char &choice)  //������� ������������ ������ �� ���������� �� ��������� � �� ������
{
	for (int i = 0; i < n; i++) free(*(str+i)); //������ ������ �� ���������� �� ������  
	free(str);                                  //������� ������ �� ���������� �� ������ ���������� 
	if(choice != '1') free(new_str);            //���� ��� new_str ���� �������� ������, �� ���������� �� 
}