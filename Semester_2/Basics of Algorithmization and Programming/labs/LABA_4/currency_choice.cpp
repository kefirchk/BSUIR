#include "Header.h"    //����������� ����������

int* currency_choice(person *&man, int i, int count) //������� ������ ������
{
	puts("�������� ������, � ������� ����� ��������:\n"
		"1 - ������;\n"
		"2 - ����;\n"
		"3 - ���������� �����\n"
		"4 - ����������� �����");
	int t;  //��������� ����������
	for (int j = 0; j < count; j++)
	{
		man[i].data[1].mv[j] = input_int(1);  //����� ������� ������ ������ �� "1" �� "4"
		t = j;
		while (--t >= 0) if (man[i].data[1].mv[j] == man[i].data[1].mv[t]) { t = 5; break; } //�������� �� ���������� �����
		if (t == 5 || man[i].data[1].mv[j] == 0 || man[i].data[1].mv[j] > 4 || man[i].data[1].mv[j] < 1) //�������� �� ������������ �����
		{
			puts("Error! Please, try again");
			j--;
		}
	}
	return man[i].data[1].mv;          //������� ������ ������� ��������� �����
}