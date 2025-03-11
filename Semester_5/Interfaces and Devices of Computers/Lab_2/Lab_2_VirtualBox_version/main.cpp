
// Делать через порты ввода/вывода!!!
// Сканируем шину PCI (посылаем запрос, получаем ответ через порты), получаем идентификатор устройств
#include "Libs.h"
#include "Functions.h"
#include "PCIDevice.h"
#include "(PCI_DEVS)pci_codes.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    PCIDevice dev;
    print_hat();
    for (int i = 0; dev.bind(i) != false; ++i)
    {
        cout << "|" << setw(5) << left << (i + 1)
             << "|" << setw(85) << left << dev.get_name().c_str()
             << "|" << setw(9) << left << dev.get_deviceID().c_str()
             << "|" << setw(9) << left << dev.get_vendorID() << "|" << endl;
    }
    print_end();
    return 0;
}