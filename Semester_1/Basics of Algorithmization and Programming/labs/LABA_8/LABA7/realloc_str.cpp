#include "Headers.h"                                           //подключение библиотеки

void realloc_str(int n, char** &str, int &size)                //функция перераспределения памяти
{
	int j;                                                     //счетчик
	for (int i = 0; i < n; i++)                                //цикл по i для проход по строкам
	{
		for (j = 0; (*(*(str + i) + j)) != '\0'; j++);         //вычисления исходной длины строки
		str = (char**)realloc(str, n * sizeof(char*));         //перераспределение памяти
		(*(str+i)) = (char*)realloc((*(str+i)), (j+1) * sizeof(char)); 
		(*(*(str + i) + j)) = '\0';                            //присваивание в конец строки символа \0
	}
}