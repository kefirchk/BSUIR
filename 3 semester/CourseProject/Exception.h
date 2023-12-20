#ifndef EXCEPTION_H
#define EXCEPTION_H

#pragma once
#include <QMessageBox>

class Exception
{
protected:
    QWidget* _window;     //использумое окно
    QString _error_msg;   //сообщение об ошибке
    QString _error_description;  //описание ошибки
public:
    Exception(QWidget* = nullptr, QString = "", QString = "");   //конструктор
    ~Exception();  //деструктор
    void what();   //метод вывода ошибки
};

#endif // EXCEPTION_H
