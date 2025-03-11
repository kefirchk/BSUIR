#include "stdafx.h"

int main(int argc, char* argv[])
{
	ALLOW_IO_OPERATIONS
	printHat();

	unsigned long configAddress,
				  registerData,
				  deviceId,
				  vendorId;

	for(int bus = 0; bus <= PCI_MAX_BUS; ++bus)
		for(int dev = 0; dev <= PCI_MAX_DEV; ++dev)
			for(int fun = 0; fun <= PCI_MAX_FUN; ++fun)
			{
				configAddress = calculateAddress(bus, dev, fun, 0x00); // get register address for config circle
				registerData = getRegisterData(configAddress);

				if(registerData != -1) // if device with such addrees exist
				{
					// Get Device ID and Vendor ID from register of 0x00
					deviceId = registerData >> 16;
					vendorId = registerData - (deviceId << 16);

					cout << "| " << setw(38) << left << getDeviceChip(deviceId, vendorId)
						<< "| " << setw(48) << left << getDeviceChipDesc(deviceId, vendorId)
						<< "| " << setw(20) << left << getDeviceProducerName(deviceId, vendorId)
						<< "| " << setw(10) << left << deviceId
						<< "| " << setw(10) << left << vendorId << "|" << endl;
				}
			}

	printEnd();
	system("pause");
	return 0;
}