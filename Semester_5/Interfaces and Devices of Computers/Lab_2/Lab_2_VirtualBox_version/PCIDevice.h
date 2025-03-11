#pragma once
#include "Libs.h"

class PCIDevice
{
private:
	HDEVINFO deviceInfoSet;   // набор информации об устройстве
	SP_DEVINFO_DATA devInfo;  // информация об устройстве из всего набора информации

public:
	PCIDevice();
	~PCIDevice();
	string get_name();
	string get_deviceID();
	string get_vendorID();
	bool bind(DWORD index);
};

