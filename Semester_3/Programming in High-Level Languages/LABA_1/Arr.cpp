#include "Arr.h"                  //подключение библиотеки класса Arr
#include "functions.h"            //подключение библиотеки вспомогательных функций

Arr::Arr() {                      //конструктор по умолчанию
	n = 0;                        //размер массива
	ms = nullptr;                 //указатель на массив целых чисел
}
Arr::Arr(int n) {                 //конструктор с параметрами
	ms = new int[n];              //выделение памяти под массив
	this->n = n;                  //установка размера массива
}
Arr::Arr(Arr const &m) {          //конструктор копирования
	n = m.n;                      //копирование размера массива
	ms = new int[n];              //выделение памяти под массив
	for (int i = 0; i < n; i++)   //копирование элементов массива
		ms[i] = m.ms[i]; 
}
Arr& Arr::operator=(Arr const& m) //оператор присваивания
{
	if (this != &m)
	{
		delete[] ms;              //очистка памяти от массива
		n = m.n;                  //присваивание размера массива
		ms = new int[n];          //создание нового массива
		for (int i = 0; i < n; i++) //перепись элементов в новый массив
			ms[i] = m.ms[i];
	}
	return *this;
}

Arr::~Arr() { delete[] ms; }    //деструктор

Arr Arr:: operator+(const Arr &m)
{
	Arr result(n + m.n);        //создание объекта(массива) результата
	int real_length = 0;        //реальная длина массива результата
	for (int i = 0; i < n; i++) //цикл по первому массиву
	{
		if (real_length && result.repeatCheck(real_length, ms[i]))
			continue;           //если такой элемент уже имеется, то пропустить его        
		result.ms[real_length++] = ms[i];   //присваивание элемента
	}
	for (int i = 0; i < m.n; i++)//цикл по второму массиву
	{
		if (real_length && result.repeatCheck(real_length, m.ms[i])) 
			continue;           //если такой элемент уже имеется, то пропустить его        
		result.ms[real_length++] = m.ms[i]; //присваивание элемента
	}
	result.n = real_length;     //корректировка размера массива
	//Arr goodmemres = result;    //создание массива с оптимальным размером выделенной памяти
	//return goodmemres;          //вернуть готовый массив объединения
	return result;
}

int Arr::repeatCheck(int real_length, int elem) //метод для проверки на потворения элементов
{
	for (int j = 0; j < real_length; j++)
	{
		if (ms[j] == elem)  //проверка на повторение элементов
			return 1;       //признак того, что такой элемент уже есть в итоговом массиве
	}
	return 0;               //элемент не был найден в массиве
}

void Arr::input() {                        //метод ввода элементов массива
	for (int i = 0; i < n; i++)            //цикл для ввода элементов массива
		ms[i] = rightInput();              //вызов функции ввода числа с проверкой
}
void Arr::output() {                       //метод вывода массива
	for (int i = 0; i < n; i++)            //цикл по выводу массива на экран
		cout << ms[i] << " ";              //вывод очередного элемента
}

Arr Arr:: unite(Arr m)          //метод объединения массивов
{
	Arr result(n + m.n);        //создание объекта(массива) результата
	int real_length = 0;        //реальная длина массива результата
	for (int i = 0; i < n; i++) //цикл по первому массиву
	{
		if (real_length && result.repeatCheck(real_length, ms[i]))
			continue;           //если такой элемент уже имеется, то пропустить его        
		result.ms[real_length++] = ms[i];   //присваивание элемента
	}
	for (int i = 0; i < m.n; i++)//цикл по второму массиву
	{
		if (real_length && result.repeatCheck(real_length, m.ms[i]))
			continue;           //если такой элемент уже имеется, то пропустить его        
		result.ms[real_length++] = m.ms[i]; //присваивание элемента
	}
	result.n = real_length;     //корректировка размера массива
	Arr goodmemres = result;    //создание массива с оптимальным размером выделенной памяти
	return goodmemres;          //вернуть готовый массив объединения
}

Arr Arr::operator&(const Arr& m)
{
	int maxlen;                //размер, на который будем выделять массив
	if (n > m.n) maxlen = n;
	else maxlen = m.n;
	Arr result(maxlen);        //создание объекта(массива) результата
	int real_length = 0;        //реальная длина массива результата
	for (int i = 0; i < n; i++) //цикл по первому массиву
	{
		for (int j = 0; j < m.n; j++)
		{
			if (ms[i] == m.ms[j])
			{
				if (real_length && result.repeatCheck(real_length, ms[i]))
					continue;           //если такой элемент уже имеется, то пропустить его       
				result.ms[real_length++] = ms[i];   //присваивание элемента		
			}
		}
	}
	result.n = real_length;     //корректировка размера массива
	Arr goodmemres = result;    //создание массива с оптимальным размером выделенной памяти
	return goodmemres;          //вернуть готовый массив объединения
}

//ostream& operator<<(ostream& out, const Arr& obj)
//{
//	out << obj.ms;
//	return out;
//}