#pragma once
#include "Functions.h"

class Smartphone : public PortableCM         //класс "Смартфон"
{
	char touchScreen[80];   //тип экрана (IPS, OLED, AMOLED, Tn+Film, PLS, MVA)
	int сameraResolution;   //разрешение камеры(в Мп)
public:
	Smartphone();                            //конструктор без параметров
	Smartphone(char*, int, int, char*, int); //конструктор с параметрами
	Smartphone(const Smartphone &phone);     //конструктор копирования
	Smartphone(Smartphone && phone);         //конструктор перемещения
	~Smartphone();                           //деструктор

	Smartphone& operator=(const Smartphone& phone);   //оператор присваивания
	Smartphone& operator=(Smartphone && phone);       //оператор присваивания перемещения

	void setTouchScreen(char*);              //метод задания типа экрана
	void setCameraResolution(int);           //метод задания разрешения камеры
	char* getTouchScreen();                  //метод получения типа экрана
	int getCameraResolution();               //метод получения разрешения камеры

	virtual void outputHat();  //шапка таблицы
	virtual void endOfTable(); //конец таблицы(подрисовка)

	friend ostream& operator<<(ostream& out, const Smartphone& phone); //оператор << для вывода
	friend istream& operator>>(istream& in, Smartphone& phone);        //оператор >> для ввода
};
