#include "PCIDevice.h"

PCIDevice::PCIDevice()
{
	devInfo = {};                          // ������������� ��������� ���������, ���� ���������� �� �������
	deviceInfoSet = SetupDiGetClassDevs(   // deviceInfoSet - ����� ���������� �� ����������
		nullptr,						   // ��������� ������ ��������� ���������� (�������������)
		TEXT("PCI"),					   // ������������� ���������� ����������
		nullptr,						   // ���� �������� ������ ���������� ����������������� ���������� (�������������)
		DIGCF_PRESENT | DIGCF_ALLCLASSES); // ��������� ���������� ������ | ��� �������������
}

PCIDevice::~PCIDevice()
{
	SetupDiDestroyDeviceInfoList(deviceInfoSet);
}

string PCIDevice::get_name() {
	char buffer[1024] ;
	if (SetupDiGetDeviceRegistryPropertyA(
		deviceInfoSet,        //����� ���������
		&devInfo,             //���������� ���������� �� ������
		SPDRP_DEVICEDESC,     //����, ��� ������� �������� �������� ����������
		nullptr,              //���������� ��� ������
		(BYTE*)buffer,        //���� �������� ���
		1024,                 //������ ������
		nullptr)              //������� �������� �������� �������������
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