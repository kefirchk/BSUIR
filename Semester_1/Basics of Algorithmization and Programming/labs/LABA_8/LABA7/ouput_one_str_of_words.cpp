#include "Headers.h"                             //подключение библиотеки

void output_one_str_of_words(char* new_str)      //функция вывода строки new_str 
{
	printf("\nВсе найденные слова в тексте:\n"); //вывод текста
	puts(new_str);                               //вывод строки
	printf("\n");                                //переход на новую строку
}