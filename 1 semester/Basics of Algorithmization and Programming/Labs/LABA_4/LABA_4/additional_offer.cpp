#include <stdio.h>                            //����������� ���������
#include <windows.h>

void additional_offer(char choice)            //������� ��� ������� �� ����������� ���������� ��������� 
{
	char symbol;
	printf("\n������ ����������?(y\\n)");     //����������� �� ����
	for (;;) {                                
		rewind(stdin);                        //������ ������
		scanf_s("%c", &choice);               //���� y ��� n(����� ��� ����������� ��� ���)
		scanf_s("%c", &symbol);               //���� ���������� symbol ��� ���������� �������� 
		if (symbol == '\n' && (choice == 'y' || choice == 'n'))   //������� ������ �� �����
		{
			system("cls");                    //������� ������
			break;                            //����� �� �����
		}
		else {
			printf("������!\n");              //����� �� ������
			printf("������ ����������?(y\\n)");
		}
	}
	if (choice == 'n') exit(0);               //������� ������ �� �����
}