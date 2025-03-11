#include "Header.h"   //подключение библиотеки

void realloc_ms1(int *&ms1, int size)    //функция перераспределения памяти для массива индексов
{
	ms1 = (int*)realloc(ms1, size * sizeof(int)); //перераспределение памяти
	if (!ms1) //еслии возникла ошибка
	{
		if (size) puts("Ошибка выделения памяти\n");
		return;
	}
}