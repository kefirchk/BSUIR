#include "Header.h" //подключение библиотеки

char* del(stack *&head, char *str, int index) //функция исправления скобок(способ 2)
{
	do {
		correct_option_2(head, str, index); //вызов функции исправления ошибки
		while (head) pop(&head);            //удаление стека
		index = check_with_stack(head, str, 0);   //вызов функции проверки расстановки скобок
		if (index < 0)
		{
			puts("\nИсправленная строка:");
			output_str(str, index); //вызов функции вывода строки
			break;
		}
	} while (1);
	return str;
}

void correct_option_2(stack *&head, char* &str, int index) //функция исправления ошибки в выражении с помощью стека
{
	int k = 0; //временная переменная
	switch (str[index])
	{
	case ')': k = 1; break;
	case ']': k = 2; break;
	case '}': k = 3; break;
	}
	if (k) k = check2(head, index, str, k); //функция проверки и исправления скобки
	str = del_symbol(index, str); //если стек пустой, то вызов функции удаления символа в строке
}

int check2(stack* head, int index, char* str, int c) //функция проверки и исправления скобки
{
	char s1, s2, s3, s4;
	if (c == 1) { s1 = '['; s2 = '{'; s3 = ']'; s4 = '}'; }
	if (c == 2) { s1 = '('; s2 = '{'; s3 = ')'; s4 = '}'; }
	if (c == 3) { s1 = '('; s2 = '['; s3 = ')'; s4 = ']'; }
	if (head) //если стек не пустой
	{
		if (head->bracket == s1) str[index] = s3; //исправление на скобки на нужную
		if (head->bracket == s2) str[index] = s4; //исправление на скобки на нужную
		return 0;
	}
	return 1;
}