#pragma once
#include "BinaryTree.h"        //подключение класса "Бинарное дерево"

template<class T>
class Interface
{
private:
	char name[30]; //= "Г Л А В Н О Е     М Е Н Ю";
public:
	Interface();               //конструктор
	~Interface() {}            //деструктор
	void mainMenu();           //метод главного меню
	void subMenu(BinaryTree<T>& tree); //метод подменю
	void outputName();         //метод вывода текста "Г Л А В Н О Е     М Е Н Ю"
	void setColor(int color);  //метод задания цвета тексту
};