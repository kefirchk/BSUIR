#pragma once
#include <iostream>          //подключение библиотеки потока ввода-вывода
#include <iomanip>
using namespace std;         //использование пространства имён std
#include "CountingMachine.h" //подключение библиотеки класса "Вычислительная машина"
#include "StationaryCM.h"    //подключение библиотеки класса "Стационарная ВМ"
#include "PortableCM.h"      //подключение библиотеки класса "Портативная ВМ"
#include "Monoblock.h"       //подключение библиотеки класса "Моноблок"
#include "Notebook.h"        //подключение библиотеки класса "Ноутбук"
#include "Smartphone.h"      //подключение библиотеки класса "Смартфон"

void outputHatCM();
void outputHatSCM();
void outputHatPCM();
void outputHatMonoblock();
void outputHatNotebook();
void outputHatSmartphone();