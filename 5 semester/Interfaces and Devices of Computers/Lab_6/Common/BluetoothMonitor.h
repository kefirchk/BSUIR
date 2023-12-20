#pragma once

#include "SystemLibs.h"
#include "Config.h"
#include "Radio.h"
#include "Device.h"


struct RadioStruct
{
    QString address;
    QString deviceClass;
    QString instanceName;
    QString manufacturer;
};

struct DeviceStruct
{
    QString address;
    QString deviceClass;
    QString instanceName;
    bool isConnected;
    bool isAuthenticated;
    bool isRemembered;
};

class BluetoothMonitor
{
private:
    BLUETOOTH_DEVICE_SEARCH_PARAMS deviceSearchParams = {
        sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS),
        1,    // fReturnAuthenticated
        0,    // fReturnRemembered
        1,    // fReturnUnknown
        1,    // fReturnConnected
        1,    // fIssueInquiry
        8,    // cTimeoutMultiplier
        NULL  // hRadio
    };
    Radio radio;

    BLUETOOTH_DEVICE_INFO deviceInfo = {
        sizeof(BLUETOOTH_DEVICE_INFO),
        0,
    };
    HBLUETOOTH_DEVICE_FIND hDeviceFind = NULL;

public:
    ~BluetoothMonitor();

    RadioStruct findRadio();
    QList<DeviceStruct> findDevices();


};
