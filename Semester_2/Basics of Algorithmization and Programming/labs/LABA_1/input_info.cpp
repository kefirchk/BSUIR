#include "Header.h" //����������� ����������

pupil* input_info(int n, pupil* info1) //������� ����� ���������� � ��������
{
	int �;                            //��������� ����������
	for (int i = 0; i < n; i++)       //���� �� ����������
	{
		rewind(stdin);                //������ ������

		//���
		printf("\n������� ��� �������: ");
		info1 = input(i, info1, 1);     //����� ������� ����� �����

		//�������
		printf("\n������� ������� �������: ");
		info1 = input(i, info1, 0);     //����� ������� ����� �������

		//�����
		do {
			rewind(stdin);            //������ ������
			printf("\n������� ����� ���������(<12): ");
			� = scanf_s("%d%c", &info1[i].clas, &info1[i].letter);  //���� ������
		} while (�<2 || info1[i].clas > 11 || info1[i].clas < 1);    //���� ����� � ����� ������
	}
	return info1;
}