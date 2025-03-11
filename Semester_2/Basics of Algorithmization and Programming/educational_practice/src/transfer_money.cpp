#include "Header.h"                        //����������� ����������

int transfer_fun(int sum, info* &pointer1, info* &pointer2, int k);  //������� ��������� ���� �� ����� ����������� � ����������

void transfer_money(info* head, info* tail, char* fileName, FILE* f) //������� �������� ����� �� ����� �� ����
{
	char name2[len], surname2[len];        //������ ��� ����� � ������� ����������
	file_in_str(tail, head, fileName, f);  //����� ������� �������� ���������� �� ����� � �������
	info* pointer1, *pointer2 = tail;      //��������� �� ����������� � ���������� ��������������
	printf("\n������� ������ ����������� ��������\n");
	if (pointer1 = input_PIN(tail))        //����� ������� ����� � ������� ������
	{
		while (1)
		{
			printf("\n������� ������ ���������� ��������");
			printf("%c[%d;%dm\n������� ���:%c[%dm\n", 27, 1, 33, 27, 0);
			strcpy_s(name2, input_str());  //����� ������� ����� ����� ����������
			printf("%c[%d;%dm\n������� �������:%c[%dm\n", 27, 1, 33, 27, 0);
			strcpy_s(surname2, input_str()); //����� ������� ����� �������
			while (pointer2)               //���� �� �������, ���� �� ������ ��������� ����������
			{
				if (!strcmp(pointer2->name, name2) && !strcmp(pointer2->surname, surname2)) break; //���� ��������� ������� �������
				pointer2 = pointer2->next; //������� � ���������� �������� �������
			}
			if (pointer2)                  //���� ��������� ������� �������
			{
				int temp = 0, k = currency_choice(); //��������� ����������; ����� ������� ������ ������
				temp = transfer_fun(sum_choice(), pointer1, pointer2, k); //����� ������� ��������� ���� �� ����� ����������� � ����������
				if (!temp)                 //���� �� ����� ����������� ������������ �������� ������� ��� �������� ����������� �����
				{
					printf("%c[%d;%dm������������ �������� ������� �� �������!%c[%dm\n", 27, 1, 31, 27, 0);
					return;
				}
				else replace_file(tail, fileName, f); //����� ������� ������ �����
				return;
			}
			printf("%c[%d;%dm\n�� ������� ����� ������ ��������!\n��������� ����%c[%dm\n", 27, 1, 31, 27, 0);
		}
	}
	else return;
}

int transfer_fun(int sum, info* &pointer1, info* &pointer2, int k) //������� ��������� ���� �� ����� ����������� � ����������
{
	if ((pointer1->cash[k].BYN -= sum)>=0) //���� �� ����� ����������� ���������� �������� �������
	{
		pointer2->cash[k].BYN += sum;      //��������� ����� ����� ����������
		return 1;
	}
	else pointer1->cash[k].BYN += sum;     //����������� � ��������� ����� ����� �� ����� �����������
	return 0;
}