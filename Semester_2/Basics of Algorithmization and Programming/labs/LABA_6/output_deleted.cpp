#include "Header.h"                        //����������� ����������

void output_deleted(people* tailDeleted)   //������� ������ ������ ���������� �����
{
	if (!tailDeleted)
	{
		puts("\n������ ���������� ����� ����!");
		return;
	}
	people* ptr = tailDeleted;             //��������� �� ����� ������ ���������� �����
	int k = 0;                             //�������
	printf(" ");
	while (k++ < 58) printf("_");          //����� ������� ������� �������
	printf("\n|���\t\t|�������        |���������      |������    |\n|"); //����� "�����"
	k = 56;
	while (k-- > 1)                        //���������� ������� ������� �������
	{
		if (k == 10 || k == 25 || k == 40) printf("|");
		printf("_");
	}
	while (ptr)                            //���� �� ������ ����������
	{
		printf("|\n|%-15s|%-15s|%-15s|%-10d", ptr->name, ptr->surname,
			ptr->faculty, ptr->group);
		ptr = ptr->next_person;
	}
	printf("|\n|");
	while (k++ < 55)                       //������� ������ ������� �������
	{
		if (k == 16 || k == 31 || k == 46) printf("|");
		printf("_");
	}
	puts("|");
}