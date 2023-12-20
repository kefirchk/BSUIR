#ifndef MONEY_H
#define MONEY_H

#pragma once
#include <QString>
#include <QTextStream>

class Money
{
protected:
    QString _currencyName;   //название валюты
    double _amount;          //количество денег
public:
    Money(QString = "", double = -1); //конструктор
    ~Money();                         //деструктор
    Money(const Money& m);            //конструктор копирования

    void setCurrencyName(QString);    //установка названия валюты
    void setAmount(double);           //установка значения валюты
    QString getCurrencyName();        //получение названия валюты
    double getAmount();               //получения значения валюты
};

#endif // MONEY_H
