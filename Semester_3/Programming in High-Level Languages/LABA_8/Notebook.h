#pragma once
#include "PortableCM.h"             //����������� ������ "PortableCM"

class Notebook : public PortableCM  //����� "�������"
{
	char keyboardBacklight;  //������� ��������� ���������� ("+" - ����, "-" - ���)
	char typeOfNotebook[80]; //��� �������� (��� ������, ��� �����, ��� ����, 
							 //����������, �������, ���������, ��� ������� � ���������,
							 //��� ����������������, ������, ��� ���������, 
							 //��� ���������, ������, �����������, ���������)
public:
	Notebook();                              //����������� ��� ����������
	Notebook(char*, int, int, char, char*);  //����������� � �����������
	Notebook(const Notebook& phone);         //����������� �����������
	Notebook(Notebook&& phone);             //����������� �����������
	~Notebook();                             //����������

	Notebook& operator=(const Notebook& notebook);//�������� ������������
	Notebook& operator=(Notebook&& notebook);    //�������� ������������ �����������
	bool operator==(Notebook& notebook);          //�������� �����
	bool operator<(Notebook& notebook);

	void setKeyboardBacklight(char);         //����� ������� ������� ��������� ����������
	void setTypeOfNotebook(const char*);     //����� ������� ���� ��������
	char getKeyboardBacklight();             //����� ��������� ������ � ������� ��������� ����������
	char* getTypeOfNotebook();               //����� ��������� ���� ��������

	virtual void beginOfTable(); //����� ������ ������ �������
	virtual void outputHat();  //����� �������
	virtual void endOfHat();   //����� �����
	virtual void endOfTable(); //����� �������(����������)
	void edit();               //����� ��� �������������� ���������� �������
	void choose_search_parametres(); //����� ������ ���������� ������
	void set_parametres(int choice); //����� ��������� ����������
	void outputClassName();    //����� ������ �������� ������
	void cleanSomeFields(Notebook&);
	void set_sort_parametres();

	friend ostream& operator<<(ostream& out, const Notebook& phone); //�������� << ��� ������
	friend istream& operator>>(istream& in, Notebook& phone);        //�������� >> ��� �����
	friend ofstream& operator<<(ofstream& fout, const Notebook& notebook); //�������� << ��� ������
	friend ifstream& operator>>(ifstream& fin, Notebook& notebook);       //�������� >> ��� �����
	friend fstream& operator>>(fstream& fin, Notebook& notebook);
	friend fstream& operator<<(fstream& fout, const Notebook& notebook);
};

