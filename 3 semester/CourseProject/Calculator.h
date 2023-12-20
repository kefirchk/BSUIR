#ifndef CALCULATOR_H
#define CALCULATOR_H

#pragma once
#include <QDialog>

namespace Ui {
class Calculator;
}

class Calculator : public QDialog
{
    Q_OBJECT

public:
    explicit Calculator(int num_window = 0, QWidget *parent = nullptr); //конструктор
    ~Calculator();                             //деструктор

private slots:
    void on_convert_pushButton_clicked();      //конвертировать валюты
    void on_calc_credit_Button_clicked();      //рассчитать кредит
    void on_calc_deposit_Button_clicked();     //рассчитать депозит
    void close_calculator();                   //закрыть калькулятор(конвертер)

private:
    Ui::Calculator *ui;
    int _num_window = 0;  //номер активного окна
};

#endif // CALCULATOR_H
