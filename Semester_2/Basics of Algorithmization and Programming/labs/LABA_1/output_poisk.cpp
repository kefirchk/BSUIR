#include "Header.h"   //подключение библиотеки

void output_poisk(int t, pcopy *info2) //функция вывода результата поиска одноклассников
{
	if (!t) //если одноклассников не найдено
	{
		puts("\nОдноклассников не найдено");
		return;
	}
	int k = 0;        //счётчик
	printf("\n");     //переход на новую строку
	while (k++ < 5) printf(" ");
	printf("Одноклассники\n");

	//заполнение таблицы информацией о учениках
	int flag = 0; //флажок
	for (int i = 0; i < t; i++)
	{
		int p = i; //счетчик для проверки, был ли данный учебный класс уже рассмотрен
		while ((--p) > -1) if (info2[i].number == info2[p].number && info2[i].bukva == info2[p].bukva) flag = 1; //сама проверка + проверка на совпадение названий класса
		if (!flag) //если классы совпадают и не были рассмотрены ранее
		{
			k = 0; //обнуление счетчика
			printf(" ");
			while (k++ < 21) printf("_"); //рисовка очередной верхней границы шапки
			printf("\n|%10d%-11c|\n", info2[i].number, info2[i].bukva);
			printf("|");
			k = 22;
			while (k-- > 1) printf("_"); //рисовка очередной нижней границы шапки
			printf("|");
			printf("\n|%-21s|", info2[i].name); //вывод имени
			printf("\n|%-21s|\n", info2[i].surname); //вывод фамилии
			for (int j = i + 1; j < t; j++)
			{
				if (info2[i].number == info2[j].number && info2[i].bukva == info2[j].bukva) { //если классы учеников совпадают
					printf("|");
					while (k++ < 21) printf(" ");
					printf("|\n|%-21s|", info2[j].name); //вывод имени одноклассника
					printf("\n|%-21s|\n", info2[j].surname); //вывод фамилии одноклассника
					k = 0; //обнуление счётчика
				}
			}
			printf("|");
			while (k++ < 21) printf("_");;//рисовка нижней границы таблицы
			puts("|");
		}
		flag = 0; //обнуление флажка
	}
}