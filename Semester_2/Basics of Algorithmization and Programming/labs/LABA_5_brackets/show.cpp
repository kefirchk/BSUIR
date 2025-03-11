#include "Header.h"    //подключение библиотеки

void show(stack *head) //функция просмотра элементов стека
{
	if (!head)         //если стек пуст
	{
		puts("\nСтек пуст");
		return;
	}
	puts("\nСтек:");
	do 
	{
		printf("%c\n", head->bracket);  //вывод информации текущего элемента стека
		head = head->next;              //переход к следующему элементу стека
	} while (head);    //пока стек не пуст
}