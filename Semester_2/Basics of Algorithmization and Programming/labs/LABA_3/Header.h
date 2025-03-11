#include <locale.h>   //подключение библиотек
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <io.h>

#define n1 2    //количество строк в тексте
#define n2 20   //длина строк

struct word     //структура, которая содержит информацию о слове
{
	char word[n2 + 1];   //слово
	int repeat;          //число появлений в тексте
};

int menu(char** &, FILE *&f, char*);             //функция выбора режима работы программы
void show_file(FILE *f, char* name);             //функция вывода содержимого в файле
int file_in_str(char*, char **&str, FILE *f);    //функция переписи информации из файла в массив строк
int input_n(int k);                              //функция ввода количества слов, которые нужно отобразить
char** input_text(char*, char **, FILE *&, int); //функция ввода текста
char* input_word(int);                           //функция ввода слова
char** memory_for_text(char **&str, int);        //функция выделения памяти под текст
char **realloc_text(char **&str, int size);      //функция перераспределения памяти под текст
int poisk_words(word*&, char **, int size);      //функция поиска слов в тексте
int special_order(int k, word* ab);              //функция, которая предлагает вывести на экран отдельно желаемое слово 
void special_output(int k, word*, char* sl);     //функция вывода желаемого слова
word* memory_struct(word *ab, int k);            //функция выделения памяти под массив структур
word* repeats(word* ab, int k);                  //функция подсчета числа появлений каждого слова
word* delete_same_words(word* ab, int &k);       //функция удаления одинаковых слов из массива структур
word* sort_ms(word* ab, int k);                  //функция сортировки слов по их числу появлений в массиве структур
void output_result(int n, word* ab, int);        //функция вывода результата на экран
void free_memory(int, char** str, word* ab);     //функция освобождения памяти от указателей на указатели на строки, на структуры и на строки
int offer();                                     //функция, которая предлагает продолжить программу
int length(FILE *f, char* name);                 //функция подсчета длины файла