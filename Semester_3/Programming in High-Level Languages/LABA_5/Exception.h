#pragma once
/*                                      _________
*                                      |Exception|
*                                      /    |    \
*                         ____________/     |     \____________
*                 _______|______      ______|______      ______|___________
*                |InputException|    |FileException|    |ContainerException|
*/
//======================================EXCEPTION=================================================

class Exception
{
protected:
	int code;             //код ошибки
	char error_msg[20];   //сообщение об ошибке
public:
	Exception(int, const char*);   //конструктор
	~Exception();         //деструктор
	virtual void what();  //метод вывода ошибки с ее кодом и примечанием
};

//======================================INPUT EXCEPTION===========================================

class InputException : public Exception
{
private:
	char remark[80];      //примечание к ошибке
public:
	InputException(int, const char*, const char*); //конструктор
	~InputException();    //деструктор
	virtual void what();  //метод вывода ошибки с ее кодом и примечанием
};

//======================================FILE EXCEPTION============================================

class FileException : public Exception
{
private:
	char remark[80];      //примечание к ошибке
public:
	FileException(int, const char*, const char*); //конструктор
	~FileException();     //деструктор
	virtual void what();  //метод вывода ошибки с ее кодом и примечанием
};

//======================================CONTAINER EXCEPTION=======================================

class ContainerException : public Exception
{
private:
	char remark[80];       //примечаение к ошибке
public:
	ContainerException(int, const char*, const char*); //конструктор
	~ContainerException(); //деструктор
	virtual void what();   //метод вывода ошибки с ее кодом и примечанием
};

