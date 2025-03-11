#include "Header.h"  //подключение библиотеки

void special_output(int k, word* ab, char* sl) //функция вывода желаемого слова
{
	if (!sl) return;
	int i = 0;      //счетчик
	for (; i < k; i++) 
		if (!strcmp(sl, ab[i].word)) //если нашлось совпадение 
		{ 
			output_result(i, ab, 1); //вызов функции вывода на экран результата поиска
			break;                   //прервать цикл
		}
	if (i == k) puts("Не удалось найти такого слова в базе данных");
}