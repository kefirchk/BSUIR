#include "Header.h"            //����������� ����������

void test2(char choice, char *&str) //������� ������� �������� � ����������� ������ � ��������� � ������� �����
{
	if (choice != '1') return; //���� ������ ������ ����� ������
	int index;                 //������ ������������ ������
	stack *head = NULL;        //��������� �� ������� �����
	index = check_with_stack(head, str, 1); //����� ������� �������� ����������� ������
	puts("�������� ������:");
	output_str(str, index);    //����� ������� ������ �������� ������
	printf("\n");
	if (index > -1)
	{
		char strcopy[len+1] = {}, *s; //���. ������
		strcpy_s(strcopy, str);       //����������� �������� ������
		char c;
		while (1)
		{
			puts("�������� ��������:");
			printf("%c[%d;%dm0 - ��������� ������ �������%c[%dm\n", 27, 1, 34, 27, 0);
			printf("%c[%d;%dm1 - ��������� ������ �������������%c[%dm\n", 27, 1, 34, 27, 0);
			printf("%c[%d;%dm2 - �������� ��� ���������%c[%dm\n", 27, 1, 34, 27, 0);
			switch (c = _getch())
			{
			case '0': str = input_str('1');  //����� ������� ����� ������
				index = check_with_stack(head, str, 1);   //����� ������� �������� ����������� ������
				if (index > -1) continue;
			case '1': stack_fix(head, str, index); break; //����� ������� �������� ������������ ������
			case '2': break;
			default: puts("������ ������ ��������!"); continue;
			} 
			s = strcopy;
			if (c != '2') save(s, str);  //����� ������� ���������� ��������� � ������
			break;
		}
	}
}