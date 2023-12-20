#include "Human.h"

Human::Human(QString newName, QString newSurname) //конструктор
    : _name(newName), _surname(newSurname)
{}

Human::Human(const Human& h)//конструктор копирования
{
    this->_name = h._name;
    this->_surname = h._surname;
    this->accountData = h.accountData;
}
Human::~Human()                                   //деструктор
{}

Account* Human::getAccountData()     //метод получения данных об аккаунте
{
    return &accountData;
}
QString Human::getName()             //метод получения имени человека
{
    return _name;
}
QString Human::getSurname()          //метод получения фамилии человека
{
    return _surname;
}
void Human::setName(QString newName) //метод задания имени человека
{
    _name = newName;
}
void Human::setSurname(QString newSurname) //метод задания фамилии человека
{
    _surname = newSurname;
}
