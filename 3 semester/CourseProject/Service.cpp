#include "Service.h"

Service::Service(int newNumber)  //конструктор
    : _idNumber(newNumber)
{}

Service::~Service()              //деструктор
{}

void Service::setNumber(int newNumber) //установка номера(id пользователя) услуги
{
    _idNumber = newNumber;
}

int Service::getNumber()               //получить номер(id пользователя) услуги
{
    return _idNumber;
}

QTextStream& operator>>(QTextStream& in, Service& service)  //оператор для чтения из файла
{
    in >> service._idNumber;
    return in;
}

QTextStream& operator<<(QTextStream& out, Service& service) //оператор для записи в файл
{
    out << service._idNumber << ' ';
    return out;
}
