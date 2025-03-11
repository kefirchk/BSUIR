#include "Header.h" //подключение библиотеки

int check_without_stack(char *str, int c) //функция проверки расстановки скобок в выражении без использования стека
{
	int n = 0, index = -1; //n - cчетчик, index - индекс неправильного символа
	char stack[len] = { }, b = 0; //дополнительный массив, используемый как стек
	for (int i = 0; str[i] != '\0'; i++)
	{
		while (str[i] != '(' && str[i] != ')' && str[i] != '[' &&    //пропуск символов, 
			str[i] != ']' && str[i] != '{' && str[i] != '}' && str[i] != '\0') i++; //пока не встретим какие-либо скобки
		if (!n && (str[i] == ')' || str[i] == ']' || str[i] == '}')) //если первой была закрывающая скобка
		{
			if (c)printf("%c[%d;%dm\nСкобки расставлены неправильно!%c[%dm\n", 27, 1, 31, 27, 0);
			return i;      //вернуть индекс закрыващей скобки
		}
		else
		{
			switch (str[i])
			{
			case '(': case '[': case '{': if (index < 0) index = i;  stack[n++] = str[i]; break; //добавить в стек
			case ')': b = '('; break;
			case ']': b = '['; break;
			case '}': b = '{'; break;
			}
		if ((stack[--n] != b && n) || (stack[n] != b && !n)) //несоответствие скобок
		{ 
			if (c)printf("%c[%d;%dm\nСкобки расставлены неправильно!%c[%dm\n", 27, 1, 31, 27, 0);
			return i;
		}
	}
	}
	if (!n) { //если счетчик равен нулю (стек пуст)
		if (c)printf("%c[%d;%dm\nВсе правильно!%c[%dm\n", 27, 1, 32, 27, 0);
		return -1;
	}
	else { //стек не пуст
		if (c)printf("%c[%d;%dm\nСкобки расставлены неправильно!%c[%dm\n", 27, 1, 31, 27, 0);
		return index;
	}
}

void correct_without_stack(char *stack, char *str, int index) //функция исправления ошибки в выражении без стека
{
	int k = 0; //временная переменная
	switch (str[index])
	{
	case ')': k = 1; break;
	case ']': k = 2; break;
	case '}': k = 3; break;
	}
	if (k) k = check1(stack, index, str, k); //вызов функции проверки и исправления скобки
	str = del_symbol(index, str); //вызов функции удаления символа в строке
}
int check1(char* stack, int index, char* str, int c) //функция проверки и исправления скобки
{
	char s1, s2, s3, s4;
	if (c == 1) { s1 = '['; s2 = '{'; s3 = ']'; s4 = '}'; }
	if (c == 2) { s1 = '('; s2 = '{'; s3 = ')'; s4 = '}'; }
	if (c == 3) { s1 = '('; s2 = '['; s3 = ')'; s4 = ']'; }
	if (strlen(stack)) //если стек-cтрока не пустая
	{
		int i = len - 1;
		while (stack[i] == '\0') i--;  //переход в конец строки (на вершину стека)
		if (stack[i] == s1) str[index] = s3; //исправление на скобки на нужную
		if (stack[i] == s2) str[index] = s4; //исправление на скобки на нужную
		return 0;
	}
	return 1;
}
