#include <locale.h>    //подключение библиотек
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

#define len 15
//длина строк для имен и фамилий

struct people //структура "люди", используется в двунаправленным кольце
{
	char name[len+1];         //имя человека
	char surname[len+1];      //фамилия человека
	char faculty[len+1];      //факультет
	int group;                //группа
	people* next_person;      //указатель на следующего человека
	people* previous_person;  //указатель на предыдущего человека
};

struct rooms  //структура "комната", используется в однонаправленной очереди
{
	int numberOfRoom;         //номер комнаты
	int countOfPeople;        //количество жильцов
	people* human;            //указатель на двунаправленное кольцо проживающих людей
	rooms* next_room;         //указатель на следующую комнату
};

struct floor  //структура "этаж", используется в двунаправленной очереди
{
	int numberOfFloor;        //номер этажа
	int allPlaces;            //все места на этаже
	int freePlaces;           //свободные места на этаже
	rooms* room;              //указатель на однонаправленную очередь комнат          
	floor* next_floor;        //указатель на следующий этаж
	floor* previous_floor;    //указатель  на предыдущий этаж
};

void menu_add(floor*&, floor*&, int* ms); //функция подменю заселения человека в общежитие
int fun_add(floor*&, floor*&, people*, int *ms, int floorNumber, int roomNumber); //функция заселения человека в общежитие
people* menu_del(floor*&, floor*&);       //функция подменю выселения человека из общежития
int fun_del(floor*&, floor*&, people*, int floorNumber, int roomNumber); //функция выселения человека из общежития
int search_person(floor*&, floor*&, rooms*&, people* person, int , int); //фукнция поиска человека в общежитии
void add_from_queue(floor*&, floor*&, people**, people**, int* ms); //функция заселения человека из очереди на заселение
void set(people**, people**);             //функция ставит человека в очередь на заселение
void move(floor*&, floor*&, int* ms);     //функция переселения человека из одной комнаты в другую
int check_free_places(floor*, int*);      //функция проверки свободных мест в общежитии
void show(floor* tail);                   //функция просмотра информации о заселенных людях с одного этажа
void deleted_plus_queue(people** headHuman, people** tailHuman, people* person); //функция добавления человека в список выселенных людей
void output_deleted(people* tailDeleted); //функция вывода списка выселенных людей

void copy_info(people* &newHuman, people* &person); //функция копирования информации о человеке из одной структуры в другую
floor* memory1();        //функция выделения памяти под этаж
rooms* memory2();        //функция выделения памяти под комнату
people* memory3();       //функция выделения памяти под человека
void input_person_info(people* &person); //функция ввода информации и человеке

int* input_basic_info(); //функция ввода основной информации (количество этажей, количество комнат на этаже, вместимость комнат)
char* input_str();       //функция ввода строки
int input_int();         //функция ввода целого числа
int offer();             //функция решает продолжить или завершить выполнение программы  
void freeAll(floor* &tailFloor, people* &tailHuman, people* &tailDeleted); //функция полностью освобождает память от очередей и кольца
void instructions();     //функция вывода инструкция работы программы
