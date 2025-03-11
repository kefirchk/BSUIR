#pragma once
#include "Libs.h"

class PowerSupply                                // ����� "��������������"
{
private:
	string powerSupplyType;                      // ��� �������������
	int isSaveMode;
	string batteryType;                          // ��� �������
	string powerSavingMode;                      // ������� ����� ����������������
	int batteryLevel;                            // ������� ������ ������� � %
	unsigned long batteryLifeWithoutCharging;              // ����� ������ ������������ ��� ����������� � �������
	unsigned long batteryTimeAfterDisconnectingTheCharger; // ���������� ����� ������ ������������ ����� ���������� ��������� ����������

public:
	void update();
	string getPowerSupplyType(SYSTEM_POWER_STATUS status);
	string getPowerSavingMode();
	string getBatteryChemistry();
	friend ostream& operator<<(ostream& out, PowerSupply battery);
};

