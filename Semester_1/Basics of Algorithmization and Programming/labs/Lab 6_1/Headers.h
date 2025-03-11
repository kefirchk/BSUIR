#include <windows.h>                                        //подключение библиотек
#include <locale.h>
#include <stdio.h>                                            
#include <stdlib.h>
#include <conio.h>

int input_n(int &n, char &choice);                          //функция ввода натурального числа n
char* memory_s(int &n, char* &str_s);                       //функция выделения памяти под строку s
char* memory_a(int &n, char* &str_a);                       //функция выделения памяти под строку а
void input_stroka_s(char* &str_s, int &n);                  //функция ввода строки s 
void input_stroka_a(char* &str_a, int &n);                  //функция ввода строки а
char* memory_del_elements(int n, char* str_del);            //функция выделения памяти под удаленные символы
int choose_str(int number_str);                             //функция выбора строки, которую нужно преобразовывать
void algorithm(char* str_s, char* str_a, int &n, char* str_del, int &k);   //функция удаления из строки всех символов, которые есть в другой строке
void output_main_result(int &k, char* str_s, char* str_a, char* str_del, int number_str);//функиця вывода преобразованной строки s
char add_offer_for_del(char &c);                            //функция предлагает вывести удаленные символы
void output_del_elements(char* str_del, int number_str);    //функция вывода удаленных символов
void clean_memory(char* &str_s, char* &str_a, char* &str_del); //функция освобожения памяти от указателей на строки
void add_offer(char choice);                                //функция выбора, которая решает продолжить ли выполнение программы или нет