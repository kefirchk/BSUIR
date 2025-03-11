#pragma once
#include "StationaryCM.h"   //����������� ������ "StationaryCM"

class Monoblock : public StationaryCM  //����� "��������"
{
	char mouse[80];         //�������� ������������ �����
	char keyboard[80];      //�������� ����������
public:

	Monoblock();                                //����������� ��� ����������
	Monoblock(char*, int, char*, char*, char*); //����������� � �����������
	Monoblock(const Monoblock& SCM);            //����������� �����������
	Monoblock(Monoblock&& SCM);                //����������� �����������
	~Monoblock();                               //����������

	Monoblock& operator=(const Monoblock& MonoB); //�������� ������������
	Monoblock& operator=(Monoblock&& MonoB);     //�������� ������������ �����������
	bool operator==(Monoblock& MonoB);            //�������� �����
	bool operator<(Monoblock& MonoB);

	void setMouse(const char*);      //����� ������� �������� �����
	void setKeyboard(const char*);   //����� ������� �������� ����������
	char* getMouse();          //����� ��������� �������� �����
	char* getKeyboard();       //����� ��������� �������� ����������

	virtual void beginOfTable(); //����� ������ ������ �������
	virtual void outputHat();  //����� �������
	virtual void endOfHat();   //����� �����
	virtual void endOfTable(); //����� �������(����������)
	void edit();               //����� �������������� ���������� �������
	void choose_search_parametres(); //����� ������ ���������� ������
	void set_parametres(int choice); //����� ��������� ����������
	void outputClassName();    //����� �������� ������
	void cleanSomeFields(Monoblock&);
	void set_sort_parametres();

	friend ostream& operator<<(ostream& out, const Monoblock& MonoB); //�������� << ��� ������
	friend istream& operator>>(istream& in, Monoblock& MonoB);        //�������� >> ��� �����
	friend ofstream& operator<<(ofstream& fout, const Monoblock& MonoB);
	friend ifstream& operator>>(ifstream& fin, Monoblock& MonoB);
	friend fstream& operator>>(fstream& fin, Monoblock& monoblock);
	friend fstream& operator<<(fstream& fout, const Monoblock& monoblock);
};
