#include <locale.h>         //подключение библиотек
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#define len 15  //длина вводимых слов

union currency  //объединение "валюта"
{
	int dollar; //доллары
	int euro;   //евро
	int RUB;    //российские рубли
	int BYN;    //белорусские рубли
};

struct info     //структура, хранящая информацию о человеке
{
	char name[len + 1];     //имя
	char surname[len + 1];  //фамилия
	int PIN;                //PIN-код пользователя
	currency cash[4];       //структура, хранящая валюту человека
	info* next;             //указатель на следующую структуру
};

void instructions();        //функция выводит инструкции по работе программы
int input_int();            //функция ввода целого числа
char* input_str();          //функция ввода строки
info* input_PIN(info* tail);//функция ввода PIN-кода
int currency_choice();      //функция выбора валюты
int sum_choice();           //функция выбора суммы
int offer();                //функция, которая решает продолжить или завершить выполнение программы  
void clean(info** tail);    //функция очистки очереди

void get_or_push_money(info* tail, info* head, char*, FILE* &f, int); //функция снятия со счета денежных средств
void show_balance(info* tail, info* head, FILE* f, char* fileName);   //функция просмотра баланса
void add_person(info** tail, info** head, char* fileName, FILE* f);   //функция добавления человека в систему
void del_person(info** tail, info** head, info* &element);            //функция удаления человека из системы
int del_in_file(FILE *&f, info *&tail, info* &head, char* fileName);  //функция удаления человека из файла
void transfer_money(info* head, info* tail, char*, FILE* f);          //функция перевода денежных средств с одного счета на другой
void changePIN(info* head, info* tail, char* fileName, FILE* f);      //функция смены PIN-кода

void struct_in_file(char* name, FILE *&f, info* tail);                //фукнция записи структуры в текстовый файл
int file_in_str(info* &tail, info* &head, char* name, FILE *f);       //функция переписи информации из файла в список
void show_file(FILE *f, char* name, info* head, info* tail);          //функция просмотра файла
void replace_file(info*&tail, char* fileName, FILE* &f);              //функция замены файла