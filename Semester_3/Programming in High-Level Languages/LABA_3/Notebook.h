#pragma once
#include "Functions.h"

class Notebook : public PortableCM            //����� "�������"
{
	char keyboardBacklight;  //������� ��������� ���������� ("+" - ����, "-" - ���)
	char typeOfNotebook[80];    //��� �������� (��� ������, ��� �����, ��� ����, 
	                         //����������, �������, ���������, ��� ������� � ���������,
	                         //��� ����������������, ������, ��� ���������, 
	                         //��� ���������, ������, �����������, ���������)
public:

	Notebook();                              //����������� ��� ����������
	Notebook(char*, int, int, bool, char*);  //����������� � �����������
	Notebook(const Notebook &phone);         //����������� �����������
	Notebook(Notebook && phone);             //����������� �����������
	~Notebook();                             //����������

	Notebook& operator=(const Notebook& notebook);//�������� ������������
	Notebook& operator=(Notebook && notebook);    //�������� ������������ �����������

	void setKeyboardBacklight(char);         //����� ������� ������� ��������� ����������
	void setTypeOfNotebook(char*);           //����� ������� ���� ��������
	bool getKeyboardBacklight();             //����� ��������� ������ � ������� ��������� ����������
	char* getTypeOfNotebook();               //����� ��������� ���� ��������

	virtual void outputHat();  //����� �������
	virtual void endOfTable(); //����� �������(����������)

	friend ostream& operator<<(ostream& out, const Notebook& phone); //�������� << ��� ������
	friend istream& operator>>(istream& in, Notebook& phone);        //�������� >> ��� �����
};