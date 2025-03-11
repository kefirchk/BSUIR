#include "Header.h" //����������� ����������

char **realloc_text(char **&str, int size) //������� ����������������� ������ ��� ������
{
	int lenght; //������ �����
	for (int i = 0; i < size; i++)
	{
		lenght = strlen(str[i]); //���������� ������� ��������� ������
		str[i] = (char*)realloc(str[i], (lenght + 1)*sizeof(char)); //����������������� ������ ��� �������� �����
		if (!str[i])   //���� �� ������� ���������������� ������
		{
			while (--i >= 0) free(str[i]); //������������ ������ �� �����, ��� ������� �������� ������
			free(str); //������������ ������ �� ��������� �� ��������� �� ������
			puts("Segmentation error!\n");
			return 0;
		}
		str[i][lenght] = '\0';
	}
	return str;        //������� ��������� �� ��������� �� ������
}