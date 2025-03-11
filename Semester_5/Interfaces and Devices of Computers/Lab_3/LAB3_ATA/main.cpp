#include "Libs.h"
#include "hexioctrl.h"
#include "(PCI_DEVS)pci_codes.h"
#include "ATADevice.h"

void setColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

int main()
{
	ALLOW_IO_OPERATIONS;

	ATADevice disk;
	printHat();

	// Iterate through all possible ATA devices
	for(int channel = 0; channel < 1; ++channel)
		for (int device = 0; device < 2; ++device)
		{
			disk.setChannel(channel);
			disk.setDevice(device);
			bool ok = disk.initialize();
			if (ok == true) {
				disk.printProducer();
				disk.printModel();
				disk.printSerialNumber();
				disk.printFirmwareVersion();
				disk.printMemorySize();
				disk.printInterfaceType();
				disk.printSupportedMultiwordDMA();
				disk.printSupportedPIO();
				disk.printSupportedUltraDMA();
				printEnd();
			}
		}
	system("pause");

	return 0;
}
