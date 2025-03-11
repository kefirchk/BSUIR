#include "Exception.h"
#include "Interface.cpp"
#include <iostream>
using namespace std;

//======================================EXCEPTION=================================================

Exception::Exception(int newCode = -1, const char* newMessage = "")   //����������� � �����������
{
	this->code = newCode;
	strcpy_s(this->error_msg, strlen(newMessage) + 1, newMessage);
}
Exception::~Exception()        //����������
{}

void Exception::what()         //����� ������ ������ � �� �����
{
	Interface<int> temp;
	temp.setColor(12);
	cout << this->error_msg << endl;
	temp.setColor(6);
	cout << "��� ������: " << this->code << endl;
	temp.setColor(7);
}

//======================================INPUT EXCEPTION===========================================

InputException::InputException(int newCode = -1, const char* newMessage = "", const char* newRemark = "") //����������� 
	: Exception(newCode, newMessage)
{
	strcpy_s(this->remark, strlen(newRemark) + 1, newRemark);
}
InputException::~InputException()      //����������
{}

void InputException::what()            //����� ������ ������ � �� ����� � �����������
{
	Exception::what();
	Interface<int> temp;
	temp.setColor(6);
	cout << "����������: " << this->remark << endl << endl;
	temp.setColor(7);
}

//======================================FILE EXCEPTION============================================

FileException::FileException(int newCode = -1, const char* newMessage = "", const char* newRemark = "") //�����������
: Exception(newCode, newMessage) 
{
	strcpy_s(this->remark, strlen(newRemark) + 1, newRemark);
}
FileException::~FileException()  //�����������
{}

void FileException::what()      //����� ������ ������ � �� ����� � �����������
{
	Exception::what();
	Interface<int> temp;
	temp.setColor(6);
	cout << "����������: " << this->remark << endl << endl;
	temp.setColor(7);
}

//======================================CONTAINER EXCEPTION=======================================

ContainerException::ContainerException(int newCode = -1, const char* newMessage = "", const char* newRemark = "")  //�����������
	: Exception(newCode, newMessage)
{
	strcpy_s(this->remark, strlen(newRemark) + 1, newRemark);
}
ContainerException::~ContainerException()   //����������
{}

void ContainerException::what()             //����� ������ ������ � �� ����� � �����������
{
	Exception::what();
	Interface<int> temp;
	temp.setColor(6);
	cout << "����������: " << this->remark << endl << endl;
	temp.setColor(7);
}

//==========================================================================================