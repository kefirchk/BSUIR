#include "Headers.h"                             //����������� ����������

char add_offer(char choice)                       //������� ������, ������� ������ ���������� �� ���������� ���������  
{
	choice = 0;
	char symbol;                                 //���������� ������������� ����������
	printf("\n������ ����������?(y\\n)");        //����������� �� ����������� ���������� ���������
	rewind(stdin);                           //������ ������
	scanf_s("%c", &choice);                  //���� y ��� n(����� ��� ����������� ��� ���)
	scanf_s("%c", &symbol);                  //���� ���������� symbol ��� ���������� �������� 
	if (symbol == '\n' && (choice == 'y' || choice == 'n'))    //������� ������ �� �����
	{
		system("cls");                       //������ �������
		return choice;                               //����� �� �����
	}
	else {                                   //�����
		printf("������!\n");                 //����� �� ������
		add_offer(choice);
	}
}