#include "Header.h"  //подключение библиотеки

void push(stack **h, char c, int i) //функция добавления элемента на верхушку стека
{
	stack *pointer;
	if (!(pointer = (stack*)calloc(1, sizeof(stack))))
	{
		puts("\nНет свободной памяти");
		return;
	}
	pointer->index = i;    //заносим очередной индекс скобки в стек 
	pointer->bracket = c;  //заносим очередную скобку в стек
	pointer->next = (*h);  //запоминаем адрес старой врешины стека
	*h = pointer;          //новый элемент становится вершиной стека
}