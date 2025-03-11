//#ifndef SERIALPORTFUNCTIONS_H
//#define SERIALPORTFUNCTIONS_H
#pragma once

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

void initPort(QSerialPort& port, const QSerialPortInfo& portInfo);
bool canChangePort(const QList<QSerialPortInfo> &portList, const QString& newPortName);
QString toBinary(QString decimalNumber, unsigned long size);

//#endif // SERIALPORTFUNCTIONS_H
