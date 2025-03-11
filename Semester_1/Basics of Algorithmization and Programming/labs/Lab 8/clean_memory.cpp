#include "Headers.h"                            //����������� ����������

//void clean_memory(char** &str, int &n, char* &new_str, char &choice)  //������� ������������ ������ �� ���������� �� ��������� � �� ������
//{
//	for (int i = 0; i < n; i++) free(*(str+i)); //������ ������ �� ���������� �� ������  
//	free(str);                                  //������� ������ �� ���������� �� ������ ���������� 
//	if(choice != '1') free(new_str);            //���� ��� new_str ���� �������� ������, �� ���������� �� 
//}

enum Type { Char, Int, Pointer2x, Pointer };
void clean_memory(enum Type t, ...);            // ���������� t ��������� �������� ���� enum Type

void clean_memory_param(char** &str, int &n, char* &new_str, char &choice)
{
	clean_memory(Pointer2x, str, Int, n, Pointer, new_str, Char, choice, '\0');   //��������� � ������� ������������ ������
}

void clean_memory(enum Type t, ...)      // ���������� t ��������� �������� ���� enum Type
{
	char choice = 0, *new_str = NULL, **str = NULL;
	int n = 0;
	void *p = &t;                      // ��� ��� � � ���������� ��������
	p = ((int *)p) + 1;
	puts("\n");
	switch (t)
	{
	case Char: while (*(char *)p) p = ((char*)p) + 1; break;
	case Int: while (*(int *)p) p = ((int*)p) + 1; break;
	case Pointer2x: while (*(char*)p) p = ((char***)p) + 1; break;
	case Pointer: while (*(char*)p) p = ((char**)p) + 1; break;
	}
	for (int i = 0; i < n; i++) free(*(str + i)); //������ ������ �� ���������� �� ������  
	free(str);                                    //������� ������ �� ���������� �� ������ ���������� 
	if (choice != '1') free(new_str);             //���� ��� new_str ���� �������� ������, �� ���������� �� 
}
