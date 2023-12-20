#include "Radio.h"

//void Radio::printInfo()
//{
//    cout << "Device #" << id << endl;
//    wprintf(L"  \tClass: 0x%08x\r\n", info.ulClassofDevice);
//    wprintf(L"  \tInstance Name: %s\r\n", info.szName);
//    wprintf(L"  \tManufacturer: 0x%08x\r\n", info.manufacturer);
//    wprintf(L"  \tAddress: %02X:%02X:%02X:%02X:%02X:%02X\r\n",
//            info.address.rgBytes[5],
//            info.address.rgBytes[4],
//            info.address.rgBytes[3],
//            info.address.rgBytes[2],
//            info.address.rgBytes[1],
//            info.address.rgBytes[0]
//            );
//}

int Radio::getId()
{
    return this->id;
}

QString Radio::getClass()
{
    return QString::number(this->info.ulClassofDevice, 16);
}

QString Radio::getInstanceName()
{
    int devNameSize = wcslen(info.szName);
    return QString::fromWCharArray(info.szName, devNameSize);
}

QString Radio::getManufacturer()
{
    return QString::number(this->info.manufacturer, 16);
}

QString Radio::getAddress()
{
    //WCHAR addr[10] = L"";
    //for(size_t i = 5; i >= 0; --i)
    //{
        //QString::number(this->info.address.rgBytes[], 16);
        return QString::number(this->info.address.ullLong, 16);
    //}
}
