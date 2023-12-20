#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include "User.h"
#include "BinaryTree.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    friend class SignIn;
    friend class ChangeMenu;
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, short newStatus = 0); //конструктор
    ~MainWindow();                        //деструктор

private slots:
    void on_signIn_pushButton_clicked();  //вход в аккаунт
    void on_signUp_pushButton_clicked();  //регистрация

    void on_currency_converter_pushButton_clicked(); //конвертер валют
    void on_deposit_calculator_pushButton_clicked(); //депозитный калькулятор
    void on_credit_calculator_pushButton_clicked();  //кредитный калькулятор
    void on_options_pushButton_clicked();            //настройки

    void on_openNewAcc_pushButton_clicked();         //открыть новый счет
    void on_closeAcc_pushButton_clicked();           //закрыть счет
    void on_addMoney_pushButton_clicked();           //положить деньги на счет
    void on_takeMoneyFrom_pushButton_clicked();      //снять деньги со счета
    void on_updateAccountInfo_pushButton_clicked();  //обновить информацию об открытых счетах
    void on_transferTo_pushButton_clicked();         //перевести деньги

    void on_changeCurrRate_pushButton_clicked();     //изменить курс валют

    void on_backForAdmin_pushButton_clicked();       //кнопка "Назад" для админа
    void on_backFromUserOptions_pushButton_clicked();//кнопака "Назад" для пользователя
    void exits();                                    //выходы из приложения

    void on_given_credits_triggered();               //открыть таблицу возможных кредитов
    void on_given_deposits_triggered();              //открыть таблицу возможных депозитов

    void on_cleanHistory_pushButton_clicked();       //очистить историю переводов
    void on_takeNewCredit_pushButton_clicked();      //взять новый кредит
    void on_takeNewDeposit_pushButton_clicked();     //взять новый депозит

    void on_updateMyDeposits_pushButton_clicked();   //обновить таблицу взятых депозитов
    void on_updateMyCredits_pushButton_clicked();    //обновить таблицу взятых кредитов
    void on_payForCredit_pushButton_clicked();       //оплатить кредит
    void on_takeFromDeposit_pushButton_clicked();    //снять деньги с депозитного счета

    void on_deleteUser_pushButton_clicked();         //удалить пользователя
    void on_showAllUsers_pushButton_clicked();       //показать всех зарегистрированных пользователей
    void on_search_pushButton_clicked();             //поиск ифнормации в таблице пользователей
    void on_changeParametres_pushButton_clicked();   //изменение полей пользователя через настройки пользователя

    void on_editUser_pushButton_clicked();           //изменение полей пользователя админом

    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    BinaryTree<User> tree;  //контейнер "Бинарное дерево", хранящий пользователей
    short status = 0;       //признак активного окна
    User _current_user;     //текущий пользователь
};
#endif // MAINWINDOW_H
