#include "Header.h" //����������� ����������

int menu(char **&str, FILE *&f, char* name)  //������� ������ ������ ������ ���������
{
	int size = n1;               //���������� ����� � ������
	char c;                      //��������� ����������
	memory_for_text(str, size);  //����� ������� ��������� ������
	while (1)
	{
	    puts("\n�������� ����� ������:\n"
		"\n1 - �������� � ���� ����������"
		"\n2 - ����������� ����"
		"\n3 - ���������� ����"
		"\n4 - ������� ����"
		"\n5 - �������� n �������� ����� ������������� ���� � ����� �� ���������"
		"\n6 - �������� � ������ ������"
		"\n7 - �����");
		switch (c = _getch())
		{
		case '1': str = input_text(name, str, f, 1); break;      //����� ������� ���������� � ���� ����������
		case '2': show_file(f, name); continue;                  //����� ������� ��������� �����
		case '3': str = input_text(name, str, f, 3); break;      //����� ������� ���������� �����
		case '4': if (remove(name)) {
			      puts("������ ������� ����");
			      exit(1); }
		          else puts("\n���� ������"); continue;          //�������� �����
		case '5': size = file_in_str(name, str, f); break;       //����� ������� �������� ���������� �� ����� � ������ �����
		case '6': name = input_word(1); continue;                //����� ������� ����� �������� �����
		case '7': exit(0);                                       //����� �� ���������
		default: puts("������ ������ ��������. ��������� ����"); continue;
		}
		if (c == '1' || c == '3' || c == '5') realloc_text(str, size); //����� ������� ����������������� ������ ��� ����� � ��������� ������
		break;
	}
	return size;
}




//���������� ����� ����� � ������
//int descriptor = _fileno(f);		// ���������� �����
//long length = _filelength(descriptor);	// ����� �����	
//printf("\n����� ����� = %d\n", length);