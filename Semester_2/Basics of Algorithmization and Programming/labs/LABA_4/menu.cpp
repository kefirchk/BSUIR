#include "Header.h" //����������� ����������

int menu(person *&man, FILE *&f, char* name)  //������� ������ ������ ������ ���������
{
	char c, howOpen; //��������� ����������
	int n = 0;       //���������� �����
	while (1) {
		puts("�������� ��� �����:"
			 "\n0 - ��������� "
			 "\n1 - ��������");
		howOpen = _getch();
		if (howOpen == '0' || howOpen == '1') break;
	}
	while (1)
	{
		puts("\n�������� ����� ������:\n"
			"\n1 - �������� � ���� ����������"
			"\n2 - ����������� ����"
			"\n3 - ���������� ����"
			"\n4 - ������� ����"
			"\n5 - �������� ���������� � ����� ������ � ����� ������� �����"
			"\n6 - �������� � ������ ������"
			"\n7 - ������ ������ ���� �����"
			"\n8 - ������� ���������� � ��������"
			"\n9 - �����");
		switch (c = _getch()) {
		case '1': case '3':
		{
			n = input_int(0);             //����� ������� ����� ���������� �����
			man = memory_struct(man, n);  //����� ������� ��������� ������ ��� ������ �������� ���� person
			man = input_info(n, man);     //����� ������� ����� ���������� � �����
			if (c == '1') 
				if(howOpen == '0') struct_in_text_file(name, f, man, '1', n); //�������� � ���� ����������
				else struct_in_binary_file(name, f, man, '1', n);
			if (c == '3') 
				if(howOpen == '0') struct_in_text_file(name, f, man, '3', n); //���������� ����
				else struct_in_binary_file(name, f, man, '3', n);
			break;
		}
		case '2': show_file(howOpen, f, name, man); continue;    //����� ������� ��������� �����
		case '5': n = file_in_str(man, name, f, howOpen); break; //����� ������� �������� ���������� �� ����� � ������ �����
		case '4':
		{
			if (remove(name)) { puts("������ ������� ����"); exit(1); } //�������� �����
			else puts("\n���� ������"); continue;
		}
		case '6': name = input_str(0, man, 2); continue;    //����� ������� ����� �������� �����
		case '7': perevod(man, -1); continue;
		case '8': del_person(f, man, name, howOpen);        //����� ������� �������� ���������� � �������� � �����
			      continue;
		case '9': exit(0);                                  //����� �� ���������
		default: puts("������ ������ ��������. ��������� ����"); continue;
		}
		break;
	}
	return n;
}



//���������� ����� ����� � ������
//int descriptor = _fileno(f);		// ���������� �����
//long length = _filelength(descriptor);	// ����� �����	
//printf("\n����� ����� = %d\n", length);