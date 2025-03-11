#include "Exception.h"
#include "Interface.cpp"
#include <iostream>
using namespace std;

//======================================EXCEPTION=================================================

Exception::Exception(int newCode = -1, const char* newMessage = "")   //конструктор с параметрами
{
	this->code = newCode;
	strcpy_s(this->error_msg, strlen(newMessage) + 1, newMessage);
}
Exception::~Exception()        //деструктор
{}

void Exception::what()         //метод вывода ошибки с ее кодом
{
	Interface<int> temp;
	temp.setColor(12);
	cout << this->error_msg << endl;
	temp.setColor(6);
	cout << "КОД ОШИБКИ: " << this->code << endl;
	temp.setColor(7);
}

//======================================INPUT EXCEPTION===========================================

InputException::InputException(int newCode = -1, const char* newMessage = "", const char* newRemark = "") //конструктор 
	: Exception(newCode, newMessage)
{
	strcpy_s(this->remark, strlen(newRemark) + 1, newRemark);
}
InputException::~InputException()      //деструктор
{}

void InputException::what()            //метод вывода ошибки с ее кодом и примечанием
{
	Exception::what();
	Interface<int> temp;
	temp.setColor(6);
	cout << "ПРИМЕЧАНИЕ: " << this->remark << endl << endl;
	temp.setColor(7);
}

//======================================FILE EXCEPTION============================================

FileException::FileException(int newCode = -1, const char* newMessage = "", const char* newRemark = "") //конструктор
: Exception(newCode, newMessage) 
{
	strcpy_s(this->remark, strlen(newRemark) + 1, newRemark);
}
FileException::~FileException()  //декструктор
{}

void FileException::what()      //метод вывода ошибки с ее кодом и примечанием
{
	Exception::what();
	Interface<int> temp;
	temp.setColor(6);
	cout << "ПРИМЕЧАНИЕ: " << this->remark << endl << endl;
	temp.setColor(7);
}

//======================================CONTAINER EXCEPTION=======================================

ContainerException::ContainerException(int newCode = -1, const char* newMessage = "", const char* newRemark = "")  //конструктор
	: Exception(newCode, newMessage)
{
	strcpy_s(this->remark, strlen(newRemark) + 1, newRemark);
}
ContainerException::~ContainerException()   //деструктор
{}

void ContainerException::what()             //метод вывода ошибки с ее кодом и примечанием
{
	Exception::what();
	Interface<int> temp;
	temp.setColor(6);
	cout << "ПРИМЕЧАНИЕ: " << this->remark << endl << endl;
	temp.setColor(7);
}

//==========================================================================================