#pragma once
#include <iostream>          //подключение библиотеки потока ввода-вывода
#include <iomanip>
#include <windows.h>
#include <limits>
using namespace std;         //использование пространства имён std
#include "CountingMachine.h" //подключение класса "Вычислительная машина"
#include "StationaryCM.h"    //подключение класса "Стационарная ВМ"
#include "PortableCM.h"      //подключение класса "Портативная ВМ"
#include "Monoblock.h"       //подключение класса "Моноблок"
#include "Notebook.h"        //подключение класса "Ноутбук"
#include "Smartphone.h"      //подключение класса "Смартфон"
#include "BinaryTree.cpp"    //подключение класса "Бинарное дерево" и "Узел дерева" 

int get_int(int min, int max);
char get_char(char first, char second);
char* get_str(istream& in);