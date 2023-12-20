#pragma once

#include "SystemLibs.h"
#include "Config.h"

class Device
{
private:
    int id;

    PBLUETOOTH_DEVICE_INFO info;

public:
    Device();
    Device(PBLUETOOTH_DEVICE_INFO deviceInfo);
    //void printInfo();

    int getId();
    QString getClass();
    QString getInstanceName();
    QString getAddress();
    bool isConnected();
    bool isAuthenticated();
    bool isRemembered();
    void setId(int newId);
};

