#include "Header.h"                   //подключение библиотеки

void show_balance(info* tail, info* head, FILE* f, char* fileName)
{
	info* pointer = tail;             //указатель для прохода по очереди
	if (!file_in_str(tail, head, fileName, f)) //вызов функции переписи информации из файла в очередь 
	{ puts("Файл пуст"); return; }
	if (pointer = input_PIN(tail))    //вызов функции входа в учетную запись
	{
		int k = 0;                    //счётчик
		printf(" ");
		while (k++ < 75) printf("_"); //рисовка верхней границы таблицы
		k = 71;
		printf("\n|Имя\t\t|Фамилия\t|Доллары   |Евро      |Рос. рубли|Бел. рубли|\n|"); //вывод "шапки" таблицы
		while (k-- > 1)                                                                 //цикл по подрисовке верхней границы таблицы
		{
			if (k == 10 || k == 20 || k == 30 || k == 40 || k == 55) printf("|");
			printf("_");
		}
		printf("|");
		printf("\n|%-15s|%-15s|%-10d|%-10d|%-10d|%-10d|\n|",                            //заполнение таблицы информацией
			pointer->name, pointer->surname, pointer->cash[0].dollar, 
			pointer->cash[1].euro, pointer->cash[2].RUB, pointer->cash[3].BYN);
		while (k++ < 70)                                                                //рисовка нижней границы таблицы
		{
			if (k == 16 || k == 31 || k == 41 || k == 51 || k == 61) printf("|");
			printf("_");
		}
		puts("|");
	}
	else return;
}