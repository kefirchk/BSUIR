#include "Header.h"      //����������� ����������

char* input_str(int i, person *&man, int choice)    //������� ����� ������
{
	int j = 0;    //�������
	static char sl[n2] = {}, name[n2];         //������ ��� ������ �����
	if (choice == 2 && i > -1) puts("������� �������� �����:"); //����������� �� ����� �������� �����
	char c;       //������������� ���������� ��� ������ � ��������
	do
	{
		c = _getche();   //���� �������
		if (choice == 1) man[i].name[j] = c;         //���� ������ ���
		if (!choice) man[i].surname[j] = c; //���� ������ �������
		if (choice == 2 && i > -1) sl[j] = c;        //���� ������ ��� �����
		else if(choice == 2 && i ==-1) name[j] = c;
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
			(c >= '�' && c <= '�') || (c >= '�' && c <= '�') ||
			(c >='0' && c<='9') || c == ' ' || c == '_' || c == '.');
		else if (c == '\b')                     //������ ������� Backspace
		{
			if (j > 0) { printf(" \b \b"); j--; }   //������ ������� Backspace
			else printf(" ");
			j--;
		}
		else if (c == '\r') break;              //���� ����� Enter
		else
		{
			puts("\n�������� �� ��������� ������.");
			puts("����������, ��������� ����:");
			j = -1;                             //����� ������ ���� ������
			rewind(stdin);                      //������ ������
		}
	} while (j++ < n2-1);
	if (choice == 1) (man + i)->name[j] = '\0'; //���� ������ ���
	if (!choice) (man + i)->surname[j] = '\0';  //���� ������ �������
	if (choice == 2 && i > -1) { sl[j] = '\0'; return sl; }    //���� ������ ��� �����
	else if (choice == 2 && i == -1) { name[j] = '\0'; return name; } //���� ������ ���/�������
}