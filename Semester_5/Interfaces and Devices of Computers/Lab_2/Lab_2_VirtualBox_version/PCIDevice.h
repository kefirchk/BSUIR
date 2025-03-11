#pragma once
#include "Libs.h"

class PCIDevice
{
private:
	HDEVINFO deviceInfoSet;   // ����� ���������� �� ����������
	SP_DEVINFO_DATA devInfo;  // ���������� �� ���������� �� ����� ������ ����������

public:
	PCIDevice();
	~PCIDevice();
	string get_name();
	string get_deviceID();
	string get_vendorID();
	bool bind(DWORD index);
};

