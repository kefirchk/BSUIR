#include "Header.h"  //����������� ����������

void special_output(int k, word* ab, char* sl) //������� ������ ��������� �����
{
	if (!sl) return;
	int i = 0;      //�������
	for (; i < k; i++) 
		if (!strcmp(sl, ab[i].word)) //���� ������� ���������� 
		{ 
			output_result(i, ab, 1); //����� ������� ������ �� ����� ���������� ������
			break;                   //�������� ����
		}
	if (i == k) puts("�� ������� ����� ������ ����� � ���� ������");
}