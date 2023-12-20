#ifndef HUMAN_H
#define HUMAN_H

#pragma once
#include "Account.h"      //подключение класса "Аккаунт"

class Human               //класс "Человек"
{
protected:
    QString _name;        //имя пользователя
    QString _surname;     //фамилия пользователя
    Account accountData;  //данные об аккаунте
public:
    Human(QString = "", QString = "");  //конструктор с параметрами
    Human(const Human& m);//конструктор копирования
    ~Human();             //деструктор

    Account* getAccountData(); //метод получения данных об аккаунте
    QString getName();         //метод получения имени
    QString getSurname();      //метод получения фамилии
    void setName(QString);     //метод задания имени
    void setSurname(QString);  //метод задания фамилии
};

#endif // HUMAN_H
