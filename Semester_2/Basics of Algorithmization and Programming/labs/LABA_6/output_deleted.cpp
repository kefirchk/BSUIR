#include "Header.h"                        //подключение библиотеки

void output_deleted(people* tailDeleted)   //функция вывода списка выселенных людей
{
	if (!tailDeleted)
	{
		puts("\nСписок выселенных людей пуст!");
		return;
	}
	people* ptr = tailDeleted;             //указатель на хвост списка выселенных людей
	int k = 0;                             //счетчик
	printf(" ");
	while (k++ < 58) printf("_");          //вывод верхней границы таблицы
	printf("\n|Имя\t\t|Фамилия        |Факультет      |Группа    |\n|"); //вывод "шапки"
	k = 56;
	while (k-- > 1)                        //подрисовка верхней границы таблицы
	{
		if (k == 10 || k == 25 || k == 40) printf("|");
		printf("_");
	}
	while (ptr)                            //цикл по выводу информации
	{
		printf("|\n|%-15s|%-15s|%-15s|%-10d", ptr->name, ptr->surname,
			ptr->faculty, ptr->group);
		ptr = ptr->next_person;
	}
	printf("|\n|");
	while (k++ < 55)                       //рисовка нижней границы таблицы
	{
		if (k == 16 || k == 31 || k == 46) printf("|");
		printf("_");
	}
	puts("|");
}