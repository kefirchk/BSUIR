#include "Functions.h"

void setColor(int color)        //����� ������� ����� ������
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color); //������� ����� ������
}