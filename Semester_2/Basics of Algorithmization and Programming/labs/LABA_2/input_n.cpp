#include "Header.h" //����������� ����������

person* input_n_and_mem(int &n, person* man) //������� ����� ���������� ����� � ��������� ������ ��� ������ ��������
{
	int i, f = 0; char symbol; //������������� ���������� ��� �������� � �����
	while (1)
	{
		do
		{
			if (f++) puts("������!");
			rewind(stdin);                                //������ ������
			printf("������� ���������� �����: ");
			i = scanf_s("%d%c", &n, &symbol);             //���� ��������
		} while (n < 0 || !i || i < 1 || symbol != '\n'); //�������� ���������� ����� � ������������ �����

		//��������� ������ ��� ������ ��������
		man = (person*)calloc(n, sizeof(person));
		if (man == NULL)
		{
			puts("������! ������ �� ��������\n");
			exit(1);
		}
		else break;
	}
	return man;
}