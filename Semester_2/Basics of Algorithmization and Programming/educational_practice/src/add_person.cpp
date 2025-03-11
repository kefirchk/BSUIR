#include "Header.h" //����������� ����������

void add_person(info** tail, info** head, char* fileName, FILE* f) //������� ���������� �������� � ������� � ����
{
	while (1)
	{
		info* pointer = (info*)calloc(1, sizeof(info)); //��������� ��� ������� �� ������� 
		if (!pointer)
		{
			printf("%c[%d;%dm������ �� ��������!%c[%dm\n", 27, 1, 31, 27, 0);
			return;
		}
		printf("%c[%d;%dm\n������� ���:%c[%dm\n", 27, 1, 33, 27, 0);
        strcpy_s(pointer->name, input_str());                             //���� �����
		printf("%c[%d;%dm\n������� �������:%c[%dm\n", 27, 1, 33, 27, 0);
		strcpy_s(pointer->surname, input_str());                          //���� �������
		pointer->cash[0].dollar = pointer->cash[1].euro = pointer->cash[2].RUB = pointer->cash[3].BYN = 0; //��������� ���� �����
		pointer->PIN = 1234;                                              //��������� ���-���
		//pointer->PIN = rand() % 9000 + 1000;
		printf("%c[%d;%dm\n��� PIN-���: %c[%dm%c[%d;%dm%d%c[%dm", 27, 1, 33, 27, 0, 27, 1, 32, pointer->PIN, 27, 0);
		if (!*tail || !*head) *tail = *head = pointer; //���� ������� �� �������
		else
		{
			pointer->next = *tail;      //���������� �������� � ����� �������
			*tail = pointer;            //������������� ������
		}
		printf("%c[%d;%dm\n����������?(y\\n)%c[%dm\n", 27, 1, 33, 27, 0);
		if (!offer())                   //����������� � ����������� ���������� �����
		{
			struct_in_file(fileName, f, *tail); //����� ������� ������ ��������� � ��������� ����
			return;
		}
	}
}