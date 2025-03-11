#pragma once
#include "Functions.h"

class Monoblock : public StationaryCM         //класс "Моноблок"
{
	char mouse[80];         //название компьютерной мышки
	char keyboard[80];      //название клавиатуры
public:

	Monoblock();                                //конструктор без параметров
	Monoblock(char*, int, char*, char*, char*); //конструктор с параметрами
	Monoblock(const Monoblock &SCM);            //конструктор копирования
	Monoblock(Monoblock && SCM);                //конструктор перемещения
	~Monoblock();                               //деструктор

	Monoblock& operator=(const Monoblock& MonoB); //оператор присваивания
	Monoblock& operator=(Monoblock && MonoB);     //оператор присваивания перемещения

	void setMouse(char*);     //метод задания названия мышки
	void setKeyboard(char*);  //метод задания названия клавиатуры
	char* getMouse();         //метод получения названия мышки
	char* getKeyboard();      //метод получения названия клавиатуры

	virtual void outputHat();  //шапка таблицы
	virtual void endOfTable(); //конец таблицы(подрисовка)

	friend ostream& operator<<(ostream& out, const Monoblock& MonoB); //оператор << для вывода
	friend istream& operator>>(istream& in, Monoblock& MonoB);        //оператор >> для ввода
};

