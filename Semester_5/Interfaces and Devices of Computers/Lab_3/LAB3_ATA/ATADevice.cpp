#include "ATADevice.h"


void ATADevice::setChannel(int newChannel)
{
	this->channel = newChannel;
}


void ATADevice::setDevice(int newDevice)
{
	this->device = newDevice;
}


bool ATADevice::initialize()
{
	const WORD DH[2] = {DH_1, DH_2};
	const WORD CR[2] = {CR_1, CR_2};
	const WORD SR[2] = {SR_1, SR_2};
	const WORD DR[2] = {DR_1, DR_2};

	waitBusy();

	// Choose ATA device
	_outpd(DH[channel], (device << 4) | 0xE0); // 00010000 | 11100000, 7 and 5 bits must be '1', 6 bit - using LBA addressing

	// Wait for ready of device if device is present in the computer
	if (!waitReady()) 
		return false;

	// Write the command code to the command register (CR)
	_outp(CR[channel], COMMANDS::IDENTIFY_DEVICE);

	waitBusy();

	// Get the configuration block
	for (int i = 0; i < 256; ++i)
		this->data[i] = _inpw(DR[channel]);

	return true;
}


void ATADevice::waitBusy()
{
	BYTE state;
	const WORD AS[2] = {ATADevice::AS_1, ATADevice::AS_2};
	do {
		state = _inp(AS[this->channel]);
	} while (state & 0x80); // state & 10000000
}


bool ATADevice::waitReady()
{
	const WORD AS[2] = {ATADevice::AS_1, ATADevice::AS_2};
	for (int i = 0; i < 1000; ++i)
		// If the ATA device is ready to exec commands
		if (_inp(AS[this->channel]) & 0x40) // bit DRDY (ready to exec any command) & 01000000
			return true;
	return false;
}


void ATADevice::printProducer()
{
	cout << setw(30) << setfill(' ') << left << "| PRODUCER" << "| ";
	for (int i = 27; i <= 28; ++i)
		cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0xFF); // data[i] & 11111111
	cout << setw(36) << setfill(' ') << "";
}


void ATADevice::printModel() //  and  Producer
{
	cout << "|" << endl << setw(30) << setfill(' ') << left << "| MODEL" << "| ";
	for (int i = 27; i <= 46; ++i)
		cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0xFF); // data[i] & 11111111
}


void ATADevice::printSerialNumber()
{
	cout << "|" << endl << setw(30) << setfill(' ') << left << "| SERIAL NUMBER" << "| ";
	for (int i = 10; i <= 19; ++i)
		cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0xFF);
	cout << setw(20) << setfill(' ') << "";
}


void ATADevice::printFirmwareVersion()
{
	cout << "|" << endl << setw(30) << setfill(' ') << left << "| FIRMWARE VERSION" << "| ";
	for (int i = 23; i <= 26; ++i)
		cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0xFF);
	cout << setw(32) << setfill(' ') << "";
}


void ATADevice::printMemorySize()
{
	cout << "|" << endl << setw(30) << setfill(' ') << left << "| SIZE, GB" << "| ";
	cout << setw(40) << (long long)(((ULONG *)data)[30]) * 512 / 1024 / 1024 / 1024;
}


void ATADevice::printInterfaceType()
{
	cout << "|" << endl << setw(30) << setfill(' ') << left << "| INTERFACE TYPE" << "| "; 
	cout << ((data[15] >> 14) & 1 ? "ATAPI-" : "ATA-") << data[81] << right << setw(35);
}


void ATADevice::printSupportedMultiwordDMA()
{
	for(int i = 0, num = 1; i < 3; ++i, num *= 2)
		cout << "|" << endl << "| Multiword DMA " << i << " SUPPORT" << setw(7) << setfill(' ') << "| " << setw(20) << right << (data[64] & num ? "+" : "-") << setw(21);
}


void ATADevice::printSupportedPIO()
{
	for(int i = 3, num = 1; i < 5; ++i, num *= 2)
		cout << "|" << endl << "| PIO " << i << " SUPPORT" << setw(17) << setfill(' ') << "| " << setw(20) << right << (data[64] & num ? "+" : "-") << setw(21);
}


void ATADevice::printSupportedUltraDMA()
{
	for(int i = 0, num = 1; i < 6; ++i, num *= 2)
		cout << "|" << endl << "| UDMA " << i << " SUPPORT" << setw(16) << setfill(' ') << "| " << setw(20) << right << (data[80] & num ? "+" : "-") << setw(21);
}


void ATADevice::printSupportedATAVersions()
{
	for(int i = 1, num = 2; i < 8; ++i, num *= 2)
		cout << "|" << endl << "| ATA " << i << " SUPPORT" << setw(17) << setfill(' ') << "| " << setw(20) << right << (data[80] & num ? "+" : "-") << setw(21);
}

