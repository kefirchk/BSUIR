#include "Header.h"      //����������� ����������

person* input_str(int i, person *man, int choice)    //������� ����� ������
{
	int j = 0;    //�������
	char c;       //������������� ���������� ��� ������ � ��������
	do
	{
		c = _getche();   //���� �������
		if (choice) man[i].name[j] = c;   //���� ������ ���
		else man[i].surname[j] = c;       //���� ������ �������
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '�' && c <= '�') || (c >= '�' && c <= '�') || c == ' ');
		else if (c == '\b')                   //������ ������� Backspace
		{
			if (j > 0) { printf(" \b \b"); j--; }   //������ ������� Backspace
			else printf(" ");
			j--;
		}
		else if (c == '\r') break;            //���� ����� Enter
		else
		{
			puts("\n�������� �� ��������� ������.");
			puts("����������, ��������� ����:");
			j = -1;                           //����� ������ ���� ������
			rewind(stdin);                    //������ ������
		}
	} while (j++ < 14);
	if (choice) (man + i)->name[j] = '\0';    //���� ������ ���
	else (man + i)->surname[j] = '\0';        //���� ������ �������
	return man;                               //������� ��������� �� ������ ��������
}