#include "Header.h" //����������� ����������

void string_fix(char* stack, char *str, int index) //������� �������� ������������ ������
{
	do {
		correct_without_stack(stack, str, index); //����� ������� ����������� ������
		index = check_without_stack(str, 0);    //����� ������� �������� ����������� ������
		if (index < 0)
		{
			puts("\n������������ ������:");
			output_str(str, index); //����� ������� ������ ������
			break;
		}
	} while (1);
}

void stack_fix(stack *&head, char* &str, int index) //������� �������� ������������ ������
{
	char c = 0;
	do
	{
		puts("\n�������� �����:"
			"\n1 - ������� ������"
			"\n2 - ���������/�������� ������");
		c = _getch();
	} while (c != '1' && c != '2');
	if (c == '1') str = del(head, str, index); //����� ������� ����������� ������(������ 1)
	else str = add(head, str, index); //����� ������� ����������� ������(������ 2)
}