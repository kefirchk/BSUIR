#pragma once
#include "CountingMachine.h"  //����������� ������ "CountingMachine"

class StationaryCM : public CountingMachine   //����� "������������ ��"
{
protected:
	char location[80];        //��������������
public:

	StationaryCM();                          //����������� ��� ����������
	StationaryCM(char* Brand, int w, char* Location); //����������� � �����������
	StationaryCM(const StationaryCM& SCM);   //����������� �����������
	StationaryCM(StationaryCM&& SCM);       //����������� �����������
	~StationaryCM();                         //����������

	StationaryCM& operator=(const StationaryCM& SCM);   //�������� ������������
	StationaryCM& operator=(StationaryCM&& SCM);       //�������� ������������ �����������

	void setLocation(const char*);   //����� ������� ��������������
	char* getLocation();       //����� ��������� ��������������

	virtual void beginOfTable(); //����� ������ ������ �������
	virtual void outputHat();  //����� ������ ����� �������
	virtual void endOfHat();   //����� �����
	virtual void endOfTable(); //����� ������ ����� �������(����������)

	friend ostream& operator<<(ostream& out, const StationaryCM& SCM); //�������� << ��� ������
	friend istream& operator>>(istream& in, StationaryCM& SCM);        //�������� >> ��� �����
	friend ofstream& operator<<(ofstream& fout, const StationaryCM& SCM); //�������� << ��� ������
	friend ifstream& operator>>(ifstream& fin, StationaryCM& SCM);        //�������� >> ��� �����
	friend fstream& operator>>(fstream& fin, StationaryCM& SCM);
	friend fstream& operator<<(fstream& fout, const StationaryCM& SCM);
};