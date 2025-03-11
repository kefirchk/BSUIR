#include "Header.h"

void hat_for_ex2(pupil *info1, int size, int *ms2) //функция вывода результата поиска однофамильцев по параллельным классам
{
	if (size)
	{
		int k = 0;    //cчетчик
		printf("\n");
		while (k++ < 12) printf(" ");
		printf("Однофамильцы в параллельных классах\n");
		k = 0;

		//рисовка верхней границы таблицы
		printf(" ");
		while (k++ < 53) printf("_");

		//вывод "шапки" таблицы
		printf("\n|Имя\t\t\t");
		printf("Фамилия\t\t\t");
		printf("Класс |\n|");
		while (k-- > 1) printf("_");//рисовка нижней границы шапки
		printf("|");

		//заполнение таблицы информацией о учениках
		int temp = 0;     //временная переменная, что знать до какого элемента проверять на подчеркивание таблицы
		for (int i = 0; i < size; i++)
		{
			int j = i;    //счетчик
			while(--j >= temp) //проверка, где нужно подчеркивать очередную строку таблицы
			{   
				if (j && info1[ms2[j]].letter == info1[ms2[i]].letter && !strcmp(info1[ms2[j]].imya, info1[ms2[i]].imya) && !strcmp(info1[ms2[j]].familia, info1[ms2[i]].familia))
				{
					temp = i;
					printf("\n|");
					while (k++ < 53) printf("_");
					printf("|");
					k = 0;
				}
			}
			printf("\n|%-23s", info1[ms2[i]].imya); //вывод имени
			printf("%-24s", info1[ms2[i]].familia); //вывод фамилии
			printf("%-2d%-1c   |", info1[ms2[i]].clas, info1[ms2[i]].letter); //вывод номера и буквы класса 
		}
		printf("\n|");
		while (k++ < 53) printf("_");;//рисовка нижней границы таблицы
		puts("|");
	}
}