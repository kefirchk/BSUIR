#include "Header.h"        //����������� ����������

int* mem_for_mv(person *man, int count, int i) //������� ��������� ������ ��� ������ ������� �����
{
	man[i].data[1].mv = (int*)calloc(count, sizeof(int)); //��������� ������
	if (!man[i].data[1].mv)        //���� ������ �� ����������
	{
		puts("������ ��������� ������");
		return NULL;
	}
	return man[i].data[1].mv;      //������� ��������� �� ������
}