#include "Headers.h"                                //����������� ����������

int input_n(int, ...)                   //������� ����� ������� �����
{
	int n=0; char choice=0;
	char symbol;                                    //���������� ��������� ����������
	for (;;)                                        //���� ��� ����� ���������� �����
	{
		rewind(stdin);                              //������� ������
		printf("������� ���������� ����� n:\n");    //����������� �� ���� ���������� ����� 
		int check = scanf_s("%d%c", &n, &symbol);   //���� ���������� ����� ������
		if (check == 2 && symbol == '\n') {         //�������� ��� �����
			if (n <= 0)                             //���� �������� ���������� ����� <= 0
			{
				printf("������! ������� �� ����������� �����.\n");    //����� �� ����� ������
				for (;;) {
					printf("������ ������ n ��� ���?(y\\n)");         //����� �� ����� ������
					rewind(stdin);                                    //������ ������
					scanf_s("%c", &choice);                           //���� y ��� n(����� ��� ����������� ��� ���)
					scanf_s("%c", &symbol);                           //���� ���������� symbol ��� ���������� ��������
					if (choice == 'y' && symbol == '\n') break;       //��� ����������� ������� ��� ���������� choice ��������� ����� �� �����
					else if (choice == 'n' && symbol == '\n') exit(0);//���� ������� "n", �� ����� ���������
					else printf("������!\n");                         //����� �� ������
				}
			}
			else break;                                               //����� �� �����
		}
		else printf("������! ���������� ��� ���.\n");                 //����� ������ �� ������
	}
	return n;                                                         //����������� �������� n
}