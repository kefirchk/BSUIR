#pragma once
#include "PortableCM.h"               //подключение класса "PortableCM"

class Smartphone : public PortableCM  //класс "Смартфон"
{
	char touchScreen[80];   //тип экрана (IPS, OLED, AMOLED, Tn+Film, PLS, MVA)
	int сameraResolution;   //разрешение камеры(в Мп)
public:
	Smartphone();                            //конструктор без параметров
	Smartphone(char*, int, int, char*, int); //конструктор с параметрами
	Smartphone(const Smartphone& phone);     //конструктор копирования
	Smartphone(Smartphone&& phone);         //конструктор перемещения
	~Smartphone();                           //деструктор

	Smartphone& operator=(const Smartphone& phone);   //оператор присваивания
	Smartphone& operator=(Smartphone&& phone);       //оператор присваивания перемещения
	bool operator==(Smartphone& phone);
	bool operator<(Smartphone& phone);

	void setTouchScreen(const char*);        //метод задания типа экрана
	void setCameraResolution(int);           //метод задания разрешения камеры
	char* getTouchScreen();                  //метод получения типа экрана
	int getCameraResolution();               //метод получения разрешения камеры

	virtual void beginOfTable(); //метод вывода начала таблицы
	virtual void outputHat();  //метод вывода шапки таблицы
	virtual void endOfHat();   //конец шапки
	virtual void endOfTable(); //метод вывода конца таблицы(подрисовка)
	void edit();               //метод для редактирования параметров объекта
	void choose_search_parametres(); //метод выбора параметров поиска
	void set_parametres(int choice); //метод установки параметров
	void outputClassName();    //метод вывода названия класса
	void cleanSomeFields(Smartphone& phone);
    void set_sort_parametres();

	friend ostream& operator<<(ostream& out, const Smartphone& phone); //оператор << для вывода
	friend istream& operator>>(istream& in, Smartphone& phone);        //оператор >> для ввода
	friend ofstream& operator<<(ofstream& fout, const Smartphone& phone); //оператор << для вывода
	friend ifstream& operator>>(ifstream& fin, Smartphone& phone);        //оператор >> для ввода
	friend fstream& operator>>(fstream& fin, Smartphone& phone);
	friend fstream& operator<<(fstream& fout, const Smartphone& phone);
};

