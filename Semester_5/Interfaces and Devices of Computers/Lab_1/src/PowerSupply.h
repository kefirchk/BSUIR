#pragma once
#include "Libs.h"

class PowerSupply                                // класс "Электропитание"
{
private:
	string powerSupplyType;                      // тип энергопитания
	int isSaveMode;
	string batteryType;                          // тип батареи
	string powerSavingMode;                      // текущий режим энергосбережения
	int batteryLevel;                            // уровень заряда батареи в %
	unsigned long batteryLifeWithoutCharging;              // время работы аккумулятора без подключения к зарядке
	unsigned long batteryTimeAfterDisconnectingTheCharger; // оставшееся время работы аккумулятора после отключения зарядного устройства

public:
	void update();
	string getPowerSupplyType(SYSTEM_POWER_STATUS status);
	string getPowerSavingMode();
	string getBatteryChemistry();
	friend ostream& operator<<(ostream& out, PowerSupply battery);
};

