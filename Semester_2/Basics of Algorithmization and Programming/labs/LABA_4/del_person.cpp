#include "Header.h" //����������� ����������

int del_person(FILE *&f, person *&man, char* nameFile, char fileOpen)  //������� �������� �������� �� �����
{
	char *str, name[n2] = {}, surname[n2] = {}; //��������� ������� �������� ��� ������ �������� �������� � �����
	puts("������� ��� ��������:");
	str = input_str(-1, man, 2); //����� ������� ����� �����
	strcpy_s(name, n2, str);     //����������� ��������� ���������� � name
	puts("\n������� ������� ��������:");
	str = input_str(-1, man, 2); //����� ������� ����� �������
	strcpy_s(surname, n2, str);  //����������� ��������� ���������� � surname
	int n = file_in_str(man, nameFile, f, fileOpen); //����� ������� ������ ���������� �� ����� � ���������
	if (n)
	{
		int flag = 0; //������, ������� ������, ��� �� ����� �������� �������� ��� �������� ��� �������� 1
		for (int i = 0; i < n; i++)
		{
			if (!strcmp(name, man[i].name) && !strcmp(surname, man[i].surname)) //��������� ���� � �������
			{
				for (int j = i+1; j < n; j++) //���� �� �������� ������� ��������
				{
					*(man + j - 1) = *(man + j);
				}
				n--;      //��������� ���������� ����� � �����
				flag = 1; //������� ��������� ������� 
				break;    //�������� ����
			}
		}
		if (flag)         //���� �� ����� ��������
		{
			char fileCopyName[n2] = "file_copy"; //��������� ��� ������ �����
			if (fileOpen == '0') struct_in_text_file(fileCopyName, f, man, '3', n);
			else struct_in_binary_file(fileCopyName, f, man, '3', n);
			free(man);                           //���������� ������ �� ������� �������� ���� person
			if (remove(nameFile)) { puts("������ �������� ������� �����"); exit(1); } //�������� ������� �����
			if (rename(fileCopyName, nameFile)) 
			{ puts("������ �������������� �����"); exit(1); } //�������������� ������ �����
			puts("���������� �������");
		}
		else puts("������ �������� � ����� �� �������");
	} 
	else puts("���� ����");
	return 0;
}