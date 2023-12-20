#ifndef SIGN_H
#define SIGN_H

#pragma once
#include <QDialog>
#include "User.h"

namespace Ui {
class Sign;
}

class Sign : public QDialog
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit Sign(short* = 0, User* = 0, short = 0, QWidget *parent = nullptr); //конструктор
    ~Sign();                 //деструктор
    User* getUserData();     //метод получения информации о пользователе

private slots:
    void on_signIn_buttonBox_accepted();  //нажать на кнопку "Ok" для входа в аккаунт
    void on_signUp_buttonBox_accepted();  //нажать на кнопку "Ok" для регистрации
    void on_signIn_buttonBox_rejected();  //нажать на кнопку "Cancel" для входа в аккаунт
    void on_signUp_buttonBox_rejected();  //нажать на кнопку "Cancel" для регистрации
    void on_agree_checkBox_stateChanged(int); //подтвердить, что прочитал(-а) условия пользования приложением

private:
    Ui::Sign *ui;
    short* _st;     //номер текущего главного окна
    short _win_num; //номер текущего окна для подменю входа/регистрации
    User* _user;    //пользователь
};

#endif // SIGN_H
