#include "Header.h" //����������� ����������

person* input_info(int n, person* &man) //������� ����� ���������� � �����
{
	int k;
	for (int i = 0; i < n; i++)       //���� �� ����������
	{
		//���
		printf("\n������� ��� ��������: ");
		man = input_str(i, man, 1);   //����� ������� ����� �����

		//�������
		printf("\n������� ������� ��������: ");
		man = input_str(i, man, 0);   //����� ������� ����� �������

		//�������
		printf("\n������� ������� ��������(<120): ");
		man[i].age = input_int(1);

		//���������o ������
		puts("������� ��������� ������ ���� � ��������?(<5)");
		man[i].data[0].count = input_int(0);      //����� ������� ����� ���������� ������ 

		mem_for_mv(man, man[i].data[0].count, i); //��������� � ������� ��������� ������ ��� ������ ������� �����

		if (man[i].data[0].count) man[i].data[1].mv = currency_choice(man, i, man[i].data[0].count);  //����� ������� ������ ������

		//���� ������
		for (int j = 0; j < man[i].data[0].count; j++) 
		{ 
			switch (man[i].data[1].mv[j])
			{
			case 1: puts("������� ���������� ��������, ������� ���� � ��������: ");
				input_float(man[i].money[0].dollar); break;  //���� ��������
			case 2: puts("������� ���������� ����, ������� ���� � ��������: ");
				input_float(man[i].money[1].euro); break;    //���� ����
			case 3: puts("������� ���������� ���������� ������, ������� ���� � ��������: ");
				input_float(man[i].money[2].RUB); break;     //���� ���������� ������
			case 4: puts("������� ���������� ����������� ������, ������� ���� � ��������: ");
				input_float(man[i].money[3].BYN); break;     //����� ������� ����� ���������� ����������� ������
			default: printf("������! ��������� ����\n");     //���� ��������� �������������� �����
			}
		}
	}
	return man;  //������� ��������� �� ��������� 
}