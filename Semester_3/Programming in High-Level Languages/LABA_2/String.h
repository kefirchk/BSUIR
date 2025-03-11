#pragma once
#include <iostream>
using namespace std;

class String
{
	char *str;                             //указатель на строку
public:
	String();                              //конструктор без параметров
	String(char* ss);                      //конструктор с параметрами
	String(const String &s);               //конструктор копирования
	String(String && s);                   //конструктор перемещения
	~String();                             //деструктор

	String& operator=(String && s);        //оператор присваивания перемещения
	String& operator=(const String& s);    //оператор = (String = String)
	String& operator=(const char*s);       //оператор присваивания (String = const char[])
	//String& operator=(char*s);            //оператор = (String = char*)
	
	String& operator+=(const String& s);   //оператор += (String += String)

	String& operator+(const String& s);    //оператор + (String + String)
	String& operator+(const char* s);      //оператор + (String + const char[])
	//String& operator+(char* s);            //оператор + (String + char[])
	String& operator+(char symbol);        //оператор + (String + char)
	friend String& operator+(const char* s, String& obj);
	
	bool operator==(const String& s);      //оператор ==
	bool operator!=(const String& s);      //оператор !=
	bool operator>(const String& s);       //оператор >
	bool operator>=(const String& s);      //оператор >=
	bool operator<(const String& s);       //оператор <
	bool operator<=(const String& s);      //оператор <=
	char operator[](int i);                //оператор []
	char* operator()(int begin, int end);  //оператор ()

	friend ostream& operator<<(ostream& out, const String& obj);  //оператор << для вывода
	friend istream& operator>>(istream& in, String& obj);         //оператор >> для ввода
	int StrLen();                          //метод определения длины строки объекта

	String& operator++();                  //оператор ++String
	String& operator++(int i);             //оператор String++
	String& operator--();                  //оператор --String
	String& operator--(int i);             //оператор String--
};