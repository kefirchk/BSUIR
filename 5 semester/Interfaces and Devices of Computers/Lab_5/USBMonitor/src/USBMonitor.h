#ifndef USBMONITOR_H
#define USBMONITOR_H

#pragma once

#include <QList>
#include <QDebug>
#include <QObject>
#include <QApplication>
#include <QThread>

#include <iostream>
#include <windows.h>
#include <setupapi.h>
#include <initguid.h>
#include <ntddstor.h>
#include <usbiodef.h>
#include <devguid.h>

#include <string>
#include <stdio.h>
#include <conio.h>
#include <cfgmgr32.h>
#include <dbt.h>

using namespace  std;

#define AMOUNT_OF_PROPERTIES 10

class USBMonitor : public QThread
{
    Q_OBJECT

signals:
    void usbConnectionSignal(int status);

public:
    explicit USBMonitor(QObject* parent = nullptr);
    ~USBMonitor();
    void run() override;

    HDEVINFO getDeviceInfoSet();
    size_t getDeviceInfoSetSize();
    QString getData(size_t index, DWORD property);
    DWORD ejectDevice(size_t index);

    DWORD property[AMOUNT_OF_PROPERTIES] = {
        SPDRP_DEVICEDESC,
        SPDRP_MFG,
        SPDRP_CLASS,
        SPDRP_CLASSGUID,
        SPDRP_ENUMERATOR_NAME,
        SPDRP_HARDWAREID,
        SPDRP_LOCATION_INFORMATION,
        SPDRP_LOCATION_PATHS,
        SPDRP_PHYSICAL_DEVICE_OBJECT_NAME,
        SPDRP_SERVICE
    };

    QString property_names[AMOUNT_OF_PROPERTIES] = {
        "DEVICEDESC",
        "MFG",
        "CLASS",
        "CLASSGUID",
        "ENUMERATOR_NAME",
        "HARDWAREID",
        "LOCATION_INFORMATION",
        "LOCATION_PATHS",
        "PHYSICAL_DEVICE_OBJECT_NAME",
        "SERVICE"
    };

    void setIsRunning(bool newIsRunning);

private slots:
    bool updateDeviceInfoSet();
    bool updateDeviceInfoSetSize();

private:
    HDEVINFO deviceInfoSet;
    size_t deviceInfoSetSize;

    bool isRunning;

    HDEVNOTIFY hDevNotify;
};

#endif // USBMONITOR_H
