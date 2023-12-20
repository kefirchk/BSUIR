#ifndef TRANSFERMONEY_H
#define TRANSFERMONEY_H

#pragma once
#include <QTextStream>
#include "Money.h"

class TransferMoney : public Money
{
private:
    int _idOfReceiver;         //ID получателя
    int _idOfSender;           //ID отправителя
    QString _dateTime;         //дата и время перевода
public:
    TransferMoney(int senderId = -1, int receiverId = -1, QString dt = 0, double sum = -1); //конструктор
     ~TransferMoney();         //деструктор

    int getIdOfReceiver();     //получение ID получателя
    int getIdOfSender();       //получение ID отправителя
    QString getDateTime();     //получения даты и времени перевода
    void setIdOfReceiver(int); //установка ID получателя
    void setIdOfSender(int);   //установка ID отправителя
    void setDateTime(QString); //установка даты и времени перевода

    friend QTextStream& operator<<(QTextStream& out, TransferMoney& trMoney);  //оператор для записи в файл
    friend QTextStream& operator>>(QTextStream& in, TransferMoney& trMoney);   //оператор для чтения из файла
};

#endif // TRANSFERMONEY_H
