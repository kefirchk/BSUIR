#include "Header.h" //����������� ����������

void changePIN(info* head, info* tail, char* fileName, FILE* f) //������� ����� ���-����
{
	info* pointer; //��������� ��� ������� �� �������
	file_in_str(tail, head, fileName, f); //����� ������� ������ ���������� �� ����� � �������
	if (pointer = input_PIN(tail))        //����� ������� ����� � ������� ������
	{
		printf("%c[%d;%dm������� ����� PIN-���%c[%dm\n", 27, 1, 33, 27, 0);
		pointer->PIN = input_int();       //����� ������� ����� ������ ���-����
		replace_file(tail, fileName, f);  //����� ������� ������ �����
		printf("%c[%d;%dmPIN-��� ������� �������!%c[%dm\n", 27, 1, 32, 27, 0);
	}
	return;
}