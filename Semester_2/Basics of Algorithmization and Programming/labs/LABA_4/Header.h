#include <locale.h>    //подключение библиотек
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <io.h>

#define n2 15          //длина строки для записи имени и фамилии человека

union currency         //объединение, содержащее валюты людей
{
	double dollar;     //доллары
	double euro;       //евро
	double RUB;        //российские рубли
	double BYN;        //белорусские рубли
};
union cash             //oбъединение, содержашее количество различной валюты человека и массив выбранных валют
{
	int count;         //количество различной валюты
	int mv[4] = { };   //массив выбранной валюты
};

struct ripo            //структура искомых людей
{
	char name[n2];     //имя
	char surname[n2];  //фамилия
	int age;           //возраст
	double BYN;        //белорусские рубли
};

struct person          //объявление главной структуры
{
	char name[n2];           //имя
	char surname[n2];        //фамилия
	int age;                 //возраст человека
	union cash data[2];      //oбъединение, содержашее количество различной валюты человека и массив выбранных валют
	union currency money[4]; //объединение, содержащее валюты людей
	//struct ripo result[4];   //структура результатов поиска искомых людей
};

void text_file_in_str(int size, FILE *f, person *&man); //функция переписи информации из текстового файла в структуры
void binary_file_in_str(int size, FILE *f, person *&man); //функция переписи информации из бинарного файла в структуры
void struct_in_binary_file(char* name, FILE *f, person* man, char choice, int n); //функция записи структуры в бинарный файл
void struct_in_text_file(char* name, FILE *f, person* man, char choice, int n); //функция записи структуры в текстовый файл
int checkFileOpen(errno_t ff);                   //функция проверки файла на открытие
int menu(person* &, FILE *&f, char*);            //функция выбора режима работы программы
void show_file(char, FILE *f, char*, person*);   //функция вывода содержимого в файле
int file_in_str(person*&, char*, FILE *f, char); //функция переписи информации из файла в массив строк
int del_person(FILE*&, person*&, char*, char);   //функция удаления информации о человеке из файла
person* memory_struct(person* &man, int n);      //функция выделения памяти под массив структур
int input_int(int);                              //функция ввода количества людей
int* currency_choice(person*&, int i, int);      //функция выбора валюты
person* input_info(int n, person* &man);         //функция ввода информации о людях
char* input_str(int i, person*&, int choice);    //функция ввода фамилии или имени
int input_float(double &value);                  //функция ввода валюты или белорусских рублей
void output_table(int n, person *man);           //функция вывода введенной информации о людях
int *poisk1(int n, person *&man, ripo *&);       //функция поиска людей, у которых больше всего и меньше всего белорусских рублей
int *poisk2(int n, person *&man, ripo *&);       //функция поиска самого богатого и самого бедного человека
double perevod(person *man, int i);              //функция перевода валюты в белорусские рубли с прибавлением найденного значения к значению белорусских рублей
void output_result(person*, int*, int*, int n, ripo*);  //функция вывода результата поиска требуемых людей
int offer();                                     //функция предложения продолжить или завершить программу