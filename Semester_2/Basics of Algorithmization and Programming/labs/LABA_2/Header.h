#include <locale.h>   //подключение библиотек
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#define n2 15  //длина имени/фамилии человека

union currency //объединение, содержащее валюты человека
{
	long float dollar; //доллары
	long float euro;   //евро
	long float RUB;    //российские рубли
	long float BYN;    //белорусские рубли
};
union cash     //объединение, содержашее количество различной валюты человека и массив выбранных валют
{
	int count; //количество различной валюты
	int *mv;   //указатель на массив выбранной валюты
};

struct ripo            //структура искомых людей
{
	char name[n2];     //имя
	char surname[n2];  //фамилия
	int age;           //возраст
	long float BYN;    //белорусские рубли
};

struct person  //объявление структуры информации о человеке
{
	char name[n2];           //имя человека
	char surname[n2];        //фамилия человека
	int age;                 //возраст человека
	union cash data[2];      //объединение, содержашее количество различной валюты человека и массив выбранных валют
	union currency money[4]; //объединение, содержащее валюты человека
	struct ripo result[4];   //структура искомых людей
};

person* input_n_and_mem(int &n, person *man);    //функция ввода количества людей и выделения памяти под массив структур
int* currency_choice(person*, int i, int count); //функция выбора валюты
int input_int(int choice);                       //функция ввода количества различных валют
int* mem_for_mv(person *man, int count, int i);  //функция выделения памяти под массив номеров выбранных валют
person* input_info(int n, person* &man);         //функция ввода информации о людях
person* input_str(int i, person*, int choice);   //функция ввода фамилии или имени
int input_float(long float &value);              //функция ввода валюты или белорусских рублей
void output_table(int n, person *man);           //функция вывода введенной информации о людях
int *poisk1(int n, person *man);                 //функция поиска людей, у которых больше всего и меньше всего белорусских рублей
int *poisk2(int n, person *man);                 //функция поиска самого богатого и самого бедного человека
long float perevod(person *man, int i);          //функция перевода валюты в белорусские рубли с прибавлением найденного значения к значению белорусских рублей
void output_result(person*, int*, int*, int n);  //функция вывода результата поиска требуемых людей
void free_memory(int n, person *man);            //функция освобождения памяти
int offer();                                     //функция, которая предлагает продолжить программу