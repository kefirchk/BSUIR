#include "Header.h" //����������� ����������

void show_file(char choice, FILE *f, char* name, person* man) //������� ��������� �����
{
	char c;         //��������� ����������
	int size = 0;   //�����, �� ������� �������� ������ ��� ��������
	errno_t ff;
	if (choice == '1') ff = fopen_s(&f, name, "rb"); //�������� ��������� ����� ��� ������
	else ff = fopen_s(&f, name, "rt");   //�������� ��������� ����� ��� ������
	if (ff) { puts("\n���� �� ����� ���� ������"); return; }
	while (1)       //���� �� �������� ���������� �������� � �����
	{
		fscanf_s(f, "%c", &c); //���������� ���������� ������� � �����
		if (feof(f)) break; //���� ����� �����
		if(c == '\n') size++;
	}
	rewind(f);      //���������� ����
	if (size) 
	{
		man = memory_struct(man, size); //��������� ������ ��� ���������
		int k = 0;
		//������� ������� ������� �������
		printf(" ");
		while (k++ < 110) printf("_");
		//����� "�����"
		printf("\n|���\t\t     ");
		printf("�������   ");
		printf("          �������");
		printf("   �������");
		printf("        ����");
		printf("           ���. �����");
		printf("     ���. �����     |\n");
		//���������� ������� ������� �������
		printf("|");
		while (k-- > 1) printf("_");
		printf("|");
		for (int i = 0; i < size; i++)
		{
			if (choice == '1')
			{
				fread(man + i, sizeof(person), 1, f); //������ ����� ��� ���������
				fscanf_s(f, "\n");
			}
			printf("\n|%-20s", man[i].name);     //������� ���
			printf("%-20s", man[i].surname);     //������� �������
			printf("%-10d%-15.2lf%-15.2lf%-15.2lf%-15.2lf|", man[i].age, man[i].money[0].dollar, man[i].money[1].euro, man[i].money[2].RUB, man[i].money[3].BYN);
		}
		//������� ������ ������� �������
		printf("\n|");
		while (k++ < 110) printf("_");
		puts("|");
		free(man);
	}
	else puts("���� ����");
	fclose(f);      //�������� �����
}



//else
//			{
//			fread(man[i].name, n2, 1, f);    //������ ���
//			fread(man[i].surname, n2, 1, f); //������ �������
//			fscanf_s(f, "%d%lf%lf%lf%lf\n", &man[i].age, &man[i].money[0].dollar, &man[i].money[1].euro, &man[i].money[2].RUB, &man[i].money[3].BYN);
//			}