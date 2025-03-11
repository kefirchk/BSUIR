#include "stdafx.h"

// Print hat of the table
void printHat()
{
	cout << " ";
	for(int i = 0; i < TABLE_WIDTH; ++i)
		cout << "_";
	cout << endl <<
		setw(40) << left << "| Device name" <<
		setw(50) << left << "| Description" <<
		setw(22) << left << "| Producer name" << 
		setw(12) << left << "| Device ID" << 
		setw(12) << left << "| Vendor ID" << "|" << endl;
	cout << "|";
	for(int i = 0; i < TABLE_WIDTH; ++i)
		cout << "=";
	cout << "|" << endl;
}

// Print end of the table
void printEnd()
{
	cout << " ";
	for(int i = 0; i < TABLE_WIDTH; ++i)
		cout << "=";
	cout << endl;
}

// Calculate config register address through bus number, device number, function number and register number
unsigned long calculateAddress(int bus, int dev, int fun, int reg)
{
	unsigned long address = 0;
	address |= (1 << 31)
		       | (bus << 16)
	           | (dev << 11)
	           | (fun << 8)
	           | (reg << 2);
	return address;
}

// Get register data through configAddress
unsigned long getRegisterData(unsigned long configAddress)
{
	unsigned long registerData;
	_outpd(0x0CF8, configAddress);  // write to port 0CF8h (CONFIG_ADDRESS) register address of device
	registerData = _inpd(0x0CFC);   // read register data of device from 0CFCh (CONFIG_DATA) port
	return registerData;
}

// Decoding producer name, device name and class name
char* getDeviceProducerName(unsigned long deviceId, unsigned long vendorId)
{
	// Producer name of device
	for(int i = 0; i < PCI_VENTABLE_LEN; ++i)
		if(PciVenTable[i].VenId == vendorId)
			return PciVenTable[i].VenFull;
	return "UNKNOWN";
}

char* getDeviceChip(unsigned long deviceId, unsigned long vendorId)
{
	// Name of device
	for(int i = 0; i < PCI_DEVTABLE_LEN; ++i)
		if(PciDevTable[i].VenId == vendorId && PciDevTable[i].DevId == deviceId)
			return PciDevTable[i].Chip;
	return "UNKNOWN";
}

char* getDeviceChipDesc(unsigned long deviceId, unsigned long vendorId)
{
	// Description of device
	for(int i = 0; i < PCI_DEVTABLE_LEN; ++i)
		if(PciDevTable[i].VenId == vendorId && PciDevTable[i].DevId == deviceId)
			return PciDevTable[i].ChipDesc;
	return "UNKNOWN";
}
