#include "PowerSupply.h"

void PowerSupply::update()
{
	SYSTEM_POWER_STATUS status;
	GetSystemPowerStatus(&status);
	this->powerSupplyType = getPowerSupplyType(status);
	this->batteryLevel = status.BatteryLifePercent;
	this->batteryType = getBatteryChemistry();
	isSaveMode = status.SystemStatusFlag;
	this->powerSavingMode = getPowerSavingMode();
	this->batteryLifeWithoutCharging = status.BatteryLifeTime;
	this->batteryTimeAfterDisconnectingTheCharger = status.BatteryFullLifeTime / (3600 * 24 * 365) ;
}

string PowerSupply::getPowerSupplyType(SYSTEM_POWER_STATUS status) 
{
	switch (status.ACLineStatus)
	{
	case 0: return "Battery"; // питание от аккумулятора
	case 1: return "Mains";   // питание от сети
	default: return "Unknown"; // неизвестно
	}
}

string PowerSupply::getPowerSavingMode() {
	if(isSaveMode == 1)
		return "On";
	else
		return "Off";
}

string PowerSupply::getBatteryChemistry() 
{	
	string batteryType;

	HDEVINFO DeviceInfoSet = SetupDiGetClassDevs( // получаем дескриптор список интерфейсов всех устройств
		&GUID_DEVCLASS_BATTERY,                   // здесь указываем батарею(ее указатель)
		NULL,                                     // необязательный параметр
		NULL,                                     // дескриптор окна верхнего уровня, который будет использоваться 
												  // для пользовательского интерфейса, связанного с установкой 
												  // экземпляра устройства в наборе информации об устройстве.
												  // Этот дескриптор не является обязательным и может иметь значение NULL.
		DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);	  // только те устройства, которые в данный момент присутствуют в системе и
												  // возврат устройств, поддерживающих интерфейсы устройств для указанных классов интерфейсов устройств

	if (DeviceInfoSet)
	{
		SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
		DeviceInterfaceData.cbSize = sizeof(DeviceInterfaceData); // Для установки в SetupDiGetDeviceInterfaceDatail значений NULL

		// Перечисляем интерфейсы устройства, содержащиеся в наборе информации об устройстве
		SetupDiEnumDeviceInterfaces(DeviceInfoSet, 0, &GUID_DEVCLASS_BATTERY, 0, &DeviceInterfaceData); 

		DWORD cbRequired = 0;
		// Возвращаем сведения об интерфейсе устройства и обновляем cbRequired
		SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, NULL, 0, &cbRequired, 0); 

		// содержит путь к интерфейсу устройства
		PSP_DEVICE_INTERFACE_DETAIL_DATA pdidd = (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, cbRequired); // Выделяет указанное количество байтов из кучи
																												 // где фикс. размер памяти и нициализация нулями
		if (pdidd)
		{
			pdidd->cbSize = sizeof(*pdidd);
			// Возвращаем сведения об интерфейсе устройства
			SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, pdidd, cbRequired, &cbRequired, 0);

			// Создает или открывает файл или устройство ввода-вывода
			HANDLE batteryHandle = CreateFile(pdidd->DevicePath,  // имя файла
				GENERIC_READ | GENERIC_WRITE,					  // запрошенный доступ к файлу
				FILE_SHARE_READ | FILE_SHARE_WRITE,				  // запрошенный режим общего доступа к файлу или устройству
				NULL,											  // флаги безопасности
				OPEN_EXISTING,								      // действия, которые нужно выполнить
				FILE_ATTRIBUTE_NORMAL,							  // флаги и атрибуты устройства (указано по умолчанию)
				NULL);											  // для дополнительных флагов и атрибутов
 
			BATTERY_QUERY_INFORMATION bqi = { 0 };  // Содержит информацию о запросе батареи
			
			// Отправляет управляющий код непосредственно указанному драйверу устройства, заставляя соответствующее устройство выполнить соответствующую операцию.
			DeviceIoControl(batteryHandle,           
				IOCTL_BATTERY_QUERY_TAG,            // Получаем тэг батареи
				NULL, NULL, &bqi.BatteryTag, sizeof(bqi.BatteryTag), NULL, NULL);

			BATTERY_INFORMATION bi;                 // здесь получаем информацию о батареи
			DeviceIoControl(batteryHandle, IOCTL_BATTERY_QUERY_INFORMATION, &bqi, sizeof(bqi), &bi, sizeof(bi), NULL, NULL);

			batteryType = reinterpret_cast<char*>(bi.Chemistry);

			CloseHandle(batteryHandle);             // закрываем дескриптор
			LocalFree(pdidd);                       // освобождаем память
		}
		SetupDiDestroyDeviceInfoList(DeviceInfoSet);
	}

	return batteryType.substr(0, 4);
	
}

ostream& operator<<(ostream& out, PowerSupply powerSupply)
{
	unsigned long hours = powerSupply.batteryLifeWithoutCharging / 3600;
	unsigned long minutes = (powerSupply.batteryLifeWithoutCharging % 3600) / 60;
	unsigned long seconds = powerSupply.batteryLifeWithoutCharging % 60;
	string time = "" + to_string(hours) + "h:" + to_string(minutes) + "m:" + to_string(seconds) + "s";
	if (powerSupply.batteryLifeWithoutCharging == ULONG_MAX)
		time = "infitiny";
	
	out << setw(10) << "|Type of power supply             |" << setw(12) << left << powerSupply.powerSupplyType << "|" << endl
		<< setw(10) << "|Type of battery                  |" << setw(12) << left << powerSupply.batteryType << "|" << endl
		<< setw(10) << "|Battery level, %                 |" << setw(12) << left << powerSupply.batteryLevel << "|" << endl
		<< setw(10) << "|Current power saving mode        |" << setw(12) << left << powerSupply.powerSavingMode << "|" << endl
		<< setw(10) << "|Battery life without charging    |" << setw(12) << left << time << "|" << endl;
		//<< setw(10) << "|Remaining battery time after     |" << setw(12) << left << powerSupply.batteryTimeAfterDisconnectingTheCharger << "|" << endl
		//<< setw(10) << "|disconnecting the charger, years |" << setw(13) << right << "|" << endl;
	return out;
}