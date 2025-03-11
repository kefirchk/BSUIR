#include "Header.h"            //����������� ����������

int *poisk1(int n, person *man)  //������� ������ �����, � ������� ������ ����� � ������ ����� ����������� ������
{
	static int ms1[4] = {};
	int kmax = 0, kmin = 0;    //kmax, kmin - ������� ������� �������� 
	int flag1 = 0, flag2 = 0;  //flag1, flag2 - ������ (���� ����� ���� �� ����)
	for (int i = 0; i < n; i++)
	{
		if (man[kmax].money[3].BYN == man[i].money[3].BYN && kmax != i) flag1++;  //���� ������� �������, ������� ����� �������� ���� ��� ����� ������� �� ����������� ������
		if (man[kmax].money[3].BYN < man[i].money[3].BYN) kmax = i; //���� ������� ������� � ���������� ����������� ����������� �����
		if (man[kmin].money[3].BYN == man[i].money[3].BYN && kmin != i) flag2++; //���� ������� �������, ������� ����� �������� ���� ��� ����� ������ �� ����������� ������
		if (man[kmin].money[3].BYN > man[i].money[3].BYN) kmin = i;  //���� ������� ������� � ���������� ����������� ����������� ������
	}
	ms1[0] = kmax; //������ ��� ��������� ������ � ������
	ms1[1] = kmin;
	ms1[2] = flag1;
	ms1[3] = flag2;
	
	//����� �������������� ���������
	for (int i = 0, j = kmax; i<2 ; i++)
	{
		if (i > 0) j = kmin;
		man[0].result[i].age = man[j].age;
		man[0].result[i].BYN = man[j].money[3].BYN;
		strcpy_s(man[0].result[i].name, n2 * sizeof(char), man[j].name);
		strcpy_s(man[0].result[i].surname, n2 * sizeof(char), man[j].surname);
	}
	return ms1;    //���������� ��������� �� ������ ��������
}