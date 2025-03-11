#include "Header.h"    //подключение библиотеки

int* currency_choice(person *&man, int i, int count) //функция выбора валюты
{
	puts("Выберете валюту, с которой нужно работать:\n"
		"1 - доллар;\n"
		"2 - евро;\n"
		"3 - российский рубль\n"
		"4 - белорусский рубль");
	int t;  //временная переменная
	for (int j = 0; j < count; j++)
	{
		man[i].data[1].mv[j] = input_int(1);  //вызов функции выбора валюты от "1" до "4"
		t = j;
		while (--t >= 0) if (man[i].data[1].mv[j] == man[i].data[1].mv[t]) { t = 5; break; } //проверка на повторение ввода
		if (t == 5 || man[i].data[1].mv[j] == 0 || man[i].data[1].mv[j] > 4 || man[i].data[1].mv[j] < 1) //проверка на корректность ввода
		{
			puts("Error! Please, try again");
			j--;
		}
	}
	return man[i].data[1].mv;          //вернуть массив номеров выбранных валют
}