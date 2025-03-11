#pragma once
#include "Functions.h"

class StationaryCM : public CountingMachine   //класс "Стационарная ВМ"
{
protected:
	char location[80];        //местоположение
public:

	StationaryCM();                          //конструктор без параметров
	StationaryCM(char* Brand, int w, char* Location); //конструктор с параметрами
	StationaryCM(const StationaryCM &SCM);   //конструктор копирования
	StationaryCM(StationaryCM && SCM);       //конструктор перемещения
	~StationaryCM();                         //деструктор

	StationaryCM& operator=(const StationaryCM& SCM);   //оператор присваивания
	StationaryCM& operator=(StationaryCM && SCM);       //оператор присваивания перемещения

	void setLocation(char*);  //метод задания местоположения
	char* getLocation();      //метод получения местоположения

	virtual void outputHat();  //шапка таблицы
	virtual void endOfTable(); //конец таблицы(подрисовка)

	friend ostream& operator<<(ostream& out, const StationaryCM& SCM); //оператор << для вывода
	friend istream& operator>>(istream& in, StationaryCM& SCM);        //оператор >> для ввода
};
