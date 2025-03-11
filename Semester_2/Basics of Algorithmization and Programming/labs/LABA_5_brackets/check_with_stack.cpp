#include "Header.h"

int check_with_stack(stack *&head, char *str, int c) //������� �������� ����������� ������ � �������������� �����
{
	int j, index = -1; //j - ������� ����, ��� ����� ������� ������� �����, index - ������ ������
	//stack *head = NULL, *pointer;
	for (int i = 0; str[i] != '\0'; i++)
	{
		switch (str[i])
		{
		case '(': case '[': case '{': if (index < 0) index = i; push(&head, str[i], i); break; //�������� ������ � ����
		case ')': case ']': case '}':
			if (!head)    //���� ���� ����
			{
				error(head, c); //����� ������� ������ ������ �� ������ � ��������� �����
				return i; //������� ������ ������������ ������
			}
			else
			{
				j = 0;    //�������� ������
				switch (str[i])
				{
				case ')': if (head->bracket == '(') j = 1; break; //���� ��� ���������, �� j = 1;
				case ']': if (head->bracket == '[') j = 1; break;
				case '}': if (head->bracket == '{') j = 1; break;
				}
			}
			if (j) pop(&head); //����� ������� �������� �������� � ������� �����
			//pointer = head; head = head->next; free(pointer);
			else {
				error(head, c); //����� ������� ������ ������ �� ������ � ��������� �����
				return i;      //������� ������ ������������ ������
			}
		}
	}
	if (head) { //���� ���� � ����� �������� �� ������
		error(head, c); //����� ������� ������ ������ �� ������ � ��������� �����
		return index;
	}
	else {     //���� ���� � ����� ����
		if (c)printf("%c[%d;%dm\n��� ���������!%c[%dm\n", 27, 1, 32, 27, 0);
		return -1;
	}
}

void error(stack *head, int c) //������� ������� ����� �� ������ � ��������� �����
{
	if (c) {
		printf("%c[%d;%dm\n������ ����������� �����������!%c[%dm\n", 27, 1, 31, 27, 0);
		printf("\n����������� ����?(y\\n)\n");
		if (offer()) show(head); //����������� ������� ����
	}
}