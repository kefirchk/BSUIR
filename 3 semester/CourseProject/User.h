#ifndef USER_H
#define USER_H

#pragma once
#include "Money.h"
#include "Human.h"
#include <QList>
#include <QTextStream>

class User : public Human
{
private:
    Money cash[4]; //массив личных счетов пользователя
                   //(максимум 4 счета с различными валютами: бел, рус, доллары, евро).
public:
    User();   //конструктор
    ~User();  //деструктор

    Money* getMoney();                   //получение указателя на массив счетов

    User(const User& user);              //конструктор копирования
    User& operator=(const User& user);   //оператор присваивания
    bool operator==(User& other);        //оператор равно
    friend QTextStream& operator<<(QTextStream& out, User& object); //запись в файл
    friend QTextStream& operator>>(QTextStream& in, User& object);  //чтение из файла

};

#endif // USER_H
