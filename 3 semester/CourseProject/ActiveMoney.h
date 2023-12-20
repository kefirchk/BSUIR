#ifndef ACTIVEMONEY_H
#define ACTIVEMONEY_H

#pragma once
#include "Service.h"
#include "Money.h"
#include <QString>

class ActiveMoney : public Service, public Money //кредиты, депозиты
{
    float _percent;               //процент
    int _term;                    //период действия
    QString _application;         //описание услуги
public:
    ActiveMoney(float = 0, float = 0, QString = 0);
    ~ActiveMoney();

    void setPercent(float);       //метод задания процентов/год
    void setTerm(int);            //метод установки периода
    void setApplication(QString); //метод установки описания услуги

    float getPercent();           //метод получения процента
    int getTerm();                //метод получения периода действия
    QString getApplication();     //метод получения описания услуги
    bool operator==(ActiveMoney& other);               //оператор равно для сравнения элементов
    friend QTextStream& operator>>(QTextStream& in, ActiveMoney& credit);    //оператор для чтения из файла
    friend QTextStream& operator<<(QTextStream& out, ActiveMoney& actMoney); //оператор для записи в файл
};

#endif // ACTIVEMONEY_H
