#include "Header.h"        //подключение библиотеки

int* mem_for_mv(person *man, int count, int i) //функция выделения памяти под массив номеров валют
{
	man[i].data[1].mv = (int*)calloc(count, sizeof(int)); //выделение памяти
	if (!man[i].data[1].mv)        //если память не выделилась
	{
		puts("Ошибка выделения памяти");
		return NULL;
	}
	return man[i].data[1].mv;      //вернуть указатель на массив
}