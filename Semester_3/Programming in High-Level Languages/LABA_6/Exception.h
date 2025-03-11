#pragma once
/*                                      _________
*                                      |Exception|
*                                      /    |    \
*                         ____________/     |     \____________
*                 _______|______      ______|______      ______|___________
*                |InputException|    |FileException|    |ContainerException|
*/
//======================================EXCEPTION=================================================
#include <map>

class Exception
{
protected:
	int code;             //��� ������
	char error_msg[40];   //��������� �� ������
public:
	Exception(int, const char*);   //�����������
	~Exception();         //����������
	virtual void what();  //����� ������ ������ � �� ����� � �����������
};

//======================================INPUT EXCEPTION===========================================

class InputException : public Exception
{
private:
	char remark[80];      //���������� � ������
public:
	InputException(int, const char*, const char*); //�����������
	~InputException();    //����������
	virtual void what();  //����� ������ ������ � �� ����� � �����������
};

//======================================FILE EXCEPTION============================================

class FileException : public Exception
{
private:
	char remark[80];      //���������� � ������
public:
	FileException(int, const char*, const char*); //�����������
	~FileException();     //����������
	virtual void what();  //����� ������ ������ � �� ����� � �����������
};

//======================================CONTAINER EXCEPTION=======================================

class ContainerException : public Exception
{
private:
	char remark[80];       //����������� � ������
public:
	ContainerException(int, const char*, const char*); //�����������
	~ContainerException(); //����������
	virtual void what();   //����� ������ ������ � �� ����� � �����������
};
