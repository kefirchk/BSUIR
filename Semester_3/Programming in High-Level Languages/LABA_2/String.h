#pragma once
#include <iostream>
using namespace std;

class String
{
	char *str;                             //��������� �� ������
public:
	String();                              //����������� ��� ����������
	String(char* ss);                      //����������� � �����������
	String(const String &s);               //����������� �����������
	String(String && s);                   //����������� �����������
	~String();                             //����������

	String& operator=(String && s);        //�������� ������������ �����������
	String& operator=(const String& s);    //�������� = (String = String)
	String& operator=(const char*s);       //�������� ������������ (String = const char[])
	//String& operator=(char*s);            //�������� = (String = char*)
	
	String& operator+=(const String& s);   //�������� += (String += String)

	String& operator+(const String& s);    //�������� + (String + String)
	String& operator+(const char* s);      //�������� + (String + const char[])
	//String& operator+(char* s);            //�������� + (String + char[])
	String& operator+(char symbol);        //�������� + (String + char)
	friend String& operator+(const char* s, String& obj);
	
	bool operator==(const String& s);      //�������� ==
	bool operator!=(const String& s);      //�������� !=
	bool operator>(const String& s);       //�������� >
	bool operator>=(const String& s);      //�������� >=
	bool operator<(const String& s);       //�������� <
	bool operator<=(const String& s);      //�������� <=
	char operator[](int i);                //�������� []
	char* operator()(int begin, int end);  //�������� ()

	friend ostream& operator<<(ostream& out, const String& obj);  //�������� << ��� ������
	friend istream& operator>>(istream& in, String& obj);         //�������� >> ��� �����
	int StrLen();                          //����� ����������� ����� ������ �������

	String& operator++();                  //�������� ++String
	String& operator++(int i);             //�������� String++
	String& operator--();                  //�������� --String
	String& operator--(int i);             //�������� String--
};