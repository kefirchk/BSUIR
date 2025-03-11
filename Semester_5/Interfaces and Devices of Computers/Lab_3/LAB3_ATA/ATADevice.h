#pragma once
#include "Libs.h"
#include "Functions.h"

class ATADevice
{
private:
	WORD data[256];       // data received from the data register
	int channel;
	int device;
public:
	bool initialize();

	void waitBusy();
	bool waitReady();
	
	void setChannel(int);
	void setDevice(int);

	void printProducer();
	void printModel();
	void printSerialNumber();
	void printFirmwareVersion();
	void printMemorySize();
	void printInterfaceType();
	void printSupportedMultiwordDMA();
	void printSupportedPIO();
	void printSupportedUltraDMA();
	void printSupportedATAVersions();

	enum REGISTERS {
		// CHANNEL 1
		AS_1 = 0x3F6,   // alternative register of status (SR), but don't change state if we read information
		DC_1 = 0x3F6,   // device control
		DA_1 = 0x3F7,   // device address
		DR_1 = 0x1F0,   // data register
		ER_1 = 0x1F1,   // error register
		FR_1 = 0x1F1,   // register of properties
		SC_1 = 0x1F2,   // sector counter
		SN_1 = 0x1F3,   // sector number (LBA[7:0]) 
		CL_1 = 0x1F4,   // low byte of cylinder number (LBA[15:8])
		CH_1 = 0x1F5,   // high byte of cylinder number (LBA[23:16])
		DH_1 = 0x1F6,   // number of device and cylinder head (LBA[27:24])
		SR_1 = 0x1F7,   // state register
		CR_1 = 0x1F7,   // command register

		// CHANNEL 2
		AS_2 = 0x376,
		DC_2 = 0x376,
		DA_2 = 0x377,
		DR_2 = 0x170,
		ER_2 = 0x171,
		FR_2 = 0x171,
		SC_2 = 0x172,
		SN_2 = 0x173,
		CL_2 = 0x174,
		CH_2 = 0x175,
		DH_2 = 0x176,
		SR_2 = 0x177,
		CR_2 = 0x177
	};

	enum COMMANDS {
		IDENTIFY_PACKET_DEVICE = 0xA1,  // add information about CDROM
		IDENTIFY_DEVICE        = 0xEC   // add information about all disks
	};
};