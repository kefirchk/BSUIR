#pragma once
#include "Functions.h"

class Monoblock : public StationaryCM         //����� "��������"
{
	char mouse[80];         //�������� ������������ �����
	char keyboard[80];      //�������� ����������
public:

	Monoblock();                                //����������� ��� ����������
	Monoblock(char*, int, char*, char*, char*); //����������� � �����������
	Monoblock(const Monoblock &SCM);            //����������� �����������
	Monoblock(Monoblock && SCM);                //����������� �����������
	~Monoblock();                               //����������

	Monoblock& operator=(const Monoblock& MonoB); //�������� ������������
	Monoblock& operator=(Monoblock && MonoB);     //�������� ������������ �����������

	void setMouse(char*);     //����� ������� �������� �����
	void setKeyboard(char*);  //����� ������� �������� ����������
	char* getMouse();         //����� ��������� �������� �����
	char* getKeyboard();      //����� ��������� �������� ����������

	virtual void outputHat();  //����� �������
	virtual void endOfTable(); //����� �������(����������)

	friend ostream& operator<<(ostream& out, const Monoblock& MonoB); //�������� << ��� ������
	friend istream& operator>>(istream& in, Monoblock& MonoB);        //�������� >> ��� �����
};

