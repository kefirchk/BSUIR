#include "Header.h" //����������� ����������

char* input_word(int choice)       //������� ����� �����
{
	if(choice) puts("������� �������� �����:"); //����������� �� ����� �������� �����
	static char sl[n2 + 1] = {};   //������ ��� ������ �����
	char c;                        //��������� ����������
	int j = 0;                     //�������
	do
	{
		c = _getche();             //���� �������
		sl[j] = c;                 //������ ������� � ������ ��������
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '�' && c <= '�') ||
			(c >= '�' && c <= '�') || (c >= '0' && c <= '9') || c == '_' || c == '.');
		else if (c == '\b')        //������ ������� Backspace
		{
			if (j > 0) { printf(" \b \b"); j--; }   //������ ������� Backspace
			else printf(" "); j--;
		}
		else if (c == '\r') break; //���� ����� Enter
		else
		{
			puts("\n�������� �� ��������� ������.");
			puts("����������, ��������� ����:");
			j = -1;                //����� ������ ���� ������
		}
	} while (j++ < n2);
	sl[j] = '\0';
	return sl;                     //������� ������
}