#include "Header.h" //подключение библиотеки

void output_table(int n, pupil *info1) //функция вывода введенной информации о учениках
{
	int k = 0; int i = 0;

	//вывод заголовка таблицы
	while (i++ < 20) printf(" ");
	printf("Общая информация\n");

	//рисовка верхней границы таблицы
	printf(" ");
	while (k++ < 53) printf("_");

	//вывод "шапки" таблицы
	printf("\n|Имя\t\t\t");
	printf("Фамилия\t\t\t");
	printf("Класс |\n|");
	while (k-- > 1) printf("_");//рисовка нижней границы таблицы
	printf("|");

	//заполнение таблицы информацией о учениках
	for (int i = 0; i < n; i++)
	{
		printf("\n|%-23s", info1[i].imya);
		printf("%-24s", info1[i].familia);
		printf("%-2d%-1c   |", info1[i].clas, info1[i].letter);
	}
	printf("\n|");
	while (k++ < 53) printf("_");; //рисовка нижней границы таблицы
	puts("|");
}