#include "Header.h"   //����������� ����������

int special_order(int k, word* ab) //�������, ������� ���������� ������� ����� ����� �� ��������� ��������
{
	char c, *sl;     //��������� ����������
	while (1) {
		puts("���������� �����-�� ��������� �����?(y\\n)");
		while (1)
		{
			if ((c = _getch()) == 'y') //���� "y" - ��
			{
				puts("������� �������� �����:");
				sl = input_word(0);         //����� �����
				special_output(k, ab, sl);  //��������� � ������� ������ ��������� �����
				break;                 //�������� ����
			}
			else if (c == 'n') return 0; //���� "n" - ���
			else puts("Error! Please, try again");
		}
	}
	return 0;        //������� 0
}