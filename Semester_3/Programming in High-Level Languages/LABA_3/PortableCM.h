#pragma once
#include "Functions.h"

class PortableCM : public CountingMachine     //����� "����������� ��"
{
protected:
	int batteryCapacity;                //������� ������������
public:

	PortableCM();                       //����������� ��� ����������
	PortableCM(char* Brand, int w, int batCap); //����������� � �����������
	PortableCM(const PortableCM &PCM);  //����������� �����������
	PortableCM(PortableCM && PCM);      //����������� �����������
	~PortableCM();                      //����������

	PortableCM& operator=(const PortableCM& PCM);   //�������� ������������
	PortableCM& operator=(PortableCM && PCM);       //�������� ������������ �����������

	void setBatteryCapacity(int);       //����� ������� ������� ������������
	int getBatteryCapacity();           //����� ��������� ������� ������������

	virtual void outputHat();  //����� �������
	virtual void endOfTable(); //����� �������(����������)

	friend ostream& operator<<(ostream& out, const PortableCM& PCM); //�������� << ��� ������
	friend istream& operator>>(istream& in, PortableCM& PCM);        //�������� >> ��� �����
};
