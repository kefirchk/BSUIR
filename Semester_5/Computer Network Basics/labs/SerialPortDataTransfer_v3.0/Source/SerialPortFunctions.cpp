#include "SerialPortFunctions.h"

// Инициализация порта
void initPort(QSerialPort& port, const QSerialPortInfo& portInfo)
{
    port.setPort(portInfo);
    port.setPortName(portInfo.portName());

    // Настройка параметров передачи данных
    port.setBaudRate(QSerialPort::Baud9600);
    port.setDataBits(QSerialPort::Data5);
    port.setParity(QSerialPort::NoParity);
    port.setStopBits(QSerialPort::OneStop);
    port.setFlowControl(QSerialPort::NoFlowControl);
}

// Проверка на возможность изменения порта
bool canChangePort(const QList<QSerialPortInfo>& portList, const QString& newPortName)
{
    for(auto portInfo : portList)
    {
        QSerialPort port;
        initPort(port, portInfo);
        if(portInfo.portName() == newPortName && port.open(QIODevice::ReadWrite))
        {
            port.close();
            qDebug() << "Port" << port.portName() << "is choosen for work";
            return true;
        }
    }
    return false;
}

// Перевод десятичного числа в строковой форме в двоичное число в строковой форме с фикс. числом разрядов
QString toBinary(QString decimalNumber, unsigned long size)
{
    QString binaryNumber = QString::number(decimalNumber.toInt(), 2);
    binaryNumber = binaryNumber.rightJustified(size, '0');
    return binaryNumber;
}

