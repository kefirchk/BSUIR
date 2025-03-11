#include "Header.h"   //����������� ����������
#include <io.h>

int file_in_str(info* &tail, info* &head, char* name, FILE *f) //������� �������� ���������� �� ����� � �������
{
	errno_t ff = fopen_s(&f, name, "r+t"); //�������� ����� ��� ������
	if (ff)                                //�������� �� �������� �����
	{
		printf("%c[%d;%dm���� �� ����� ���� ������!%c[%dm\n", 27, 1, 31, 27, 0);
		return 0;
	}
	int size = 0, length = _filelength(_fileno(f));   //���������� ����� � ����� � ����� ����� 
	size = length / sizeof(info);                     //���������� ����������� �������� � �����
	if (size)                                         //���� �� ������
	{
		for (int i = 0; i < size && !feof(f); i++)    //���� �� �������� ���������� �� �����
		{
			info* pointer = (info*)calloc(1, sizeof(info)); //��������� ������
			if (!pointer)                                   //���� ������ �� ��������
			{
				printf("%c[%d;%dm������ �� ��������!%c[%dm\n\n", 27, 1, 31, 27, 0);
				exit(1);
			}
			char c = 0;                               //��������� ���������� ��� �������� �������
			for (int i = 0; i < len; i++)             //���� �� �������� �����
			{
				fscanf_s(f, "%c", &c);                //���������� �������
				if (c != ' ' && c != '\0')            //������ ������� � ������
					pointer->name[i] = c;
			}
			for (int i = 0; i < len; i++)             //���� �� �������� �������
			{
				fscanf_s(f, "%c", &c);                //���������� �������
				if (c != ' ' && c != '\0')            //������ ������� � ������
					pointer->surname[i] = c;
			}
			fscanf_s(f, "%d%d%d%d%d\n",               //������ �� ����� ��������� ����������
				&pointer->PIN, &pointer->cash[0].dollar, 
				&pointer->cash[1].euro, &pointer->cash[2].RUB, &pointer->cash[3].BYN);
			if (!tail || !head) tail = head = pointer;//���� ������� �� �������
			else
			{
				pointer->next = tail;                 //���������� �������� � ������� 
				tail = pointer;                       //������������� ������
			}
		}
	}
	else puts("���� ����");
	fclose(f);                                        //�������� �����
	return size;                                      //������� ���������� ��������
}