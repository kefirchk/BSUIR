#include "Header.h"   //����������� ����������

void realloc_ms1(int *&ms1, int size)    //������� ����������������� ������ ��� ������� ��������
{
	ms1 = (int*)realloc(ms1, size * sizeof(int)); //����������������� ������
	if (!ms1) //����� �������� ������
	{
		if (size) puts("������ ��������� ������\n");
		return;
	}
}