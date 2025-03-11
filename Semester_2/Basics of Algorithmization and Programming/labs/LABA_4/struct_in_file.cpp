#include "Header.h"   //����������� ����������

int checkFileOpen(errno_t ff); //������� �������� ����� �� ��������

void struct_in_binary_file(char* name, FILE *f, person* man, char choice, int n) //������� ������ ��������� � �������� ����
{
	errno_t ff;
	if (choice == '3') ff = fopen_s(&f, name, "w+b"); //�������� ����� ��� ������ ����������
	if (choice == '1') ff = fopen_s(&f, name, "a+b"); //�������� ����� ��� �������� ����� ���������� � ����
	if (!checkFileOpen(ff)) return;                  //�������� �� �������� �����
	for (int i = 0; i < n; i++)                      //���� �� ����������� ���������� � ����
	{
		fwrite(man + i, sizeof(person), 1, f);       //������ ��������� ��������� � ����
		fprintf(f, "\n");
	}
	fclose(f);
}

void struct_in_text_file(char* name, FILE *f, person* man, char choice, int n) //������� ������ ��������� � ��������� ����
{
	errno_t ff;
	if (choice == '3') ff = fopen_s(&f, name, "w+t"); //�������� ����� ��� ������ ����������
	if (choice == '1') ff = fopen_s(&f, name, "a+t"); //�������� ����� ��� �������� ����� ���������� � ����
	if (!checkFileOpen(ff)) return;                  //�������� �� �������� �����
	for (int i = 0; i < n; i++)                      //���� �� ����������� ���������� � ����
	{
		fwrite(man[i].name, n2, 1, f);    //������ � ���� �����
		fwrite(man[i].surname, n2, 1, f); //������ � ���� �������
		fprintf(f, "%-10d%-15.2lf%-15.2lf%-15.2lf%-15.2lf\n", //������ �������� � ����� � ����
			man[i].age, man[i].money[0].dollar, man[i].money[1].euro, man[i].money[2].RUB, man[i].money[3].BYN);
	}
	fclose(f);
}

int checkFileOpen(errno_t ff) //������� �������� ����� �� ��������
{
	if (ff)
	{
		puts("���� �� ����� ���� ������");
		return 0;
	}
	return 1;
}