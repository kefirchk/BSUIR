#pragma once
#include <iostream>
using namespace std;

class Arr {   //класс "ћассив"
public:
	Arr();                             //конструктор по умолчанию
	explicit Arr(int n);               //конструктор с параметрами
	~Arr();                            //деструктор
	Arr(Arr const &m);                 //конструктор копировани€
	Arr& operator=(Arr const& m);      //оператор присваивани€
	Arr operator+(const Arr &m);       //оператор объединени€ массивов

	Arr unite(Arr m);                  //метод объединени€ массивов
	Arr operator&(const Arr& m);
	void input();                      //метод ввода элементов массива
	void output();                     //метод вывода массива
	int repeatCheck(int rl, int elem); //метод дл€ проверки на повторени€ элементов

	//friend ostream& operator<<(ostream& out, const Arr& obj);

private:
	int *ms;  //указатель на массив
	int n;    //размер массива
};