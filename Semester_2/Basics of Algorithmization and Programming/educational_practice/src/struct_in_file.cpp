#include "Header.h"                        //����������� ����������

void struct_in_file(char* name, FILE *&f, info* pointer) //������� ������ ��������� � ��������� ����
{
	errno_t ff = fopen_s(&f, name, "a+t"); //�������� ����� ��� ������ ����������
	if (ff)                                //�������� �� �������� �����
	{
		printf("%c[%d;%dm\n���� �� ����� ���� ������!%c[%dm\n", 27, 1, 31, 27, 0);
		return;
	}
	while (pointer)                        //���� �� ����������� ���������� � ����
	{
		fprintf(f, "%-15s%-15s", pointer->name, pointer->surname); //������ ����� � �������
		fprintf(f, "%-10d%-10d%-10d%-10d%-10d\n", //������ �������� ���������� � ����
			pointer->PIN, pointer->cash[0].dollar, 
			pointer->cash[1].euro, pointer->cash[2].RUB, pointer->cash[3].BYN);
		pointer = pointer->next;           //������� � ��������� ��������� �������
	}
	fclose(f);                             //�������� �����
}