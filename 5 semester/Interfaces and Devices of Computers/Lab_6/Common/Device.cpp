#include "Device.h"

Device::Device()
{}

Device::Device(PBLUETOOTH_DEVICE_INFO deviceInfo)
{
    this->info = deviceInfo;
}

//void Device::printInfo()
//{
//    cout << "Device #" << id << endl;
//    wprintf(L"  \tClass: 0x%08x\r\n", info->ulClassofDevice);
//    wprintf(L"  \tInstance Name: %s\r\n", info->szName);
//    wprintf(L"  \tConnected: %s\r\n", info->fConnected ? L"true" : L"false");
//    wprintf(L"  \tAuthenticated: %s\r\n", info->fAuthenticated ? L"true" : L"false");
//    wprintf(L"  \tRemembered: %s\r\n", info->fRemembered ? L"true" : L"false");
//    wprintf(L"  \tAddress: %02X:%02X:%02X:%02X:%02X:%02X\r\n",
//            info->Address.rgBytes[5],
//            info->Address.rgBytes[4],
//            info->Address.rgBytes[3],
//            info->Address.rgBytes[2],
//            info->Address.rgBytes[1],
//            info->Address.rgBytes[0]
//            );
//}

void Device::setId(int newId)
{
    id = newId;
}


int Device::getId()
{
    return this->id;
}

QString Device::getClass()
{
    return QString::number(this->info->ulClassofDevice, 16);
}

QString Device::getInstanceName()
{
    int devNameSize = wcslen(info->szName);
    return QString::fromWCharArray(info->szName, devNameSize);
}

QString Device::getAddress()
{
    return QString::number(this->info->Address.ullLong, 16);
}

bool Device::isConnected()
{
    return info->fConnected;
}

bool Device::isAuthenticated()
{
    return info->fAuthenticated;
}

bool Device::isRemembered()
{
    return info->fRemembered;
}
