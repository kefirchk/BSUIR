#include "Header.h"

person *memory_struct(person *&man, int n) 	//������� ��������� ������ ��� ������ ��������
{
	man = (person*)calloc(n, sizeof(person)); //��������� ������
	if (!man) //���� ������ �� ��������
	{
		puts("������! ������ �� ��������\n");
		exit(1);
	}
	return man;
}