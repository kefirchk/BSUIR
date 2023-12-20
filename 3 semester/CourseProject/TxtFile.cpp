#include "mainwindow.h"
#include "Functions.h"
#include "TxtFile.h"
#include "Exception.h"

template<class T>
TxtFile<T>::TxtFile(QString newFileName) : _stream(&_file) //конструктор
{
    _file.setFileName(newFileName);
}
template<class T>
TxtFile<T>::~TxtFile()  //деструктор
{}

template<class T>
QFile& TxtFile<T>::getQFile() //получить файл
{
    return _file;
}

template<class T>
bool TxtFile<T>::openFile(QFlags<QIODevice::OpenModeFlag> openMode) //открыть файл
{
    MainWindow w;
    try
    {
        //if(!_file.exists() && openMode == (QIODevice::Text | QIODevice::ReadOnly))
          //  throw Exception(&w, "Ошибка открытия файла!", "Проверьте наличие файла");
        //else
        if(!_file.open(openMode))
            throw Exception(&w, "Ошибка открытия файла!", "Проверьте целостность файла");
        return true;
    }
    catch (Exception& file)
    {
        file.what();
        return false;
    }
}

template<class T>
void TxtFile<T>::writeInFile(QList<T>& list) //записать в файл
{
    for (int i = 0; i < list.size(); i++)
        _stream << list[i];
}


template <class T>
void TxtFile<T>::readFromFile(QList<T>& list) //прочитать из файла
{
    T obj;
    while(!_stream.atEnd())
    {
        _stream >> obj;
        list.push_back(obj);
    }
}


template <class T>
void TxtFile<T>::readCash(BinaryTree<User> &cashTree) //прочитать файл личных счетов пользователей
{
    QStringList lst;
    for(int i = 0, ii; !(_stream.atEnd()); i++)
    {
        User user;
        lst = _stream.readLine().split(" ");  //делим прочитанную строку на слова разделенные пробелом
        ii = matchCurrAndNum(lst.at(2));
        user.getAccountData()->setId(lst.at(0).toInt());
        user.getMoney()[ii].setAmount(lst.at(1).toDouble());
        user.getMoney()[ii].setCurrencyName(lst.at(2));
        cashTree.add(cashTree.getRoot(), user);
    }
}

template<class T>
void TxtFile<T>::readUsers(BinaryTree<User> &userTree) //прочитать файл пользователей
{
    while(!_stream.atEnd())
    {
        User temp;
        _stream >> temp;
        userTree.add(userTree.getRoot(), temp);
    }
}

template<class T>
void TxtFile<T>::writeCash(User &user, int i) //записать лицевой счет в соответствующий файл
{
    _stream << user.getAccountData()->getId() << ' ' << user.getMoney()[i].getAmount();
    _stream << ' ' << user.getMoney()[i].getCurrencyName() << ' ' << '\n';
}

template<class T>
void TxtFile<T>::writeUsers(User &user) //записать пользователя в соответствующий файл
{
    _stream << user;
}
