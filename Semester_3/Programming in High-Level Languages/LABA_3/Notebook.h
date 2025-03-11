#pragma once
#include "Functions.h"

class Notebook : public PortableCM            //класс "Ноутбук"
{
	char keyboardBacklight;  //наличие подсветки клавиатуры ("+" - есть, "-" - нет)
	char typeOfNotebook[80];    //тип ноутбука (для работы, для учебы, для дома, 
	                         //компактный, игровой, ультрабук, для фильмов и интернета,
	                         //для программирования, мощный, для дизайнера, 
	                         //для фотографа, нетбук, трансформер, бесшумный)
public:

	Notebook();                              //конструктор без параметров
	Notebook(char*, int, int, bool, char*);  //конструктор с параметрами
	Notebook(const Notebook &phone);         //конструктор копирования
	Notebook(Notebook && phone);             //конструктор перемещения
	~Notebook();                             //деструктор

	Notebook& operator=(const Notebook& notebook);//оператор присваивания
	Notebook& operator=(Notebook && notebook);    //оператор присваивания перемещения

	void setKeyboardBacklight(char);         //метод задания наличия подсветки клавиатуры
	void setTypeOfNotebook(char*);           //метод задания типа ноутбука
	bool getKeyboardBacklight();             //метод получения данных о наличии подсветки клавиатуры
	char* getTypeOfNotebook();               //метод получения типа ноутбука

	virtual void outputHat();  //шапка таблицы
	virtual void endOfTable(); //конец таблицы(подрисовка)

	friend ostream& operator<<(ostream& out, const Notebook& phone); //оператор << для вывода
	friend istream& operator>>(istream& in, Notebook& phone);        //оператор >> для ввода
};