#include <locale.h>   //подключение библиотек
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#define len 20 

struct pupil           //структура "Ученик"
{
	char imya[len+1];    //имя
	char familia[len+1]; //фамилия
	int clas;          //цифра класса
	char letter;       //буква класса
};

struct pcopy           //копия структуры "Ученик"
{
	char name[len+1];    //имя
	char surname[len+1]; //фамилия
	int number;        //цифра класса
	char bukva;        //буква класса
};

pupil* input_n_and_mem(int &n, pupil *info1);  //функция ввода количества учеников и выделения памяти под массив структур
pupil* give_memory(int n, pupil *&info1, pcopy *&info2, int* &ms, int *&ms2);   //функция выделения памяти на указатели на массив структур
pupil* input_info(int n, pupil* info);         //функция ввода информации о учениках
pupil* input(int i, pupil *info1, int choice); //функция ввода фамилии или имени
void output_table(int n, pupil *info);         //функция вывода введенной информации о учениках
int exercise_a(int n, pupil *info1, int* &ms); //функция поиска однофамильцев
void realloc_ms1(int *&ms1, int size);         //функция перераспределения памяти для массива индексов
void hat_for_ex1(pupil *info, int size, int *ms);    //функция вывода результата поиска однофамильцев
int exercise_b(pupil *info1, int size, int *ms1, int *ms2); //функция поиска однофамильцев в параллельных классах
void realloc_ms2(int *&ms2, int size);         //функция перераспределения памяти для массива индексов
void hat_for_ex2(pupil *info1, int size, int *ms2);  //функция вывода таблицы результатов поиска однофамильцев по параллельным классам
int poisk(int n, pcopy *&info2, pupil *info1); //поиск одноклассников - задание, сделанное на паре
void output_poisk(int t, pcopy *info2);        //функция вывода результата функции поиска одноклассников
void free_memory(pupil *info1, pcopy *info2, int* ms1, int* ms2); //функция освбождения памяти
int offer();                                  //функция, которая предлагает продолжить программу