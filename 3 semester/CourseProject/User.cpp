#include "User.h"
#include <QFile>

User::User()            //конструктор
{}
User::~User()           //деструктор
{}

Money* User::getMoney() //получить массив личных счетов
{
    return this->cash;
}

User::User(const User& user)              //конструктор копирования
{
    this->accountData = user.accountData;
    this->_name = user._name;
    this->_surname = user._surname;
    for(int i = 0; i < 4; i++)
        this->cash[i] = user.cash[i];
}

User& User::operator=(const User& user)   //оператор присваивания
{
    if (this != &user)
    {
        this->accountData = user.accountData;
        this->_name = user._name;
        this->_surname = user._surname;
    }
    return *this;
}

bool User::operator==(User& other)        //оператор равно для сравнения элементов при поиске
{
    bool ok = false;
    if (other.getAccountData()->getId() != -1)
    {
        if (this->getAccountData()->getId() == other.getAccountData()->getId())
            ok = true;
        else
            return false;
    }
    if (other.getAccountData()->getLogin() != "")
    {
        if (this->getAccountData()->getLogin() == other.getAccountData()->getLogin())
            ok = true;
        else
            return false;
    }
    if (other.getAccountData()->getPassword() != "")
    {
        if (this->getAccountData()->getPassword() == other.getAccountData()->getPassword())
            ok = true;
        else
            return false;
    }
    if (other.getAccountData()->getBlockingStatus() != "active")
    {
        if (this->getAccountData()->getBlockingStatus() == other.getAccountData()->getBlockingStatus())
            ok = true;
        else
            return false;
    }
    if (other.getName() != "")
    {
        if (this->getName() == other.getName())
            ok = true;
        else
            return false;
    }
    for(int i = 0; i < 4; i++)
    {
        if (other.cash[i].getAmount() != - 1)
        {
            if (this->cash[i].getAmount() == other.cash[i].getAmount())
                ok = true;
            else
            {
                ok = false;
                break;
            }
        }
    }
    for(int i = 0; i < 4; i++)
    {
        if (other.cash[i].getCurrencyName() != "" )
        {
            if (this->cash[i].getCurrencyName() == other.cash[i].getCurrencyName())
                ok = true;
            else
            {
                ok = false;
                break;
            }
        }
    }
    return ok;
}

QTextStream& operator<<(QTextStream& out, User& object)  //оператор для записи в файл
{
    out << object.getAccountData()->getId() << ' ';
    out << object.getAccountData()->getLogin() << ' ';
    out << object.getAccountData()->getPassword() << ' ';
    out << object.getAccountData()->getBlockingStatus() << ' ';
    out << object.getName() << ' ';
    out << object.getSurname() << ' ' << '\n';
    return out;
}

QTextStream& operator>>(QTextStream& in, User& object)   //оператор для чтения из файла
{
    QString str;
    QStringList lst;
    str = in.readLine(); //читаем очередную строку
    lst = str.split(" "); //делим строку на слова разделенные пробелом
    object.getAccountData()->setId(lst.at(0).toInt());
    object.getAccountData()->setLogin(lst.at(1));
    object.getAccountData()->setPassword(lst.at(2));
    object.getAccountData()->setBlockingStatus(lst.at(3));
    object.setName(lst.at(4));
    object.setSurname(lst.at(5));
    return in;
}

