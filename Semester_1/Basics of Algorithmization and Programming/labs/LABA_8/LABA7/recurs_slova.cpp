#include "Headers.h"                                      //подключение библиотеки

void recursWord(char* new_str, int begin, int end);       //функция переворота слова рекурсией
void poisk_word(char* new_str, int n);                    //функция поиска слов в строке

void recurs_slova(char* &new_str)                         //функция переворота слова в строке рекурсией
{
	int num=0;                                            //размер строки
	while(new_str[num] != '\0')num++;                     //вычисление размера строки
	poisk_word(new_str, num);                             //обращение к функции поиска очередного слова
	//puts(new_str);                                      //вывод строки
	static int j;                                         //счетчик
	if ((*(new_str + j)) != '\0')                         //проход по строке
	{
		j++;
		recurs_stroki(new_str);                           //рекурсия
	}
	printf("%c", new_str[--j]);                           //вывод символов
}


void poisk_word(char* new_str, int num)                   //функция поиска слов в строке
{
	static int begin, end;                                //начало и конец слова
	if (num > 0) poisk_word(new_str, num - 1);            //обращение к функции поиска слова
	if ((new_str[num] == ' ') || (new_str[num] == '\0')) 
	{
		end = num - 1;                                    //изменение конца слова  
		recursWord(new_str, begin, end);
 		begin = num + 1;                                  //изменение начала слова
	}
}


void recursWord(char* new_str, int begin, int end)        //функция переворота слова рекурсией
{
	static char temp;                                     //временная переменная
	if (end> begin) 
	{
		recursWord(new_str, begin + 1, end - 1);          //обращение к функции переворота слова
	}
	else return;
	temp = new_str[begin];                               
	new_str[begin] = new_str[end];
	new_str[end] = temp;
}