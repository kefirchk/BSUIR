#ifndef TXTFILE_H
#define TXTFILE_H

#pragma once
#include <QMessageBox>
#include <QFile>
#include <QList>
#include "BinaryTree.h"
#include "User.h"

#define PATH "D:/Projects/Qt/CourseProject/Files/"  //путь до рабочих файлов

template <class T>
class TxtFile
{
private:
    QFile _file;            //файл
    QTextStream _stream;    //поток для файла
public:
    TxtFile(QString = "");  //конструктор
    ~TxtFile();             //деструктор

    bool openFile(QFlags<QIODevice::OpenModeFlag> openMode);  //открыть файл
    void readFromFile(QList<T>& list);          //читать из файла
    void writeInFile(QList<T>& list);           //записать в файл

    QFile& getQFile();                          //получить файл
    void readCash(BinaryTree<User> &cashTree);  //читать из файла открытых счетов
    void readUsers(BinaryTree<User> &userTree); //читать из файла пользователей
    void writeCash(User &user, int index);      //записать в файл открытых счетов
    void writeUsers(User &user);                //записать в файл пользователей
};

#endif // TXTFILE_H
