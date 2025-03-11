#include "Header.h" //подключение библиотеки

char* add(stack *&head, char* str, int index) //функция исправления скобок (способ 1)
{
	do {
		str = correct_option_1(head, str, index); //вызов функции добавления нужных скобок
		while (head) pop(&head); //удаление стека
		index = check_with_stack(head, str, 0); //проверка исправленной строки
		if (index < 0) //если скобки расставлены правильно
		{
			puts("\nИсправленная строка:");
			output_str(str, index); //вызов функции вывода строки
			break;
		}
	} while (1);
	return str;
}

char* correct_option_1(stack* head, char* str, int index) //функция добавления нужных скобок
{
	int i = 0; //счетчик по строке
	char temp[2*len + 1] = {}, b = 0, s; //временная строка и переменные
	switch (str[index])
	{
	case '(': case '[': case '{':
		switch (head->bracket)
		{
		case '(': b = ')'; break;
		case '[': b = ']'; break;
		case '{': b = '}'; break;
		}
		//другой способ расстановки скобок
		/*for (int i = (head->index) + 1, j = 0; str[i] != '\0'; i++)
			temp[j++] = str[i];
		str[(head->index) + 1] = b;
		for (int i = (head->index) + 2, j = 0; temp[j] != '\0'; i++)
			str[i] = temp[j++];*/
		while (str[i] != '\0') i++; //переход в конец строки
		str[i] = b; //поставить нужную скобку
		break;
	case ')': case ']': case '}':
		if (head)
		{
			switch (head->bracket)
			{
			case '(': str[index] = ')'; break;
			case '[': str[index] = ']'; break;
			case '{': str[index] = '}'; break;
			} break;
		}
		else
		{
			for (int i = 0; str[i] != '\0'; i++) //цикл по строке
			{
				switch (str[i])
				{
				case ')': case ']': case '}': push(&head, str[i], i); break; //добавление в стек закрывающей скобки
				}
			}
			switch (head->bracket)
			{
			case ')': b = '('; break;
			case ']': b = '['; break;
			case '}': b = '{'; break;
			}
			i = 0;
			while (str[i] != '\0' && str[i] != ')' && str[i] != ']' && str[i] != '}') i++; //пропуск символов
			int ii = i; //запоминаем индекс, куда нужно будет вставить скобку
			for (int j = 0; str[i] != '\0'; i++) //цикл по записи части исходной строки во временную
				temp[j++] = str[i];
			str[ii] = b; //поставить нужную скобку
			for (int i = ii+1, j = 0; temp[j] != '\0'; i++) //запись переписанной информации из временной строки в исходную
				str[i] = temp[j++];
			pop(&head); //удалить вершину стека
		}
		
	}
	return str;
}