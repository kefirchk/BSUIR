#include "Functions.h"

Exception::Exception(int newCode = -1, const char* newMessage = "")   //конструктор с параметрами
{
	this->code = newCode;
	strcpy_s(this->error_msg, strlen(newMessage) + 1, newMessage);
}
Exception::~Exception()        //деструктор
{}

int Exception::getErrorCode()  //получение кода ошибки
{
	return this->code;
}

void Exception::what()         //метод вывода ошибки с ее кодом
{
	setColor(12);
	cout << this->error_msg << endl;
	setColor(6);
	cout << "КОД ОШИБКИ: " << this->code << endl;
	setColor(7);
}