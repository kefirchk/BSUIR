#include <windows.h>                                           //подключение библиотек
#include <stdlib.h>
#include <stdio.h> 
#include <locale.h>
#include <conio.h>
#include <stdarg.h>

int input_n(int, ...);                                         //функция ввода количества строк
int input_size(int &size, char &choice);                       //функция ввода размера строк
char** memory_for_str(int n, int size, char** str);            //функция выделения памяти под текст
char* memory_for_new_str(int num, char* &new_str);             //функция выделения памяти под строку слов
void str_equals_new_str(int n, char* &new_str, char** &str);   //функция заполнения строки new_str
char** input_text(int n, int size, char **&str);               //функция ввода текста
void output_text(char** str, int &n);                          //функция вывода введенного текста
void search_words(char** &str, int n, int size);               //функция посика слов в тексте
void output_highlighted_words(int n, char** new_str);          //функция вывода найденных слов
char choose_option_sort(int, ...);                             //функция выбора варианта сортировки (в порядке убывания или возврастания)
void sort_by_row(char** str, int n, char &number);             //функция сортировки слов по строкам
//void revers(char **&str, int begin, int end, int &i);          //функция перестановки слов для всех строк текста(реверс)
void revers_new(char *&new_str, int begin, int end);           //функция перестановки слов для одной большой строки (реверс)
void realloc_str(int n, char** &str, int &size);               //функция перераспределения памяти
char choice_to_sort_text(char &choice);                        //функция выбора вариаанта сортировки слов(по строкам или независимо от их рассположения в тексте)
char* sort_all_text(char* &new_str, char &number);             //функция сортировки слов независимо от их рассположения в тексте
int lenght_strok(int &n, char** &str);                         //функция вычисления нужного размера для строки new_str
void output_one_str_of_words(char* new_str);                   //функция вывода строки, содержащей все найденные слова в тексте
void output_complete_text(char** str, int n);                  //функция вывода отсортированных слов по строкам, в которых первые были найдены
void output_complete_text_2(char* &new_str, int num);          //функция вывода строки отсортированных слов по их длине, которые удалось найти в тексте
void clean_memory_param(char** &str, int &n, char* &new_str, char &choice);
//void clean_memory(char** &str, int &n, char* &new_str, char &choice); //функция освобождения памяти от указателей на указатели и от указателей на строки
void recurs_slova(char* &new_str);                             //функция переворота слов в строке рекурсией   
void recurs_stroki(char* &new_str);                            //функция переворота строки рекурсией
int add_offer(char choice);                                    //функция выбора, которая предлагает продолжить выполнение программы или нет