#include "Header.h"     //����������� ����������

int *poisk2(int n, person *&man, ripo *&result) //������� ������ ������ �������� � ������ ������� ��������
{
	static int ms2[4] = {};
	int kmax = 0, kmin = 0;   //������� ������� ��������
	int flag1 = 0, flag2 = 0; //flag1, flag2 - ������ (���� ����� ���� �� ����)
	for (int i = 0; i < n; i++)
	{
		if (perevod(man, kmax) == perevod(man, i) && kmax != i) flag1++; //���� ������� ����� �� ���������
		if (perevod(man, kmax) < perevod(man, i)) kmax = i; //���� ������� ������� ������, ���������� ��� ������
		if (perevod(man, kmin) == perevod(man, i) && kmin != i) flag2++; //���� ������� ����� �� ���������
		if (perevod(man, kmin) > perevod(man, i)) kmin = i; //���� ������� ������� ������, ���������� ��� ������
	}
	ms2[0] = kmax;      //������ ��������� �������� � ������
	ms2[1] = kmin;
	ms2[2] = flag1;
	ms2[3] = flag2;

	//����� �������������� ���������
	result[2].age = man[kmax].age;
	result[2].BYN = man[kmax].money[3].BYN;
	strcpy_s(result[2].name, n2, man[kmax].name);
	strcpy_s(result[2].surname, n2, man[kmax].surname);
	result[3].age = man[kmin].age;
	result[3].BYN = man[kmin].money[3].BYN;
	strcpy_s(result[3].name, n2, man[kmin].name);
	strcpy_s(result[3].surname, n2, man[kmin].surname);
	/*man[0].result[2].age = man[kmax].age;
	man[0].result[2].BYN = man[kmax].money[3].BYN;
	strcpy_s(man[0].result[2].name, n2, man[kmax].name);
	strcpy_s(man[0].result[2].surname, n2, man[kmax].surname);
	man[0].result[3].age = man[kmin].age;
	man[0].result[3].BYN = man[kmin].money[3].BYN;
	strcpy_s(man[0].result[3].name, n2, man[kmin].name);
	strcpy_s(man[0].result[3].surname, n2, man[kmin].surname);*/

	return ms2;         //���������� ��������� �� ������ ��������
}