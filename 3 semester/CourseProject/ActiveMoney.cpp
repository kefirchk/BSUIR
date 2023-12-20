#include "ActiveMoney.h"

ActiveMoney::ActiveMoney(float newPercent, float newTerm, QString newApplication) //конструктор
    : _percent(newPercent), _term(newTerm), _application(newApplication)
{}

ActiveMoney::~ActiveMoney() //деструктор
{}

void ActiveMoney::setPercent(float newPercent) //метод задания значения для ставки
{
    _percent = newPercent;
}
void ActiveMoney::setTerm(int newTerm)       //метод задания значения периода действия
{
    _term = newTerm;
}
void ActiveMoney::setApplication(QString newApplication) //метод задания описания
{
    _application = newApplication;
}

float ActiveMoney::getPercent() //метод получения ставки
{
    return _percent;
}
int ActiveMoney::getTerm()      //метод получения периода действия
{
    return _term;
}
QString ActiveMoney::getApplication()  //метод получения описания
{
    return _application;
}

QTextStream& operator>>(QTextStream& in, ActiveMoney& actMoney) //оператор для чтения из файла
{
    in >> dynamic_cast<Service&>(actMoney);
    in >> actMoney._term >> actMoney._percent >> actMoney._amount >> actMoney._currencyName;
    in.skipWhiteSpace();
    actMoney._application = in.readLine();
    return in;
}

QTextStream& operator<<(QTextStream& out, ActiveMoney& actMoney) //оператор для записи в файл
{
    out << dynamic_cast<Service&>(actMoney);
    out << actMoney._term << ' ' << actMoney._percent << ' '
        << actMoney._amount << ' '  << actMoney._currencyName << ' ' << actMoney._application << '\n';
    return out;
}

bool ActiveMoney::operator==(ActiveMoney& other) //оператор равно
{
    bool ok = false;
    if(other._percent != -1)
    {
        if(other._percent == this->_percent)
            ok = true;
        else return false;
    }
    if(other._term != -1)
    {
        if(other._term == this->_term)
            ok = true;
        else return false;
    }
    if(other._currencyName != "")
    {
        if(other._currencyName == this->_currencyName)
            ok = true;
        else return false;
    }
    return ok;
}
