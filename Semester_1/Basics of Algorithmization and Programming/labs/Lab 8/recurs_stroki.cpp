#include "Headers.h"                   //подключение библиотеки

void recurs_stroki(char* &new_str)     //функция переворота слов в тексте с помощью рекурсии
{
	static int j;                      //счетчик
 	if ((*(new_str+j)) != '\0')        //проход по строке
	{
		j++;
		recurs_stroki(new_str);        //рекурсия
	}
	else return;
	printf("%c", new_str[--j]);        //вывод символов
}