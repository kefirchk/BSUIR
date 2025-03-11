#include "Header.h" //����������� ����������
//#define dol 3.28;   //���� ������� �� 13.03.2022 22:53
//#define eur 3.58;   //���� ���� �� 13.03.2022 22:54
//#define rus 0.034;  //���� ����������� ����� �� 13.03.2022 22:54

long float perevod(person *man, int i) //������� �������� ����� � ����������� ����� � ������������ ����� ����� ���� �����
{
	static long float dol, eur, rus;
	if (!dol || !eur || !rus)
	{
		puts("������� ���� �������:");
		input_float(dol);
		puts("������� ���� ����:");
		input_float(eur);
		puts("������� ���� ���������� ������:");
		input_float(rus);
		return 0;
	}
	long float sum = man[i].money[3].BYN;       //��������� ����� ���� �����
	for (int j = 0; j < man[i].data[0].count; j++)
	{
		switch (man[i].data[1].mv[j])     
		{
		case 1: sum += man[i].money[0].dollar*dol; break; //������� ��������
		case 2: sum += man[i].money[1].euro*eur; break;   //������� ����
		case 3: sum += man[i].money[2].RUB*rus; break;    //������� ���������� ������
		case 4: break;
		default: puts("������!\n"); break;
		} 
	}
	return sum; //������� ����� ���� �����
}