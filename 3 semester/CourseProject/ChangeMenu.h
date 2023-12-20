#ifndef CHANGEMENU_H
#define CHANGEMENU_H

#pragma once
#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class ChangeMenu;
}

class ChangeMenu : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeMenu(int = 0, float* = 0, User* user = nullptr, QWidget *parent = nullptr);
    ~ChangeMenu();

private slots:
    void on_ExchCurrRate_buttonBox_accepted();  //изменение курса валют
    void on_addToAccSum_Button_clicked();       //подменю для добавления денег на счете
    void on_takeFromAccSum_Button_clicked();    //подменю для снятия денег со счета
    void on_showPossibleCredits_pushButton_clicked();  //показать возможные кредиты
    void on_showPossibleDeposits_pushButton_clicked(); //показать возможные депозиты
    void on_closeGivenCredits_pushButton_clicked();    //закрыть окно с возможными кредитами
    void on_closeGivenDeposits_pushButton_clicked();   //закрыть окно с возможными депозитами
    void on_payForCreditSum_Button_clicked();   //оплатить кредит
    void on_saveChanges_pushButton_clicked();   //сохранить изменения полей пользователя
private:
    Ui::ChangeMenu *ui;
    int _status;   //номер текущего окна
    float *_sum;   //сумма для пополнения баланса/снятия суммы с баланса
    User* _curr_user; //текущий пользователь
};

#endif // CHANGEMENU_H
