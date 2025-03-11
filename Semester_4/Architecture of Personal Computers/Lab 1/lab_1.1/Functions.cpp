#include "Functions.h"

void setColor(int color)        //метод задания цвета тексту
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color); //задание цвета текста
}