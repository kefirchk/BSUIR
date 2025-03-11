#pragma once
class Exception
{
protected:
	int code;             //код ошибки
	char error_msg[40];   //сообщение об ошибке
public:
	Exception(int, const char*);   //конструктор
	int getErrorCode();   //получить код ошибки
	~Exception();         //деструктор
	virtual void what();  //метод вывода ошибки с ее кодом и примечанием
};
