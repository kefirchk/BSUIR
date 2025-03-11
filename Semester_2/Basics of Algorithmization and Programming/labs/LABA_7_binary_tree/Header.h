#include <locale.h>     //подключение библиотек
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

struct tree             //структура для бинарного дерева
{
	int info;           //информационное поле
	int meeting;        //число встреч элемента в бинарном дереве
	tree *left, *right; //указатель на левое и правое поддерево
};

struct stack            //стек узлов дерева через которые осуществляется движение по ветви 
{
	int flag = 0;       //признак прохождения узла ветвления
	tree *node;         //указаетель на узел дерева  
	stack *next;        //указатель на следующий элемент стека
};

void show_menu(tree *);                  //функция меню просмтора дерева нерекурсивно
void show_recursively(tree*);            //функция просмотра дерева рекурсивно (симметрично)
tree* create_menu(tree*&);               //функция меню создания дерева нерекурсивно
tree* create(tree*&, int);               //функция создания дерева нерекурсивно
tree* create_recursively_menu(tree*&);   //функция меню создания дерева рекурсивно
tree* create_recursively(tree*&, int);   //функция создания дерева рекурсивно
tree* delete_node(tree*&, int element);  //функция удаления узла в дереве
void destroy_tree(tree* &root);          //функция удаления дерева
void Print(tree* root, int lvl);        //функция псевдографического вывода содержимого бинарного дерева
tree* create_example(tree* &root);       //функция рекурсивного создания бинарного дерева по готовому массиву значений

int offer();                             //функция, которая решает продолжить ли выполнение программы  
int input_int();                         //функция ввода целого числа
void instructions();                     //функция вывода инструкций работы программы
