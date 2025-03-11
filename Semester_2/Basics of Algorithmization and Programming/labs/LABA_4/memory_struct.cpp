#include "Header.h"

person *memory_struct(person *&man, int n) 	//функция выделения памяти под массив структур
{
	man = (person*)calloc(n, sizeof(person)); //выделение памяти
	if (!man) //если память не выделена
	{
		puts("Ошибка! Память не выделена\n");
		exit(1);
	}
	return man;
}