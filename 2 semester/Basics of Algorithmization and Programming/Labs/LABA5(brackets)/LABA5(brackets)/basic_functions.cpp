#include "Header.h"      //����������� ����������

char choose_option() //������� ������ ������ ������ ���������
{
	char c = 0;
	while (1)
	{
		puts("�������� ����� ������:");
		printf("%c[%d;%dm0 - �������� ��� �����%c[%dm\n", 27, 1, 34, 27, 0);
		printf("%c[%d;%dm1 - �������� �� ������%c[%dm\n", 27, 1, 34, 27, 0);
		printf("%c[%d;%dm2 - �����%c[%dm\n", 27, 1, 34, 27, 0);
		c = _getch(); //���� ��������
		if (c == '0' || c == '1' || c == '2') break;
		else printf("%c[%d;%dm\n������ �����!\n��������� ����� ������ ������%c[%dm\n", 27, 1, 31, 27, 0);
	}
	return c; //������� ��������� ������
}

char* input_str(char choice)  //������� ����� ������
{
	if (choice == '2') exit(0);
	int j = 0;    //�������
	static char sl[2*len+1] = {};         //������ ��� ������ �����
	char c;       //������������� ���������� ��� ������ � ��������
	puts("\n������� ���������:");
	do
	{
		rewind(stdin);    //������ ������
		c = _getche();    //���� �������
		sl[j] = c;        //���� ������ ��� �����
		if (c == '\b')                            //������ ������� Backspace
		{
			if (j > 0) { printf(" \b \b"); j--; } //������ ������� Backspace
			else printf(" ");
			j--;
		}
		else if (c == '\r') break;  //���� ����� Enter
	} while (j++ < len - 1);
	sl[j] = '\0';
	return sl;                      //������� ������
}

void output_str(char *str, int index)    //������� ������ �������� ������
{
	for (int i = 0; str[i] != '\0'; i++) //���� �� ����������������� ������ �������� ������
	{
		if (i == index)	printf("%c[%d;%dm%c%c[%dm", 27, 1, 31, str[i], 27, 0); //����� �������, ��� �������� ������
		else printf("%c", str[i]);       //����� ���������� �������
	}
	printf("\n"); //����� ������
}

int offer()  //������� ������, ������� ������ ���������� �� ���������� ���������  
{
	char s;                                 //���������� ������������� ����������
	for (;;)
	{
		rewind(stdin);                      //������ ������
		s = _getch();                       //���� y ��� n(����� ��� ����������� ��� ���)
		if (s == 'y' || s == 'n') break;    //����� �� �����
		else {                              //�����
			puts("\n������!");              //����� �� ������
			printf("������ ����������?(y\\n)\n");
		}
	}
	if (s == 'n') return 0;                 //����� �� �����, ���� ����������� �������
	else return 1;
}

char* del_symbol(int index, char* str) //������� �������� ������� � ������
{
	int i; //������
	for (i = index + 1; str[i] != '\0'; i++) //���� ��� ����������� �� ������ �� ������� ��������
		str[i - 1] = str[i];
	str[--i] = '\0';
	return str; //������� ������
}

void save(char* &strcopy, char* &str)  //������� ���������� ��������� � ������
{
	puts("��������� ���������?(y\\n)");
	if (!offer()) str = strcopy;
	printf("���� ������: %s\n\n", str);
}