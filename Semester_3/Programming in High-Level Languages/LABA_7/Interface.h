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
	void sort_elements(BinaryTree<T>& tree);
};

enum COLORS
{
	DARK_BLUE = 1,
	DARK_GREEN = 2,
	DARK_TURQUOISE = 3,   //бирюзовый
	DARK_RED = 4,
	DARK_PINK = 5,
	DARK_YELLOW = 6,
	DARK_WHITE = 7,
	DARK_GRAY = 8,
	BLUE = 9,
	GREEN = 10,
	TURQUOISE = 11,
	RED = 12,
	PINK = 13,
	YELLOW = 14,
	WHITE = 15,
	BLACK_on_blue = 16,
	nothing_on_blue = 17,
	GREEN_on_blue = 18,
	TURQUOISE_on_blue = 19,
	RED_on_blue = 20,
	PINK_on_blue = 21,
	YELLOW_on_blue = 22,
	WHITE_on_blue = 23,
	GRAY_on_blue = 24,
	BLUE_on_blue = 25
};