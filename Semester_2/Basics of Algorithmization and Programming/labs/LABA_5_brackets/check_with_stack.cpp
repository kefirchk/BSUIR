#include "Header.h"

int check_with_stack(stack *&head, char *str, int c) //функция проверки расстановки скобок с использованием стека
{
	int j, index = -1; //j - признак того, что можно удалять вершину стека, index - индекс скобки
	//stack *head = NULL, *pointer;
	for (int i = 0; str[i] != '\0'; i++)
	{
		switch (str[i])
		{
		case '(': case '[': case '{': if (index < 0) index = i; push(&head, str[i], i); break; //положить скобку в стек
		case ')': case ']': case '}':
			if (!head)    //если стек пуст
			{
				error(head, c); //вызов функции вывода текста об ошибке и состояния стека
				return i; //вернуть индекс неправильной скобки
			}
			else
			{
				j = 0;    //зануляем флажок
				switch (str[i])
				{
				case ')': if (head->bracket == '(') j = 1; break; //если все правильно, то j = 1;
				case ']': if (head->bracket == '[') j = 1; break;
				case '}': if (head->bracket == '{') j = 1; break;
				}
			}
			if (j) pop(&head); //вызов функции удаления элемента с вершины стека
			//pointer = head; head = head->next; free(pointer);
			else {
				error(head, c); //вызов функции вывода текста об ошибке и состояния стека
				return i;      //вернуть индекс неправильной скобки
			}
		}
	}
	if (head) { //если стек в конце оказался не пустым
		error(head, c); //вызов функции вывода текста об ошибке и состояния стека
		return index;
	}
	else {     //если стек в конце пуст
		if (c)printf("%c[%d;%dm\nВсе правильно!%c[%dm\n", 27, 1, 32, 27, 0);
		return -1;
	}
}

void error(stack *head, int c) //функция выводит текст об ошибке и состояние стека
{
	if (c) {
		printf("%c[%d;%dm\nСкобки расставлены неправильно!%c[%dm\n", 27, 1, 31, 27, 0);
		printf("\nПросмотреть стек?(y\\n)\n");
		if (offer()) show(head); //предложение вывести стек
	}
}