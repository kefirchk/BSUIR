#pragma once
#include "CountingMachine.h"               //����������� ������ "CountingMachine"

class PortableCM : public CountingMachine  //����� "����������� ��"
{
protected:
	int batteryCapacity;                //������� ������������
public:

	PortableCM();                       //����������� ��� ����������
	PortableCM(char* Brand, int w, int batCap); //����������� � �����������
	PortableCM(const PortableCM& PCM);  //����������� �����������
	PortableCM(PortableCM&& PCM);      //����������� �����������
	~PortableCM();                      //����������

	PortableCM& operator=(const PortableCM& PCM);   //�������� ������������
	PortableCM& operator=(PortableCM&& PCM);       //�������� ������������ �����������

	void setBatteryCapacity(int); //����� ������� ������� ������������
	int getBatteryCapacity();     //����� ��������� ������� ������������

	virtual void beginOfTable();  //����� ������ ������ �������
	virtual void outputHat();     //����� �������
	virtual void endOfHat();      //����� �����
	virtual void endOfTable();    //����� �������(����������)

	friend ostream& operator<<(ostream& out, const PortableCM& PCM); //�������� << ��� ������
	friend istream& operator>>(istream& in, PortableCM& PCM);        //�������� >> ��� �����
	friend ofstream& operator<<(ofstream& fout, const PortableCM& PCM); //�������� << ��� ������
	friend ifstream& operator>>(ifstream& fin, PortableCM& PCM);        //�������� >> ��� �����
	friend fstream& operator>>(fstream& fin, PortableCM& PCM);
	friend fstream& operator<<(fstream& fout, const PortableCM& PCM);
};
