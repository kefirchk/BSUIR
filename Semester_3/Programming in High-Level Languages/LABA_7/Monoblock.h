#pragma once
#include "StationaryCM.h"   //подключение класса "StationaryCM"

class Monoblock : public StationaryCM  //класс "Моноблок"
{
	char mouse[80];         //название компьютерной мышки
	char keyboard[80];      //название клавиатуры
public:

	Monoblock();                                //конструктор без параметров
	Monoblock(char*, int, char*, char*, char*); //конструктор с параметрами
	Monoblock(const Monoblock& SCM);            //конструктор копирования
	Monoblock(Monoblock&& SCM);                //конструктор перемещения
	~Monoblock();                               //деструктор

	Monoblock& operator=(const Monoblock& MonoB); //оператор присваивания
	Monoblock& operator=(Monoblock&& MonoB);     //оператор присваивания перемещения
	bool operator==(Monoblock& MonoB);            //оператор равно
	bool operator<(Monoblock& MonoB);

	void setMouse(const char*);      //метод задания названия мышки
	void setKeyboard(const char*);   //метод задания названия клавиатуры
	char* getMouse();          //метод получения названия мышки
	char* getKeyboard();       //метод получения названия клавиатуры

	virtual void beginOfTable(); //метод вывода начала таблицы
	virtual void outputHat();  //шапка таблицы
	virtual void endOfHat();   //конец шапки
	virtual void endOfTable(); //конец таблицы(подрисовка)
	void edit();               //метод редактирования параметров объекта
	void choose_search_parametres(); //метод выбора параметров поиска
	void set_parametres(int choice); //метод установки параметров
	void outputClassName();    //вывод названия класса
	void cleanSomeFields(Monoblock&);
	void set_sort_parametres();

	friend ostream& operator<<(ostream& out, const Monoblock& MonoB); //оператор << для вывода
	friend istream& operator>>(istream& in, Monoblock& MonoB);        //оператор >> для ввода
	friend ofstream& operator<<(ofstream& fout, const Monoblock& MonoB);
	friend ifstream& operator>>(ifstream& fin, Monoblock& MonoB);
	friend fstream& operator>>(fstream& fin, Monoblock& monoblock);
	friend fstream& operator<<(fstream& fout, const Monoblock& monoblock);
};
