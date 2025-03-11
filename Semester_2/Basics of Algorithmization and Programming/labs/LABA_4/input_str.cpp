#include "Header.h"      //подключение библиотеки

char* input_str(int i, person *&man, int choice)    //функция ввода строки
{
	int j = 0;    //счетчик
	static char sl[n2] = {}, name[n2];         //массив для записи слова
	if (choice == 2 && i > -1) puts("Введите название файла:"); //приглашение на ввода названия файла
	char c;       //промежуточная переменная для замены и простоты
	do
	{
		c = _getche();   //ввод символа
		if (choice == 1) man[i].name[j] = c;         //если вводим имя
		if (!choice) man[i].surname[j] = c; //если вводим фамилию
		if (choice == 2 && i > -1) sl[j] = c;        //если вводим имя файла
		else if(choice == 2 && i ==-1) name[j] = c;
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
			(c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я') ||
			(c >='0' && c<='9') || c == ' ' || c == '_' || c == '.');
		else if (c == '\b')                     //нажата клавиша Backspace
		{
			if (j > 0) { printf(" \b \b"); j--; }   //аналог клавиши Backspace
			else printf(" ");
			j--;
		}
		else if (c == '\r') break;              //если нажат Enter
		else
		{
			puts("\nВозможно вы допустили ошибку.");
			puts("Пожалуйста, повторите ввод:");
			j = -1;                             //чтобы начать ввод заново
			rewind(stdin);                      //чистка буфера
		}
	} while (j++ < n2-1);
	if (choice == 1) (man + i)->name[j] = '\0'; //если вводим имя
	if (!choice) (man + i)->surname[j] = '\0';  //если вводим фамилию
	if (choice == 2 && i > -1) { sl[j] = '\0'; return sl; }    //если вводим имя файла
	else if (choice == 2 && i == -1) { name[j] = '\0'; return name; } //если вводим имя/фамилию
}