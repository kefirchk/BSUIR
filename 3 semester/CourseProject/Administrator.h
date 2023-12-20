#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#pragma once
#include "Human.h"
#include "Money.h"

class Administrator : public Human
{
private:
    Money _currExchRate[3];      //курсы валют (0 - российские рубли, 1 - доллары США, 2 - евро)
public:
    Administrator();
    ~Administrator();

    void setRateRUB(float RUB);  //метод установки курса рос. рубля
    void setRateDOL(float DOL);  //метод установки курса доллара
    void setRateEUR(float EUR);  //метод установки курса евро
    float getRateRUB();  //метод получения курса рос. рубля
    float getRateDOL();  //метод получения курса доллара
    float getRateEUR();  //метод получения курса евро
};

#endif // ADMINISTRATOR_H
