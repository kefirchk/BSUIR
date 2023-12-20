#include "BluetoothMonitor.h"

BluetoothMonitor::~BluetoothMonitor()
{
    // Радиостанции больше нет, закрываем все хендлы
    if (BluetoothFindRadioClose(radio.hRadioFind) == TRUE)
        qDebug() << "BluetoothFindRadioClose() is OK!";
    else
        qDebug() << "BluetoothFindRadioClose() failed with error code: " << GetLastError();
}

RadioStruct BluetoothMonitor::findRadio()
{
    RadioStruct radioDev;

    radio.hRadioFind = BluetoothFindFirstRadio(&radio.findRadioParams, &radio.hRadio);
    if (radio.hRadioFind != NULL)
        qDebug() << "Radio is founded!";
    else
    {
        qDebug() << "Error: cannot find radio, error code: " << GetLastError();
        exit(EXIT_FAILURE);
    }

    DWORD radioInfoStatus = BluetoothGetRadioInfo(radio.hRadio, &radio.info);
    if (radioInfoStatus != ERROR_SUCCESS)
    {
        qDebug() << "Error: cannot get radio info, error code: " << radioInfoStatus;
        exit(EXIT_FAILURE);
    }
    radioDev.address = radio.getAddress();
    radioDev.deviceClass = radio.getClass();
    radioDev.instanceName = radio.getInstanceName();
    radioDev.manufacturer = radio.getManufacturer();

    return radioDev;
}

QList<DeviceStruct> BluetoothMonitor::findDevices()
{
    deviceSearchParams.hRadio = radio.hRadio;
    ZeroMemory(&deviceInfo, sizeof(BLUETOOTH_DEVICE_INFO));
    deviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
    hDeviceFind = BluetoothFindFirstDevice(&deviceSearchParams, &deviceInfo);

    if (hDeviceFind == NULL)
    {
        qDebug() << "Error: cannot find any Bluetooth devices, error code: " << GetLastError();
        exit(EXIT_FAILURE);
    }

    int device_id = 0;
    QList<DeviceStruct> devices;

    // Получение информации о других устройствах Bluetooth
    do {
        Device dev(&deviceInfo);
        dev.setId(++device_id);

        DeviceStruct devStruct;
        devStruct.address = dev.getAddress();
        devStruct.deviceClass = dev.getClass();
        devStruct.instanceName = dev.getInstanceName();
        devStruct.isConnected = dev.isConnected();
        devStruct.isAuthenticated = dev.isAuthenticated();
        devStruct.isRemembered = dev.isRemembered();

        devices.append(devStruct);

    } while (BluetoothFindNextDevice(hDeviceFind, &deviceInfo));

    // NO more device, close the device handle
    if (BluetoothFindDeviceClose(hDeviceFind) == TRUE)
        qDebug() << "BluetoothFindDeviceClose() is OK!";
    else
        qDebug() << "BluetoothFindDeviceClose() failed with error code: " << GetLastError();

    return devices;
}
