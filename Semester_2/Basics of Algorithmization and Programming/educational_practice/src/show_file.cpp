#include "Header.h" //����������� ����������
#include <io.h>

void show_file(FILE *f, char* name, info* head, info* tail) //������� ��������� �����
{
	errno_t ff = fopen_s(&f, name, "r+t");   //�������� ��������� ����� ��� ������
	if (ff)                                  //������ �������� �����
	{
		printf("%c[%d;%dm\n���� �� ����� ���� ������!%c[%dm\n", 27, 1, 31, 27, 0); 
		return; 
	}
	int length = _filelength(_fileno(f)), size = length / sizeof(info);   //����� ����� � ���������� �������� �������������� 
	rewind(f);                               //���������� ����
	if (size)
	{
		int k = 0;                           //�������
		printf(" ");
		while (k++ < 86) printf("_");        //������� ������� ������� �������
		printf("\n|���\t\t|�������        |���-���   |�������   |����      |���. �����|���. �����|\n|"); //����� "�����"
		k = 81;
		while (k-- > 1)                      //���������� ������� ������� �������
		{
			if (k == 10 || k == 20 || k == 30 || k == 40 || k == 50 || k == 65) printf("|");
			printf("_");
		}
		info* pointer = NULL;                //��������� �� ���������
		for (;!feof(f);)
		{
			if (!(pointer = (info*)calloc(1, sizeof(info)))) //��������� ������ ��� ���������
			{
				printf("%c[%d;%dm\n������ �� ��������!%c[%dm\n", 27, 1, 31, 27, 0);
				exit(1);
			}
			fgets(pointer->name, len+1, f);  //���������� �����
			fgets(pointer->surname, len+1, f); //���������� �������
			fscanf_s(f, "%d%d%d%d%d\n", &pointer->PIN, &pointer->cash[0].dollar,  //���������� �������� ������ 
				&pointer->cash[1].euro, &pointer->cash[2].RUB, &pointer->cash[3].BYN);
			printf("|\n|%-15s|%-15s|%-10d|%-10d|%-10d|%-10d|%-10d",               //����� ��������� ����������
				pointer->name, pointer->surname, pointer->PIN, pointer->cash[0].dollar, 
				pointer->cash[1].euro, pointer->cash[2].RUB, pointer->cash[3].BYN);
			free(pointer);
		}
		printf("|\n|");
		while (k++ < 80) 		             //������� ������ ������� �������
		{
			if (k == 16 || k == 31 || k == 41 || k == 51 || k == 61 || k == 71) printf("|");
			printf("_");
		}
		puts("|");
	}
	else puts("���� ����");
	fclose(f);                               //�������� �����
}