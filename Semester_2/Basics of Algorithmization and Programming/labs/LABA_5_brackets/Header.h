#include <locale.h>  //подключение библиотек
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#define len 80

struct stack       //структура "Стек"
{
	char bracket;  //поле для хранение скобки
	int index;     //поле для хранения индекса скобки
	stack* next;   //указатель на следующий элемент стека
};

//общие функции
int offer();           //функция выбора, которая решает продолжить ли выполнение программы  
void output_str(char *str, int i);     //функция вывода исходной строки
char* input_str(char); //функция ввода строки
char choose_option();  //функция выбора режима работы программы
void test1(char c, char *&str); //функция проверки выражения без использования стека
void test2(char c, char *&str); //функция проверки выражения с использованием стека
char* del_symbol(int index, char* str);//функция удаления символа в строке
void save(char* &strcopy, char* &str); //функция сохранения изменений в строке

//функции с использованием стека
int check_with_stack(stack *&head, char *str, int);  //функция проверки расстановки скобок с использованием стека
void push(stack **h, char c, int i);   //функция добавления в стек элемента
char pop(stack **s);   //функция удаления последнего элемента стека (с вершины стека)
void show(stack *s);   //функция просмотра элементов стека
void stack_fix(stack *&head, char* &str, int index); //функция предлагает способ исправления ошибки со скобками
char* correct_option_1(stack* head, char* str, int index); //функция исправления ошибочной скобки со стеком(способ 1)
void correct_option_2(stack *&head, char* &str, int index); //функция исправления ошибочной скобки со стеком(способ 2)
int check2(stack* head, int index, char* str, int c); //функция проверки и исправления скобки
char* del(stack *&head, char *str, int index); //функция удаляет неправильные скобки
char* add(stack *&head, char* str, int index); //функция исправляет или добавляет скобки
void error(stack *head, int c); //функция выводит текст об ошибке и состояние стека

//функции без использования стека
void string_fix(char* stack, char *str, int index);   //функция удаления неправильной скобки
int check_without_stack(char *str, int c);    //функция проверки расстановки скобок без использования стека
void correct_without_stack(char* stack, char *str, int index); //функция исправления ошибочной скобки без стека
int check1(char* stack, int index, char* str, int c); //функция проверки и исправления скобки