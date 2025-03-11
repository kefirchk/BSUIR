#include <windows.h>                                           //подключение библиотек
#include <stdlib.h>
#include <stdio.h> 
#include <locale.h>
#include <conio.h>

char add_offer(char choice);
int lenght_strok(int n, char** str);      //функция вычисления нужной длины для строки new_str  
void revers_new(char *&new_str, int begin, int end);     //функция реверса слов (перестановка слов)
char recurs_stroki(char* &new_str);