#include "Header.h" //подключение библиотеки

void string_fix(char* stack, char *str, int index) //функция удаления неправильной скобки
{
	do {
		correct_without_stack(stack, str, index); //вызов функции исправления ошибки
		index = check_without_stack(str, 0);    //вызов функции проверки расстановки скобок
		if (index < 0)
		{
			puts("\nИсправленная строка:");
			output_str(str, index); //вызов функции вывода строки
			break;
		}
	} while (1);
}

void stack_fix(stack *&head, char* &str, int index) //функция удаления неправильной скобки
{
	char c = 0;
	do
	{
		puts("\nВыберете опцию:"
			"\n1 - удалять скобки"
			"\n2 - добавлять/изменять скобки");
		c = _getch();
	} while (c != '1' && c != '2');
	if (c == '1') str = del(head, str, index); //вызов функции исправления скобок(способ 1)
	else str = add(head, str, index); //вызов функции исправления скобок(способ 2)
}