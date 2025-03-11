#pragma once
#include "PortableCM.h"               //����������� ������ "PortableCM"

class Smartphone : public PortableCM  //����� "��������"
{
	char touchScreen[80];   //��� ������ (IPS, OLED, AMOLED, Tn+Film, PLS, MVA)
	int �ameraResolution;   //���������� ������(� ��)
public:
	Smartphone();                            //����������� ��� ����������
	Smartphone(char*, int, int, char*, int); //����������� � �����������
	Smartphone(const Smartphone& phone);     //����������� �����������
	Smartphone(Smartphone&& phone);         //����������� �����������
	~Smartphone();                           //����������

	Smartphone& operator=(const Smartphone& phone);   //�������� ������������
	Smartphone& operator=(Smartphone&& phone);       //�������� ������������ �����������
	bool operator==(Smartphone& phone);
	bool operator<(Smartphone& phone);

	void setTouchScreen(const char*);        //����� ������� ���� ������
	void setCameraResolution(int);           //����� ������� ���������� ������
	char* getTouchScreen();                  //����� ��������� ���� ������
	int getCameraResolution();               //����� ��������� ���������� ������

	virtual void beginOfTable(); //����� ������ ������ �������
	virtual void outputHat();  //����� ������ ����� �������
	virtual void endOfHat();   //����� �����
	virtual void endOfTable(); //����� ������ ����� �������(����������)
	void edit();               //����� ��� �������������� ���������� �������
	void choose_search_parametres(); //����� ������ ���������� ������
	void set_parametres(int choice); //����� ��������� ����������
	void outputClassName();    //����� ������ �������� ������
	void cleanSomeFields(Smartphone& phone);
    void set_sort_parametres();

	friend ostream& operator<<(ostream& out, const Smartphone& phone); //�������� << ��� ������
	friend istream& operator>>(istream& in, Smartphone& phone);        //�������� >> ��� �����
	friend ofstream& operator<<(ofstream& fout, const Smartphone& phone); //�������� << ��� ������
	friend ifstream& operator>>(ifstream& fin, Smartphone& phone);        //�������� >> ��� �����
	friend fstream& operator>>(fstream& fin, Smartphone& phone);
	friend fstream& operator<<(fstream& fout, const Smartphone& phone);
};

