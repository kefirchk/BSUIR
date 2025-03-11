#include "Header.h" //����������� ����������

char* add(stack *&head, char* str, int index) //������� ����������� ������ (������ 1)
{
	do {
		str = correct_option_1(head, str, index); //����� ������� ���������� ������ ������
		while (head) pop(&head); //�������� �����
		index = check_with_stack(head, str, 0); //�������� ������������ ������
		if (index < 0) //���� ������ ����������� ���������
		{
			puts("\n������������ ������:");
			output_str(str, index); //����� ������� ������ ������
			break;
		}
	} while (1);
	return str;
}

char* correct_option_1(stack* head, char* str, int index) //������� ���������� ������ ������
{
	int i = 0; //������� �� ������
	char temp[2*len + 1] = {}, b = 0, s; //��������� ������ � ����������
	switch (str[index])
	{
	case '(': case '[': case '{':
		switch (head->bracket)
		{
		case '(': b = ')'; break;
		case '[': b = ']'; break;
		case '{': b = '}'; break;
		}
		//������ ������ ����������� ������
		/*for (int i = (head->index) + 1, j = 0; str[i] != '\0'; i++)
			temp[j++] = str[i];
		str[(head->index) + 1] = b;
		for (int i = (head->index) + 2, j = 0; temp[j] != '\0'; i++)
			str[i] = temp[j++];*/
		while (str[i] != '\0') i++; //������� � ����� ������
		str[i] = b; //��������� ������ ������
		break;
	case ')': case ']': case '}':
		if (head)
		{
			switch (head->bracket)
			{
			case '(': str[index] = ')'; break;
			case '[': str[index] = ']'; break;
			case '{': str[index] = '}'; break;
			} break;
		}
		else
		{
			for (int i = 0; str[i] != '\0'; i++) //���� �� ������
			{
				switch (str[i])
				{
				case ')': case ']': case '}': push(&head, str[i], i); break; //���������� � ���� ����������� ������
				}
			}
			switch (head->bracket)
			{
			case ')': b = '('; break;
			case ']': b = '['; break;
			case '}': b = '{'; break;
			}
			i = 0;
			while (str[i] != '\0' && str[i] != ')' && str[i] != ']' && str[i] != '}') i++; //������� ��������
			int ii = i; //���������� ������, ���� ����� ����� �������� ������
			for (int j = 0; str[i] != '\0'; i++) //���� �� ������ ����� �������� ������ �� ���������
				temp[j++] = str[i];
			str[ii] = b; //��������� ������ ������
			for (int i = ii+1, j = 0; temp[j] != '\0'; i++) //������ ������������ ���������� �� ��������� ������ � ��������
				str[i] = temp[j++];
			pop(&head); //������� ������� �����
		}
		
	}
	return str;
}