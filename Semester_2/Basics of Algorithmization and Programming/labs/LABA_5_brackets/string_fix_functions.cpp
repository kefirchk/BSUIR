#include "Header.h" //����������� ����������

int check_without_stack(char *str, int c) //������� �������� ����������� ������ � ��������� ��� ������������� �����
{
	int n = 0, index = -1; //n - c������, index - ������ ������������� �������
	char stack[len] = { }, b = 0; //�������������� ������, ������������ ��� ����
	for (int i = 0; str[i] != '\0'; i++)
	{
		while (str[i] != '(' && str[i] != ')' && str[i] != '[' &&    //������� ��������, 
			str[i] != ']' && str[i] != '{' && str[i] != '}' && str[i] != '\0') i++; //���� �� �������� �����-���� ������
		if (!n && (str[i] == ')' || str[i] == ']' || str[i] == '}')) //���� ������ ���� ����������� ������
		{
			if (c)printf("%c[%d;%dm\n������ ����������� �����������!%c[%dm\n", 27, 1, 31, 27, 0);
			return i;      //������� ������ ���������� ������
		}
		else
		{
			switch (str[i])
			{
			case '(': case '[': case '{': if (index < 0) index = i;  stack[n++] = str[i]; break; //�������� � ����
			case ')': b = '('; break;
			case ']': b = '['; break;
			case '}': b = '{'; break;
			}
		if ((stack[--n] != b && n) || (stack[n] != b && !n)) //�������������� ������
		{ 
			if (c)printf("%c[%d;%dm\n������ ����������� �����������!%c[%dm\n", 27, 1, 31, 27, 0);
			return i;
		}
	}
	}
	if (!n) { //���� ������� ����� ���� (���� ����)
		if (c)printf("%c[%d;%dm\n��� ���������!%c[%dm\n", 27, 1, 32, 27, 0);
		return -1;
	}
	else { //���� �� ����
		if (c)printf("%c[%d;%dm\n������ ����������� �����������!%c[%dm\n", 27, 1, 31, 27, 0);
		return index;
	}
}

void correct_without_stack(char *stack, char *str, int index) //������� ����������� ������ � ��������� ��� �����
{
	int k = 0; //��������� ����������
	switch (str[index])
	{
	case ')': k = 1; break;
	case ']': k = 2; break;
	case '}': k = 3; break;
	}
	if (k) k = check1(stack, index, str, k); //����� ������� �������� � ����������� ������
	str = del_symbol(index, str); //����� ������� �������� ������� � ������
}
int check1(char* stack, int index, char* str, int c) //������� �������� � ����������� ������
{
	char s1, s2, s3, s4;
	if (c == 1) { s1 = '['; s2 = '{'; s3 = ']'; s4 = '}'; }
	if (c == 2) { s1 = '('; s2 = '{'; s3 = ')'; s4 = '}'; }
	if (c == 3) { s1 = '('; s2 = '['; s3 = ')'; s4 = ']'; }
	if (strlen(stack)) //���� ����-c����� �� ������
	{
		int i = len - 1;
		while (stack[i] == '\0') i--;  //������� � ����� ������ (�� ������� �����)
		if (stack[i] == s1) str[index] = s3; //����������� �� ������ �� ������
		if (stack[i] == s2) str[index] = s4; //����������� �� ������ �� ������
		return 0;
	}
	return 1;
}
