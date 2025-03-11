#include "Header.h"      //����������� ����������

pupil* input(int i, pupil *info1, int choice)    //������� ����� ������
{
	int j = 0;    //�������
	char c;       //������������� ���������� ��� ������ � ��������
	do
	{
		c = _getche(); //���� �������
		if (choice) (info1 + i)->imya[j] = c; //���� ������ ���
		else (info1 + i)->familia[j] = c;       //���� ������ �������
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '�' && c <= '�') || (c >= '�' && c <= '�') || c == ' ');
		else if (c == '\b') //������ ������� Backspace
		{
			if (j > 0) { printf(" \b \b"); j--; }      //������ ������� Backspace
			else printf(" ");
			j--;
		}
		else if (c == '\r') break; //���� ����� Enter
		else
		{
			puts("\n�������� �� ��������� ������.");
			puts("����������, ��������� ����:");
			j = -1;                       //����� ������ ���� ������
			rewind(stdin);              //������ ������
		}
	} while (j++ < 20);
	if (choice) (info1 + i)->imya[j] = '\0';  //���� ������ ���
	else (info1 + i)->familia[j] = '\0';      //���� ������ �������
	return info1;
}