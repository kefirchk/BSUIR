#include "Header.h" //����������� ����������

pupil* input_n_and_mem(int &n, pupil *info) //������� ����� ���������� �������� � ��������� ������ ��� ������ ��������
{
	int i; char c;
	while (1)
	{
		do {
			rewind(stdin);            //������ ������
			printf("������� ���������� ��������: ");
			i = scanf_s("%d%c", &n, &c);    //���� ��������
		} while (i<2 || i < 1 || c!='\n');          //���� ���������� �������� � �������� �� ������������ �����

		//��������� ������ ��� ������ ��������
		info = (pupil*)calloc(n, sizeof(pupil));
		if (info == NULL)
		{
			puts("������! ������ �� ��������\n");
			exit(1);
		}
		else break;
	}
	return info;
}