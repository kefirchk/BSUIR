#include "Functions.h"

Exception::Exception(int newCode = -1, const char* newMessage = "")   //����������� � �����������
{
	this->code = newCode;
	strcpy_s(this->error_msg, strlen(newMessage) + 1, newMessage);
}
Exception::~Exception()        //����������
{}

int Exception::getErrorCode()  //��������� ���� ������
{
	return this->code;
}

void Exception::what()         //����� ������ ������ � �� �����
{
	setColor(12);
	cout << this->error_msg << endl;
	setColor(6);
	cout << "��� ������: " << this->code << endl;
	setColor(7);
}