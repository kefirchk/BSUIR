#include "String.h"                          //подключение библиотеки с объявлением класса "String"

//===================================================================================
//ВСЕ КОНСТРУКТОРЫ И ДЕСТРУКТОР
//-----------------------------------------------------------------------------------
String::String()                             //конструктор без параметров
{
	str = nullptr;
	
}
String::String(char* ss)                     //конструктор с параметрами
{
	str = new char[strlen(ss) + 1];
	strcpy_s(str, strlen(ss)+1, ss);
}
String::String(const String &s) {            //конструктор копирования
	str = new char[strlen(s.str) + 1];
	strcpy_s(str, strlen(s.str) + 1, s.str);
}
String::~String()                            //деструктор
{
	delete[] str;
}
String::String(String && s) :str(s.str)      //конструктор перемещения
{
	s.str = nullptr;
}

//===================================================================================
//ОПЕРАТОРЫ ПРИСВАИВАНИЯ
//-----------------------------------------------------------------------------------

String& String::operator=(const String& s)   //оператор присваивания (String = String)
{
	if (this != &s)
	{
		delete[] str;
		str = new char[strlen(s.str)+1];
		strcpy_s(str, strlen(s.str) + 1, s.str);
	}
	return *this;
}
String& String::operator=(const char*s)      //оператор присваивания (String = "константная строка")
{
	if (s != str)
	{
		delete[] str;
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	return *this;
}
//String& String::operator=(char*s)           //оператор присваивания (String = s)
//{
//	if (s != str)
//	{
//		delete[] str;
//		str = new char[strlen(s) + 1];
//		strcpy_s(str, strlen(s) + 1, s);
//	}
//	return *this;
//}

String& String::operator=(String && s)               //оператор присваивания перемещения
{
	if (this != &s)
	{
		delete[] str;
		str = s.str;
		s.str = nullptr;
	}
	return *this;
}
//====================================================================================
//ОПЕРАТОР +=
//------------------------------------------------------------------------------------

String& String::operator+=(const String& s)  //оператор +=
{
	char* temp = new char[strlen(s.str) + strlen(str) + 1];
	strcpy_s(temp, strlen(s.str) + strlen(str) + 1, str);
	strcat_s(temp, strlen(s.str) + strlen(str) + 1, s.str);
	delete this->str;
	this->str = temp;
	str[strlen(s.str) + strlen(str) + 1] = '\0';
	return *this;
}
//=====================================================================================
//ОПЕРАТОРЫ +
//-------------------------------------------------------------------------------------

String& String::operator+(const String& s)   //оператор + (String + String)
{
	return *this += s;
}
String& operator+(const char* s, String& obj) //дружественная функция (const string + String)
{
	char* temp = new char[strlen(s) + obj.StrLen()+1];
	strcpy_s(temp, strlen(s) + obj.StrLen() + 1, s);
	strcat_s(temp, strlen(s) + obj.StrLen() + 1, obj.str);
	temp[strlen(s) + obj.StrLen()] = '\0';
	
	obj = temp;
	return obj;
}
String& String::operator+(const char* s)     //оператор + (String + const char[])
{
	char* temp = new char[strlen(s) + strlen(str) + 1];
	strcpy_s(temp, strlen(s) + strlen(str) + 1, str);
	strcat_s(temp, strlen(s) + strlen(str) + 1, s);
	delete this->str;
	this->str = temp;
	str[strlen(s) + strlen(str) + 1] = '\0';
	return *this;
}
//String& String::operator+(char* s)     //оператор + (String + char[])
//{
//	char* temp = new char[strlen(s) + strlen(str) + 1];
//	strcpy_s(temp, strlen(s) + strlen(str) + 1, str);
//	strcat_s(temp, strlen(s) + strlen(str) + 1, s);
//	delete this->str;
//	this->str = temp;
//	str[strlen(s) + strlen(str) + 1] = '\0';
//	return *this;
//}
String& String::operator+(char symbol)  //оператор + (String + char)
{
	char* temp = new char[strlen(str) + 2];
	strcpy_s(temp, strlen(str) + 2, str);
	temp[strlen(str)] = symbol;
	temp[strlen(str) + 1] = '\0';
	delete this->str;
	this->str = temp;
	return *this;
}
//=====================================================================================
//ОПЕРАТОРЫ СРАВНЕНИЯ
//-------------------------------------------------------------------------------------
bool String::operator==(const String& s)       //оператор ==
{ return (bool)!(strcmp(this->str, s.str)); }

bool String::operator!=(const String& s)       //оператор !=
{ return !(*this==(s)); }

bool String::operator>(const String& s)        //оператор >
{ return ((strcmp(str, s.str)) > 0) ? true : false; }

bool String::operator>=(const String& s)       //оператор >=
{ return ((strcmp(str, s.str)) >= 0) ? true : false; }

bool String::operator<(const String& s)        //оператор <
{ return ((strcmp(str, s.str)) < 0) ? true : false; }

bool String::operator<=(const String& s)       //оператор <=
{ return ((strcmp(str, s.str)) <= 0) ? true : false; }
//======================================================================================
//ОПЕРАТОРЫ СКОБКИ
//--------------------------------------------------------------------------------------
char String::operator[](int i)                 //оператор []
{
	return (i >= 0 && i < strlen(str)) ? str[i] : 0;
}
char* String::operator()(int begin, int end)   //оператор ()
{
	char* temp = new char[80];
	int j = 0;
	if (begin >= 0 && end >= 0 && begin < strlen(str) && end < strlen(str))
	{
		for (int i = begin; i <= end; i++, j++) //записываем подстроку в temp
			temp[j] = str[i];
		temp[j] = '\0';
		return temp;
	}
	else return NULL;
}
//======================================================================================
//ДРУЖЕСТВЕННЫЕ ФУНКЦИИ ВВОД-ВЫВОД
//--------------------------------------------------------------------------------------
ostream& operator<<(ostream& out, const String& obj) //оператор << для вывода
{
	out << obj.str;
	return out;
}
istream& operator>>(istream& in, String& obj)        //оператор >> для ввода
{
	char buffer[80];
	//in >> buffer;
	in.getline(buffer, 80);
	//if (obj.str)
	//{
		//delete[] obj.str;
		obj.str = new char[strlen(buffer) + 1];
		strcpy_s(obj.str, strlen(buffer) + 1, buffer);
	//}
	return in;
}
//======================================================================================
//МЕТОДЫ КЛАССА STRING
//--------------------------------------------------------------------------------------
int String::StrLen()      //метод определения длины строки объекта String
{
	return strlen(str);
}

//======================================================================================
//УНАРНЫЕ ОПЕРАТОРЫ ++ 
//--------------------------------------------------------------------------------------
String& String::operator++()
{
	for (int i = 0; i < this->StrLen(); i++)
		str[i]++;
	return *this;
}

String& String::operator++(int i)
{
	++(*this);
	return *this;
}

String& String::operator--()
{
	for (int i = 0; i < this->StrLen(); i++)
		str[i]--;
	return *this;
}

String& String::operator--(int i)
{
	--(*this);
	return *this;
}

//======================================================================================