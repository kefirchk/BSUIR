#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>
#include "BinaryTree.cpp"
#include "User.h"

int generate_id(BinaryTree<User> &tree);       //функция генерирования ID для пользователя
float choosing_currency(QString option);       //функция получения значения валюты по ее названию
int matchCurrAndNum(QString ch_curr);          //функция соответствия строки названия валюты ее индексу
void get_float(float*& _sum, QString sum_str); //функция проверки ввода вещественного числа

#endif // FUNCTIONS_H
