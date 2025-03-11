#pragma once
#include "targetver.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
#include "hexioctrl.h"
#include "(PCI_DEVS)pci_codes.h"

#define PCI_MAX_BUS 255
#define PCI_MAX_DEV 31
#define PCI_MAX_FUN 7

#define CONFIG_ADDR  0xCF8  // CONFIG_ADDR specifies the configuration address that is required to be accesses
#define CONFIG_DATA 0xCFC  // CONFIG_DATA grants access to generate the configuration access

#define TABLE_WIDTH 135

void printHat();
void printEnd();
char* getDeviceChip(unsigned long deviceId, unsigned long vendorId);
char* getDeviceChipDesc(unsigned long deviceId, unsigned long vendorId);
char* getDeviceProducerName(unsigned long deviceId, unsigned long vendorId);
unsigned long calculateAddress(int, int, int, int);
unsigned long getRegisterData(unsigned long);

