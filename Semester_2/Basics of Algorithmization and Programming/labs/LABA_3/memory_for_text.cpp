#include "Header.h"    //подключение библиотеки

char** memory_for_text(char **&str, int size) //функция выделения памяти под вводимый текст
{
	str = (char**)calloc(size, sizeof(char*));
	if (!str)          //если память не выделена
	{
		puts("Memory allocation error!\n");
		return 0;
	}
	for (int i = 0; i < size; i++)
	{
		str[i] = (char*)calloc(n2+1, sizeof(char)); //выделение памяти под хранение строк
		if (!str[i])   //если память не выделена
		{
			while (--i >= 0) free(str[i]); //освобождение памяти от предыдущих удачных попыток выделения памяти под строки
			free(str); //освобождение памяти от указателя на массви указателей на строки
			puts("Memory allocation error!\n");
			return 0;
		}

	}
	return str;        //вернуть указатель на массив указателей
}