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
	void show_table(BinaryTree<T>& tree); //вывод таблицы элементов

	void add_element(BinaryTree<T>& tree);
	void delete_element(BinaryTree<T>& tree);
	void show_elements(BinaryTree<T>& tree);
	void edit_element(BinaryTree<T>& tree);
	void find_elements(BinaryTree<T>& tree);
};