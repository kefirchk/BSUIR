#pragma once
#include "Functions.h"

class PortableCM : public CountingMachine     //класс "Портативная ВМ"
{
protected:
	int batteryCapacity;                //емкость аккумулятора
public:

	PortableCM();                       //конструктор без параметров
	PortableCM(char* Brand, int w, int batCap); //конструктор с параметрами
	PortableCM(const PortableCM &PCM);  //конструктор копирования
	PortableCM(PortableCM && PCM);      //конструктор перемещения
	~PortableCM();                      //деструктор

	PortableCM& operator=(const PortableCM& PCM);   //оператор присваивания
	PortableCM& operator=(PortableCM && PCM);       //оператор присваивания перемещения

	void setBatteryCapacity(int);       //метод задания емкости аккумулятора
	int getBatteryCapacity();           //метод получения емкости аккумулятора

	virtual void outputHat();  //шапка таблицы
	virtual void endOfTable(); //конец таблицы(подрисовка)

	friend ostream& operator<<(ostream& out, const PortableCM& PCM); //оператор << для вывода
	friend istream& operator>>(istream& in, PortableCM& PCM);        //оператор >> для ввода
};
