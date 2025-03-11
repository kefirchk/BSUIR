#include "Headers.h"                                     //подключение библиотеки

char* memory_del_elements(int n, char* str_del)           //функция выделения памяти под массив удаленных элементов
{
	str_del = (char*)malloc((n + 1) * sizeof(char));     //выделение памяти под массив удалённных элементов
	if (str_del == NULL)                                 //проверка на выделение памяти
	{
		puts("Память не выделена!");
		exit(1);                                         //завершение программы
	}
	return str_del;                                  
}