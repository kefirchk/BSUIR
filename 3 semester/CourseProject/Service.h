#ifndef SERVICE_H
#define SERVICE_H

#pragma once
#include <QTextStream>

class Service
{
protected:
    int _idNumber;         //номер услуги
public:
    Service(int = -1);      //конструктор
    ~Service();             //деструктор

    void setNumber(int);    //метод установки номера услуги
    int getNumber();        //метод получения номера услуги
    friend QTextStream& operator>>(QTextStream&, Service&);  //оператор для чтения из файла
    friend QTextStream& operator<<(QTextStream&, Service&);  //оператор для записи в файл
};

#endif // SERVICE_H
