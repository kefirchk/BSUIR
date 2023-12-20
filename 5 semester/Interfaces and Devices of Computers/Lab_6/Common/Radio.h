#pragma once

#include "Config.h"
#include "SystemLibs.h"

struct Radio
{
    HANDLE hRadio = NULL;
    HBLUETOOTH_RADIO_FIND hRadioFind = NULL;
    BLUETOOTH_RADIO_INFO info = {
        sizeof(BLUETOOTH_RADIO_INFO),
        0,
    };
    BLUETOOTH_FIND_RADIO_PARAMS findRadioParams = {
        sizeof(BLUETOOTH_FIND_RADIO_PARAMS)
    };

    int id;


public:
    //void printInfo();

    int getId();
    QString getClass();
    QString getInstanceName();
    QString getManufacturer();
    QString getAddress();
};
