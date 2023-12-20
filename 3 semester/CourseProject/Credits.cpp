#include "Credits.h"

Credits::Credits(float newPercent, float newTerm, QString newApplication)
{
    _percent = newPercent;
    _term = newTerm;
    _application = newApplication;
}

Credits::~Credits()
{}

void Credits::setPercent(float newPercent)
{
    _percent = newPercent;
}
void Credits::setTerm(float newTerm)
{
    _term = newTerm;
}
void Credits::setApplication(QString newApplication)
{
    _application = newApplication;
}

float Credits::getPercent()
{
    return _percent;
}
int Credits::getTerm()
{
    return _term;
}
QString Credits::getApplication()
{
    return _application;
}

QTextStream& operator>>(QTextStream& in, Credits& credit)
{
    in >> dynamic_cast<Service&>(credit);
    in >> credit._term >> credit._percent;
    in.skipWhiteSpace();
    credit._application = in.readLine();
    return in;
}

bool Credits::operator==(Credits& other)               //оператор равно для сравнения элементов
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
    return ok;
}
