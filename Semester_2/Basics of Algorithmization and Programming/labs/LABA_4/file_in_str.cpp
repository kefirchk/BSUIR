#include "Header.h"   //����������� ����������

int file_in_str(person* &man, char* name, FILE *f, char fileOpen) //������� �������� ���������� �� ����� � ������ �����
{
	errno_t ff;
	if(fileOpen == '0') ff = fopen_s(&f, name, "rt"); //�������� ����� ��� ������
	else ff = fopen_s(&f, name, "rb");
	if (!checkFileOpen(ff)) return 0;                   //�������� �� �������� �����
	int size = 0;                //���������� ����� � �����
	int len = _filelength(_fileno(f));
	size = len / sizeof(person);
	if (size)
	{
		man = memory_struct(man, size); //��������� ������ ��� ���������
		if (fileOpen == '1')
			binary_file_in_str(size, f, man); //����� ������� �������� ���������� �� ��������� ����� � ��������
		else
			text_file_in_str(size, f, man); //����� ������� �������� ���������� �� ���������� ����� � ���������
	}
	else puts("���� ����");
	fclose(f);    //������� ����
	return size;  //������� ������ ������� ��������
}

void binary_file_in_str(int size, FILE *f, person *&man) //������� �������� ���������� �� ��������� ����� � ���������
{
	for (int i = 0; i < size; i++)
	{
		fread(man + i, sizeof(person), 1, f); //������ ��������� ���������
		fscanf_s(f, "\n");
	}
}

void text_file_in_str(int size, FILE *f, person *&man) //������� �������� ���������� �� ���������� ����� � ���������
{
	for (int i = 0; i < size; i++)
	{
		fread(man[i].name, n2, 1, f);    //������ ���
		fread(man[i].surname, n2, 1, f); //������ �������
		fscanf_s(f, "%d%lf%lf%lf%lf\n",  //������ �������� � ������ �� �����
			&man[i].age, &man[i].money[0].dollar, &man[i].money[1].euro, &man[i].money[2].RUB, &man[i].money[3].BYN);
	}
}