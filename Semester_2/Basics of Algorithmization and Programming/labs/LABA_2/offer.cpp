#include "Header.h"                              //����������� ����������

int offer()  //������� ������, ������� ������ ���������� �� ���������� ���������  
{
	char symbol;                                 //���������� ������������� ����������
	printf("\n������ ����������?(y\\n)");        //����������� �� ����������� ���������� ���������
	for (;;) {
		rewind(stdin);                           //������ ������
		symbol = _getch();                       //���� y ��� n(����� ��� ����������� ��� ���)
		if (symbol == 'y' || symbol == 'n')      //������� ������ �� �����
		{
			system("cls");                       //������ �������
			break;                               //����� �� �����
		}
		else {                                   //�����
			printf("\n������!\n");               //����� �� ������
			printf("������ ����������?(y\\n)");
		}
	}
	if (symbol == 'n') return 0;                 //����� �� �����, ���� ����������� �������
	else return 1;
}