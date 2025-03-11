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
#include "BinFile.cpp"
#include "TxtFile.cpp"

int get_int(int min, int max);
char get_char(char first, char second);
char* get_str(istream& in);
void skip_spaces(ifstream& fin);

template<class T>
const char* choosing_file(T& obj)
{
	string className = typeid(T).name(), filename = PATH;
	if (className == "class Monoblock")
		filename += "Monoblocks";
	else if (className == "class Smartphone")
		filename += "Smartphones";
	else if (className == "class Notebook")
		filename += "Notebooks";
	char* str = new char[filename.size() + 1];
	strcpy_s(str, filename.size() + 1, filename.c_str());
	return str;
}