#include "Header.h" //����������� ����������

void show_file(FILE *f, char* name) //������� ��������� �����
{
	char c;         //��������� ����������
	errno_t ff;
	ff = fopen_s(&f, name, "rt");   //�������� ����� ��� ������
	if (ff) { puts("���� �� ����� ���� ������"); return; }
	printf("\n");   //������� �� ���� ������
	while (1)
	{
		fscanf_s(f, "%c", &c); //���������� ���������� ������� � �����
		if (feof(f)) { fclose(f); return; } //���� ����� �����
		printf("%c", c);       //����� ������� �� �����
	}
	fclose(f);      //�������� �����
}