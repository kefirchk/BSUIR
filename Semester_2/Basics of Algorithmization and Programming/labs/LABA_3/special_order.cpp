#include "Header.h"   //подключение библиотеки

int special_order(int k, word* ab) //функция, которая предлагает вывести любое слово из найденных отдельно
{
	char c, *sl;     //временные переменные
	while (1) {
		puts("Интересует какое-то отдельное слово?(y\\n)");
		while (1)
		{
			if ((c = _getch()) == 'y') //ввод "y" - Да
			{
				puts("Введите желаемое слово:");
				sl = input_word(0);         //ввода слова
				special_output(k, ab, sl);  //обращение к функции вывода желаемого слова
				break;                 //прервать цикл
			}
			else if (c == 'n') return 0; //ввод "n" - Нет
			else puts("Error! Please, try again");
		}
	}
	return 0;        //вернуть 0
}