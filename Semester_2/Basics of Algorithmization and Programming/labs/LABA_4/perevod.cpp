#include "Header.h" //����������� ����������
//#define dol 3.28;   //���� ������� �� 13.03.2022 22:53
//#define eur 3.58;   //���� ���� �� 13.03.2022 22:54
//#define rus 0.034;  //���� ����������� ����� �� 13.03.2022 22:54

double perevod(person *man, int i) //������� �������� ����� � ����������� ����� � ������������ ����� ����� ���� �����
{
	static double dol, eur, rus;
	if (i < 0) dol = eur = rus = 0;
	if (!dol || !eur || !rus)
	{
		printf("\n������� ���� �������: ");
		input_float(dol);
		printf("������� ���� ����: ");
		input_float(eur);
		printf("������� ���� ���������� ������: ");
		input_float(rus);
		return 0;
	}
	double sum = man[i].money[3].BYN;       //��������� ����� ���� �����
	//for (int j = 0; j < 4; j++)                 //man[i].data[0].count
	//{
		switch (man[i].data[1].mv[0])
		{
		case 0: case 1: case 2: case 3: 
		sum = sum + man[i].money[0].dollar*dol + man[i].money[1].euro*eur + man[i].money[2].RUB*rus; break;
		//case 1: sum += man[i].money[0].dollar*dol; break; //������� ��������
		//case 2: sum += man[i].money[1].euro*eur; break;   //������� ����
		//case 3: sum += man[i].money[2].RUB*rus; break;    //������� ���������� ������
		case 4: break;
		default: puts("������!\n"); break;
		}
	//}
	return sum; //������� ����� ���� �����
}