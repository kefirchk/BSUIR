#include "Header.h" //����������� ����������

int length(FILE *f, char *name) //������� �������� ����� �����
{
	char c;
	puts("������� ����� �����?(y\\n)");
	switch (c = _getch()) //���� ��(y) ��� ���(n)
	{
	case 'y': break;      //���� y
	case 'n': return 0;   //���� n
	default: puts("������! ��������� ����:");
	}
    errno_t ff = fopen_s(&f, name, "rt");  //�������� �����
	if (ff)
	{
		puts("���� �� ����� ���� ������");
		return 0;
	}
    //char cc;
    int ds = _fileno(f);		     //���������� �����
    long len = _filelength(ds);	     //����� �����
    printf("\n�����: %d\n", len);
    //fseek(f, 0, 2);                //����������� ���� � ����� �����
    //int kk = ftell(f);             //�������� ������� ���� � �����
    //printf("\n�������: %d\n", kk);
    fclose(f);                       //������� ����
	return len;                      //������� ����� �����
}