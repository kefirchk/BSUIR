#include "Headers.h"                                       //подключение библиотек

char* memory_for_new_str(int num, char* &new_str)          //функция выделения памяти под строку new_str
{
	if (!(new_str = (char*)malloc((num+1) * sizeof(char))))//выделение памяти + проверка на выделение памяти
	{
		printf("Нет свободной памяти!");                   //вывод на экран текста, если память не выделилась
		exit(0);                                           //завершение программы
	}
	return new_str;                                        //возвращение значения new_str
}