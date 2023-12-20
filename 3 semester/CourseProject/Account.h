#ifndef ACCOUNT_H
#define ACCOUNT_H

#pragma once
#include <QString>

class Account                 //класс "Аккаунт"
{
protected:
    int _id;                  //идентификационный номер пользователя
    QString _login;           //логин аккаунта
    QString _password;        //пароль от аккаунта
    QString _blocking_status; //статус блокировки
public:
    Account(int = -1, QString = "", QString = "", QString = "active");  //конструктор с параметрами
    ~Account();                     //деструктор

    Account(const Account&);        //конструктор копирования
    Account& operator=(const Account&); //оператор присваивания

    void setLogin(QString);         //метод задания логина
    void setId(int);                //метод задания ID пользователя
    void setPassword(QString);      //метод задания пароля
    void setBlockingStatus(QString);//метод задания статуса блокировки
    QString getLogin();             //метод получения логина
    int getId();                    //метод получения ID пользователя
    QString getPassword();          //метод получения пароля
    QString getBlockingStatus();    //метод получения статуса блокировки
};

#endif // ACCOUNT_H
