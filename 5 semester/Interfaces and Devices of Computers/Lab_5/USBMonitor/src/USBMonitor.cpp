#include "USBMonitor.h"

int usbStatus = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_DEVICECHANGE)
    {
        switch(wParam)
        {
        case DBT_DEVICEARRIVAL:
            usbStatus = DBT_DEVICEARRIVAL;
            qDebug() << "USB device connected";
            break;
        case DBT_DEVICEREMOVECOMPLETE:
            usbStatus = DBT_DEVICEREMOVECOMPLETE;
            qDebug() << "USB device disconnected";
            break;
        case DBT_DEVICEQUERYREMOVE:
            usbStatus = DBT_DEVICEQUERYREMOVE;
            qDebug() << "Tring to disconnect device safely";
            break;
        case DBT_DEVICEQUERYREMOVEFAILED:
            usbStatus = DBT_DEVICEQUERYREMOVEFAILED;
            qDebug() << "Failed to disconnect device safely";
            break;
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

USBMonitor::USBMonitor(QObject *parent) : QThread(parent)
{
    updateDeviceInfoSet();
    updateDeviceInfoSetSize();
    isRunning = false;

    // Создание невидимого окна для обработки сообщений Windows
    WNDCLASSEX wc = {sizeof(WNDCLASSEX)};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = L"USBMonitorWindow";
    RegisterClassEx(&wc);

    HWND hwnd = CreateWindowEx(0, L"USBMonitorWindow", L"", 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, nullptr, nullptr);

    // Регистрация окна для мониторинга USB-устройств
    DEV_BROADCAST_DEVICEINTERFACE NotificationFilter = {};
    NotificationFilter.dbcc_size = sizeof(NotificationFilter);
    NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    NotificationFilter.dbcc_classguid = GUID_DEVINTERFACE_USB_DEVICE;
    hDevNotify = RegisterDeviceNotification(hwnd, &NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE);
}

USBMonitor::~USBMonitor()
{
    SetupDiDestroyDeviceInfoList(deviceInfoSet);

    // Отмена регистрации окна мониторинга USB-устройств
    UnregisterDeviceNotification(hDevNotify);
}

void USBMonitor::run()
{
    isRunning = true;
    while(isRunning)
    {
        if(usbStatus != 0)
        {
            emit this->usbConnectionSignal(usbStatus);
            usbStatus = 0;
        }
        Sleep(100);
    }
}

bool USBMonitor::updateDeviceInfoSet()
{
    SetupDiDestroyDeviceInfoList(deviceInfoSet);
    deviceInfoSet = SetupDiGetClassDevsA(&GUID_DEVINTERFACE_USB_DEVICE, nullptr, nullptr, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    return deviceInfoSet == INVALID_HANDLE_VALUE ? false : true;
}

bool USBMonitor::updateDeviceInfoSetSize()
{
    size_t count = 0;
    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    while(SetupDiEnumDeviceInfo(deviceInfoSet, count, &deviceInfoData) == TRUE)
        ++count;
    deviceInfoSetSize = count;
    return true;
}


HDEVINFO USBMonitor::getDeviceInfoSet()
{
    updateDeviceInfoSet();
    return this->deviceInfoSet;
}

size_t USBMonitor::getDeviceInfoSetSize()
{
    updateDeviceInfoSetSize();
    return this->deviceInfoSetSize;
}

QString USBMonitor::getData(size_t index, DWORD property)
{
    char data[256] = "";
    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    if(SetupDiEnumDeviceInfo(deviceInfoSet, index, &deviceInfoData) == TRUE)
        SetupDiGetDeviceRegistryPropertyA(deviceInfoSet, &deviceInfoData, property, NULL, (PBYTE)data, sizeof(data), 0);
    return QString::fromLocal8Bit(data);
}

DWORD USBMonitor::ejectDevice(size_t index)
{
    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    if(SetupDiEnumDeviceInfo(deviceInfoSet, index, &deviceInfoData) == TRUE)
        return CM_Request_Device_EjectA(deviceInfoData.DevInst, NULL, NULL, 0, 0);        // осуществляем безопасное извлечение устройства
    return CR_FAILURE;
}

void USBMonitor::setIsRunning(bool newIsRunning)
{
    isRunning = newIsRunning;
}
