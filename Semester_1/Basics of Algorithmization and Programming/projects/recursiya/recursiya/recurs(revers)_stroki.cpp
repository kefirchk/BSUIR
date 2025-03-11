#include "Headers.h"                                               //подключение библиотеки

char recurs_stroki(char* &new_str)                  //функция сортировки слов независимо от их рассположения в тексте в порядке возрастания
{                                    
	static int j;
	char letter = 0;
	letter = new_str[j];
	if(new_str[++j]!='\0') recurs_stroki(new_str);
	else return letter;
	puts(new_str);
}