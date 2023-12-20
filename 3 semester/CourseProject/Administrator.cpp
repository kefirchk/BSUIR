#include "Administrator.h"

Administrator::Administrator()    //конструктор
{}
Administrator::~Administrator()   //деструктор
{}

void Administrator::setRateRUB(float RUB)   //метод уставноки курса российского рубля
{
    _currExchRate[0].setAmount(RUB);
}

void Administrator::setRateDOL(float DOL)   //метод установки курса доллара
{
    _currExchRate[1].setAmount(DOL);
}

void Administrator::setRateEUR(float EUR)   //метод установки курса евро
{
    _currExchRate[2].setAmount(EUR);
}

float Administrator::getRateRUB()           //метод получения курса рос. рубля
{
    return _currExchRate[0].getAmount();
}

float Administrator::getRateDOL()           //метод получения курса доллара
{
    return _currExchRate[1].getAmount();
}

float Administrator::getRateEUR()           //метод получения курса евро
{
    return _currExchRate[2].getAmount();
}
