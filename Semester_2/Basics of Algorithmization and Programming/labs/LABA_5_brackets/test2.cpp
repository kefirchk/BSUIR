#include "Header.h"            //подключение библиотеки

void test2(char choice, char *&str) //функция подменю проверки и исправления скобок в выражении с помощью стека
{
	if (choice != '1') return; //если выбран другой режим работы
	int index;                 //индекс неправильной скобки
	stack *head = NULL;        //указатель на вершину стека
	index = check_with_stack(head, str, 1); //вызов функции проверки расстановки скобок
	puts("Исходная строка:");
	output_str(str, index);    //вызов функции вывода исходной строки
	printf("\n");
	if (index > -1)
	{
		char strcopy[len+1] = {}, *s; //доп. строка
		strcpy_s(strcopy, str);       //копирование исходной строки
		char c;
		while (1)
		{
			puts("Выберете действие:");
			printf("%c[%d;%dm0 - исправить ошибку вручную%c[%dm\n", 27, 1, 34, 27, 0);
			printf("%c[%d;%dm1 - исправить ошибку автоматически%c[%dm\n", 27, 1, 34, 27, 0);
			printf("%c[%d;%dm2 - оставить без изменений%c[%dm\n", 27, 1, 34, 27, 0);
			switch (c = _getch())
			{
			case '0': str = input_str('1');  //вызов функции ввода строки
				index = check_with_stack(head, str, 1);   //вызов функции проверки расстановки скобок
				if (index > -1) continue;
			case '1': stack_fix(head, str, index); break; //вызов функции удаления неправильных скобок
			case '2': break;
			default: puts("Ошибка выбора операции!"); continue;
			} 
			s = strcopy;
			if (c != '2') save(s, str);  //вызов функции сохранения изменений в строке
			break;
		}
	}
}