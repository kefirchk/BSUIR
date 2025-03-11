#include "PCIDevice.h"

PCIDevice::PCIDevice()
{
	devInfo = {};                          // инициализирую начальным значением, чтоб компил€тор не ругалс€
	deviceInfoSet = SetupDiGetClassDevs(   // deviceInfoSet - набор информации об устройстве
		nullptr,						   // указатель класса настройки устройства (необ€зательно)
		TEXT("PCI"),					   // идентификатор экземпл€ра устройства
		nullptr,						   // окно верхнего уровн€ экземпл€ра пользовательского интерфейса (необ€зательно)
		DIGCF_PRESENT | DIGCF_ALLCLASSES); // доступные устройства сейчас | все установленные
}

PCIDevice::~PCIDevice()
{
	SetupDiDestroyDeviceInfoList(deviceInfoSet);
}

string PCIDevice::get_name() {
	char buffer[1024] ;
	if (SetupDiGetDeviceRegistryPropertyA(
		deviceInfoSet,        //набор устройств
		&devInfo,             //конкретное устройство из набора
		SPDRP_DEVICEDESC,     //флаг, при котором получаем описание устройства
		nullptr,              //получаемый тип данных
		(BYTE*)buffer,        //куда записать им€
		1024,                 //размер буфера
		nullptr)              //сколько символов занимает идендификатор
		== false) {  
		system("cls"); cout << "BAD";
		exit(1);
	};            
	return string{buffer};
}

string PCIDevice::get_deviceID() {
	char buffer[1024];
	SetupDiGetDeviceRegistryPropertyA(
		deviceInfoSet, 
		&devInfo, 
		SPDRP_HARDWAREID, 
		nullptr, 
		(BYTE*)buffer, 
		1024, 
		nullptr);
	return string{ buffer }.substr(13, 8);
}

string PCIDevice::get_vendorID() {
	char buffer[1024];
	SetupDiGetDeviceRegistryPropertyA(
		deviceInfoSet,
		&devInfo,
		SPDRP_HARDWAREID,
		nullptr, 
		(BYTE*)buffer,
		1024,
		nullptr);
	return string{ buffer }.substr(4, 8);
}

bool PCIDevice::bind(DWORD index) {
	devInfo.cbSize = sizeof(SP_DEVINFO_DATA);
	return SetupDiEnumDeviceInfo(deviceInfoSet, index, &devInfo);
}