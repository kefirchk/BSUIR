#include "Account.h"

Account::Account(int newId, QString newLogin, QString newPassword, QString newBlockingStatus) //конструктор
    : _id(newId), _login(newLogin), _password(newPassword), _blocking_status(newBlockingStatus)
{}
Account::~Account()                              //деструктор
{}

void Account::setLogin(QString newLogin)         //метод установления логина
{
    _login = newLogin;
}
void Account::setId(int newId)                   //метод установления идентификационного номера
{
    _id = newId;
}
void Account::setPassword(QString newPassword)   //метод установки пароля
{
    _password = newPassword;
}
void Account::setBlockingStatus(QString newBlockingStatus) //метод установки статуса блокировки
{
    _blocking_status = newBlockingStatus;
}
QString Account::getLogin()           //метод получения логина
{
    return _login;
}
int Account::getId()                  //метод получения идентификационного номера
{
    return _id;
}
QString Account::getPassword()        //метод получения пароля
{
    return _password;
}
QString Account::getBlockingStatus()  //метод получения статуса блокировки
{
    return _blocking_status;
}

Account::Account(const Account& acc)            //конструктор копирования
{
    this->_id = acc._id;
    this->_login = acc._login;
    this->_password = acc._password;
}

Account& Account::operator=(const Account& acc)   //оператор присваивания
{
    if (this != &acc)
    {
        this->_id = acc._id;
        this->_login = acc._login;
        this->_password = acc._password;
    }
    return *this;
}
