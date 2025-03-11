#include "Header.h" //подключение библиотеки

void test1(char choice, char *&str) //функция провереки расстановки скобок без использования стека
{
	if (choice != '0') return; //если выбран другой режим работы
	int index;                 //индекс неправильной скобки
	char stack[len+1] = {};
	index = check_without_stack(str, 1); //вызов функции проверки расстановки скобок
	puts("Исходная строка:");
	output_str(str, index); //вызов функции вывода исходной строки
	printf("\n");
	if (index > -1)
	{
		char strcopy[len+1] = {}, *s; //дополнительная строка
		strcpy_s(strcopy, str);     //копирование в доп. строку исходной строки
		char c;
		while (1)
		{
			puts("Выберете действие:");
			printf("%c[%d;%dm0 - исправить ошибку вручную%c[%dm\n", 27, 1, 34, 27, 0);
			printf("%c[%d;%dm1 - исправить ошибку автоматически%c[%dm\n", 27, 1, 34, 27, 0);
			printf("%c[%d;%dm2 - оставить без изменений%c[%dm\n", 27, 1, 34, 27, 0);
			switch (c = _getch())
			{
			case '0': str = input_str('1');
				index = check_without_stack(str, 1);   //вызов функции проверки расстановки скобок
				if (index > -1) continue;              //если пользователь не исправил строку
				break;
			case '1': string_fix(stack, str, index); break;
			case '2': break;
			default: puts("Ошибка выбора операции!"); continue;
		    } 
			s = strcopy;
			if (c != '2') save(s, str);  //вызов функции сохранения изменений в строке
			break;
		}
	}
}