#include "Money.h"

Money::Money(QString newCurrencyName, double newAmount) //конструктор
    : _currencyName(newCurrencyName), _amount(newAmount)
{}

Money::Money(const Money& m)      //конструктор копирования
{
    _currencyName = m._currencyName;
    _amount  = m._amount;
}

Money::~Money() //деструктор
{}

void Money::setCurrencyName(QString newCurrencyName) //установка названия валюты
{
    _currencyName = newCurrencyName;
}

void Money::setAmount(double newAmount) //установка количества валюты
{
    _amount = newAmount;
}

QString Money::getCurrencyName()        //получить название валюты
{
    return _currencyName;
}

double Money::getAmount()               //получить количество валюты
{
    return _amount;
}
