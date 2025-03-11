#pragma once
#include "PortableCM.h"             //подключение класса "PortableCM"

class Notebook : public PortableCM  //класс "Ноутбук"
{
	char keyboardBacklight;  //наличие подсветки клавиатуры ("+" - есть, "-" - нет)
	char typeOfNotebook[80]; //тип ноутбука (для работы, для учебы, для дома, 
							 //компактный, игровой, ультрабук, для фильмов и интернета,
							 //для программирования, мощный, для дизайнера, 
							 //для фотографа, нетбук, трансформер, бесшумный)
public:
	Notebook();                              //конструктор без параметров
	Notebook(char*, int, int, char, char*);  //конструктор с параметрами
	Notebook(const Notebook& phone);         //конструктор копирования
	Notebook(Notebook&& phone);             //конструктор перемещения
	~Notebook();                             //деструктор

	Notebook& operator=(const Notebook& notebook);//оператор присваивания
	Notebook& operator=(Notebook&& notebook);    //оператор присваивания перемещения
	bool operator==(Notebook& notebook);          //оператор равно
	bool operator<(Notebook& notebook);

	void setKeyboardBacklight(char);         //метод задания наличия подсветки клавиатуры
	void setTypeOfNotebook(const char*);     //метод задания типа ноутбука
	char getKeyboardBacklight();             //метод получения данных о наличии подсветки клавиатуры
	char* getTypeOfNotebook();               //метод получения типа ноутбука

	virtual void beginOfTable(); //метод вывода начала таблицы
	virtual void outputHat();  //шапка таблицы
	virtual void endOfHat();   //конец шапки
	virtual void endOfTable(); //конец таблицы(подрисовка)
	void edit();               //метод для редактирования параметров объекта
	void choose_search_parametres(); //метод выбора параметров поиска
	void set_parametres(int choice); //метод установки параметров
	void outputClassName();    //метод вывода названия класса
	void cleanSomeFields(Notebook&);
	void set_sort_parametres();

	friend ostream& operator<<(ostream& out, const Notebook& phone); //оператор << для вывода
	friend istream& operator>>(istream& in, Notebook& phone);        //оператор >> для ввода
	friend ofstream& operator<<(ofstream& fout, const Notebook& notebook); //оператор << для вывода
	friend ifstream& operator>>(ifstream& fin, Notebook& notebook);       //оператор >> для ввода
	friend fstream& operator>>(fstream& fin, Notebook& notebook);
	friend fstream& operator<<(fstream& fout, const Notebook& notebook);
};

