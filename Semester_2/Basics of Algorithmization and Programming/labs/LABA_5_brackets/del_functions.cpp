#include "Header.h" //����������� ����������

char* del(stack *&head, char *str, int index) //������� ����������� ������(������ 2)
{
	do {
		correct_option_2(head, str, index); //����� ������� ����������� ������
		while (head) pop(&head);            //�������� �����
		index = check_with_stack(head, str, 0);   //����� ������� �������� ����������� ������
		if (index < 0)
		{
			puts("\n������������ ������:");
			output_str(str, index); //����� ������� ������ ������
			break;
		}
	} while (1);
	return str;
}

void correct_option_2(stack *&head, char* &str, int index) //������� ����������� ������ � ��������� � ������� �����
{
	int k = 0; //��������� ����������
	switch (str[index])
	{
	case ')': k = 1; break;
	case ']': k = 2; break;
	case '}': k = 3; break;
	}
	if (k) k = check2(head, index, str, k); //������� �������� � ����������� ������
	str = del_symbol(index, str); //���� ���� ������, �� ����� ������� �������� ������� � ������
}

int check2(stack* head, int index, char* str, int c) //������� �������� � ����������� ������
{
	char s1, s2, s3, s4;
	if (c == 1) { s1 = '['; s2 = '{'; s3 = ']'; s4 = '}'; }
	if (c == 2) { s1 = '('; s2 = '{'; s3 = ')'; s4 = '}'; }
	if (c == 3) { s1 = '('; s2 = '['; s3 = ')'; s4 = ']'; }
	if (head) //���� ���� �� ������
	{
		if (head->bracket == s1) str[index] = s3; //����������� �� ������ �� ������
		if (head->bracket == s2) str[index] = s4; //����������� �� ������ �� ������
		return 0;
	}
	return 1;
}