#include "Webcam.h"

string Webcam::getData(DWORD property)
{
	char data[256] = "";
	SP_DEVINFO_DATA deviceInfoData = { 0 };
	HDEVINFO deviceInfoSet = SetupDiGetClassDevsA(&GUID_DEVCLASS_CAMERA, "USB", NULL, DIGCF_PRESENT);
	if (deviceInfoSet == INVALID_HANDLE_VALUE) 
	{
		cout << "Error: cannot get device list";
		exit(EXIT_FAILURE);
	}
	deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	SetupDiEnumDeviceInfo( deviceInfoSet, 0, &deviceInfoData);
	SetupDiGetDeviceRegistryPropertyA(deviceInfoSet, &deviceInfoData, property, NULL, (PBYTE)data, sizeof(data), 0);
	SetupDiDestroyDeviceInfoList(deviceInfoSet);
	return string(data);
}

string Webcam::getDriverName()
{
	char driverName[256] = "";
	char driverVersion[256] = "";
	// Получение информации о драйвере устройства захвата видео
	if (!capGetDriverDescriptionA(0, driverName, 255, driverVersion, 255))
		cout << "Error: Webcam driver not found";
	return string(driverName);
}

string Webcam::getDriverVersion()
{
	char driverName[256] = "";
	char driverVersion[256] = "";
	// Получение информации о драйвере устройства захвата видео
	if (!capGetDriverDescriptionA(0, driverName, 255, driverVersion, 255))
		cout << "Error: Webcam driver not found";
	return string(driverVersion);
}
