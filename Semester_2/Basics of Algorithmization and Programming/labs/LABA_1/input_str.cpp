#include "Header.h"      //подключение библиотеки

pupil* input(int i, pupil *info1, int choice)    //функция ввода строки
{
	int j = 0;    //счетчик
	char c;       //промежуточная переменная для замены и простоты
	do
	{
		c = _getche(); //ввод символа
		if (choice) (info1 + i)->imya[j] = c; //если вводим имя
		else (info1 + i)->familia[j] = c;       //если вводим фамилию
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я') || c == ' ');
		else if (c == '\b') //нажата клавиша Backspace
		{
			if (j > 0) { printf(" \b \b"); j--; }      //аналог клавиши Backspace
			else printf(" ");
			j--;
		}
		else if (c == '\r') break; //если нажат Enter
		else
		{
			puts("\nВозможно вы допустили ошибку.");
			puts("Пожалуйста, повторите ввод:");
			j = -1;                       //чтобы начать ввод заново
			rewind(stdin);              //чистка буфера
		}
	} while (j++ < 20);
	if (choice) (info1 + i)->imya[j] = '\0';  //если вводим имя
	else (info1 + i)->familia[j] = '\0';      //если вводим фамилию
	return info1;
}