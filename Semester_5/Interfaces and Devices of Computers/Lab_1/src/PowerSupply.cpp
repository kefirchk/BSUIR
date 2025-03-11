#include "PowerSupply.h"

void PowerSupply::update()
{
	SYSTEM_POWER_STATUS status;
	GetSystemPowerStatus(&status);
	this->powerSupplyType = getPowerSupplyType(status);
	this->batteryLevel = status.BatteryLifePercent;
	this->batteryType = getBatteryChemistry();
	isSaveMode = status.SystemStatusFlag;
	this->powerSavingMode = getPowerSavingMode();
	this->batteryLifeWithoutCharging = status.BatteryLifeTime;
	this->batteryTimeAfterDisconnectingTheCharger = status.BatteryFullLifeTime / (3600 * 24 * 365) ;
}

string PowerSupply::getPowerSupplyType(SYSTEM_POWER_STATUS status) 
{
	switch (status.ACLineStatus)
	{
	case 0: return "Battery"; // ������� �� ������������
	case 1: return "Mains";   // ������� �� ����
	default: return "Unknown"; // ����������
	}
}

string PowerSupply::getPowerSavingMode() {
	if(isSaveMode == 1)
		return "On";
	else
		return "Off";
}

string PowerSupply::getBatteryChemistry() 
{	
	string batteryType;

	HDEVINFO DeviceInfoSet = SetupDiGetClassDevs( // �������� ���������� ������ ����������� ���� ���������
		&GUID_DEVCLASS_BATTERY,                   // ����� ��������� �������(�� ���������)
		NULL,                                     // �������������� ��������
		NULL,                                     // ���������� ���� �������� ������, ������� ����� �������������� 
												  // ��� ����������������� ����������, ���������� � ���������� 
												  // ���������� ���������� � ������ ���������� �� ����������.
												  // ���� ���������� �� �������� ������������ � ����� ����� �������� NULL.
		DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);	  // ������ �� ����������, ������� � ������ ������ ������������ � ������� �
												  // ������� ���������, �������������� ���������� ��������� ��� ��������� ������� ����������� ���������

	if (DeviceInfoSet)
	{
		SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
		DeviceInterfaceData.cbSize = sizeof(DeviceInterfaceData); // ��� ��������� � SetupDiGetDeviceInterfaceDatail �������� NULL

		// ����������� ���������� ����������, ������������ � ������ ���������� �� ����������
		SetupDiEnumDeviceInterfaces(DeviceInfoSet, 0, &GUID_DEVCLASS_BATTERY, 0, &DeviceInterfaceData); 

		DWORD cbRequired = 0;
		// ���������� �������� �� ���������� ���������� � ��������� cbRequired
		SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, NULL, 0, &cbRequired, 0); 

		// �������� ���� � ���������� ����������
		PSP_DEVICE_INTERFACE_DETAIL_DATA pdidd = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, cbRequired); // �������� ��������� ���������� ������ �� ����
																												 // ��� ����. ������ ������ � ������������ ������
		if (pdidd)
		{
			pdidd->cbSize = sizeof(*pdidd);
			// ���������� �������� �� ���������� ����������
			SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, pdidd, cbRequired, &cbRequired, 0);

			// ������� ��� ��������� ���� ��� ���������� �����-������
			HANDLE batteryHandle = CreateFile(pdidd->DevicePath,  // ��� �����
				GENERIC_READ | GENERIC_WRITE,					  // ����������� ������ � �����
				FILE_SHARE_READ | FILE_SHARE_WRITE,				  // ����������� ����� ������ ������� � ����� ��� ����������
				NULL,											  // ����� ������������
				OPEN_EXISTING,								      // ��������, ������� ����� ���������
				FILE_ATTRIBUTE_NORMAL,							  // ����� � �������� ���������� (������� �� ���������)
				NULL);											  // ��� �������������� ������ � ���������
 
			BATTERY_QUERY_INFORMATION bqi = { 0 };  // �������� ���������� � ������� �������
			
			// ���������� ����������� ��� ��������������� ���������� �������� ����������, ��������� ��������������� ���������� ��������� ��������������� ��������.
			DeviceIoControl(batteryHandle,           
				IOCTL_BATTERY_QUERY_TAG,            // �������� ��� �������
				NULL, NULL, &bqi.BatteryTag, sizeof(bqi.BatteryTag), NULL, NULL);

			BATTERY_INFORMATION bi;                 // ����� �������� ���������� � �������
			DeviceIoControl(batteryHandle, IOCTL_BATTERY_QUERY_INFORMATION, &bqi, sizeof(bqi), &bi, sizeof(bi), NULL, NULL);

			batteryType = reinterpret_cast<char*>(bi.Chemistry);

			CloseHandle(batteryHandle);             // ��������� ����������
			LocalFree(pdidd);                       // ����������� ������
		}
		SetupDiDestroyDeviceInfoList(DeviceInfoSet);
	}

	return batteryType.substr(0, 4);
	
}

ostream& operator<<(ostream& out, PowerSupply powerSupply)
{
	unsigned long hours = powerSupply.batteryLifeWithoutCharging / 3600;
	unsigned long minutes = (powerSupply.batteryLifeWithoutCharging % 3600) / 60;
	unsigned long seconds = powerSupply.batteryLifeWithoutCharging % 60;
	string time = "" + to_string(hours) + "h:" + to_string(minutes) + "m:" + to_string(seconds) + "s";
	if (powerSupply.batteryLifeWithoutCharging == ULONG_MAX)
		time = "infitiny";
	
	out << setw(10) << "|Type of power supply             |" << setw(12) << left << powerSupply.powerSupplyType << "|" << endl
		<< setw(10) << "|Type of battery                  |" << setw(12) << left << powerSupply.batteryType << "|" << endl
		<< setw(10) << "|Battery level, %                 |" << setw(12) << left << powerSupply.batteryLevel << "|" << endl
		<< setw(10) << "|Current power saving mode        |" << setw(12) << left << powerSupply.powerSavingMode << "|" << endl
		<< setw(10) << "|Battery life without charging    |" << setw(12) << left << time << "|" << endl;
		//<< setw(10) << "|Remaining battery time after     |" << setw(12) << left << powerSupply.batteryTimeAfterDisconnectingTheCharger << "|" << endl
		//<< setw(10) << "|disconnecting the charger, years |" << setw(13) << right << "|" << endl;
	return out;
}