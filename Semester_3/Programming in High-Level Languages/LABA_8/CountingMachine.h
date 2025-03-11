#pragma once
class CountingMachine //класс "Вычислительная машина"
{
protected:
	char brand[80];   //производитель
	int weight;       //вес
public:
	CountingMachine();                            //конструктор без параметров
	CountingMachine(char* name, int w);           //конструктор с параметрами
	CountingMachine(const CountingMachine& CM);   //конструктор копирования
	CountingMachine(CountingMachine&& CM);       //конструктор перемещения
	~CountingMachine();                           //деструктор

	CountingMachine& operator=(const CountingMachine& CM);   //оператор присваивания
	CountingMachine& operator=(CountingMachine&& CM);       //оператор присваивания перемещения

	void setBrand(const char*);  //метод задания названия марки
	void setWeight(int);   //метод задания веса
	char* getBrand();      //метод получения названия марки
	int getWeight();       //метод получения веса

	virtual void beginOfTable(); //метод вывода начала таблицы
	virtual void outputHat();  //шапка таблицы
	virtual void endOfHat();   //конец шапки
	virtual void endOfTable(); //конец таблицы(подрисовка)

	friend ostream& operator<<(ostream& out, const CountingMachine& CM); //оператор << для вывода
	friend istream& operator>>(istream& in, CountingMachine& CM);        //оператор >> для ввода
	friend ifstream& operator>>(ifstream& fin, CountingMachine& CM);
	friend ofstream& operator<<(ofstream& fout, const CountingMachine& CM);
	friend fstream& operator>>(fstream& fin, CountingMachine& CM);
	friend fstream& operator<<(fstream& fout, const CountingMachine& CM);
};