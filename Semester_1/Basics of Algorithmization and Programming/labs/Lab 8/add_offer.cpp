#include "Headers.h"                             //����������� ����������

int add_offer(char choice)                       //������� ������, ������� ������ ���������� �� ���������� ���������  
{
	choice = 0;
	char symbol;                                 //���������� ������������� ����������
	printf("\n������ ����������?(y\\n)");        //����������� �� ����������� ���������� ���������
	for (;;) {
		rewind(stdin);                           //������ ������
		scanf_s("%c", &choice);                  //���� y ��� n(����� ��� ����������� ��� ���)
		scanf_s("%c", &symbol);                  //���� ���������� symbol ��� ���������� �������� 
		if (symbol == '\n' && (choice == 'y' || choice == 'n'))    //������� ������ �� �����
		{
			system("cls");                       //������ �������
			break;                               //����� �� �����
		}
		else {                                   //�����
			printf("������!\n");                 //����� �� ������
			printf("������ ����������?(y\\n)");
		}
	}
	if (choice == 'n') return 1;                 //����� �� �����, ���� ����������� �������
}