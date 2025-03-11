#pragma once
#include "Functions.h"

class Smartphone : public PortableCM         //����� "��������"
{
	char touchScreen[80];   //��� ������ (IPS, OLED, AMOLED, Tn+Film, PLS, MVA)
	int �ameraResolution;   //���������� ������(� ��)
public:
	Smartphone();                            //����������� ��� ����������
	Smartphone(char*, int, int, char*, int); //����������� � �����������
	Smartphone(const Smartphone &phone);     //����������� �����������
	Smartphone(Smartphone && phone);         //����������� �����������
	~Smartphone();                           //����������

	Smartphone& operator=(const Smartphone& phone);   //�������� ������������
	Smartphone& operator=(Smartphone && phone);       //�������� ������������ �����������

	void setTouchScreen(char*);              //����� ������� ���� ������
	void setCameraResolution(int);           //����� ������� ���������� ������
	char* getTouchScreen();                  //����� ��������� ���� ������
	int getCameraResolution();               //����� ��������� ���������� ������

	virtual void outputHat();  //����� �������
	virtual void endOfTable(); //����� �������(����������)

	friend ostream& operator<<(ostream& out, const Smartphone& phone); //�������� << ��� ������
	friend istream& operator>>(istream& in, Smartphone& phone);        //�������� >> ��� �����
};
