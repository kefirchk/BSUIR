#include "TransferMoney.h"
#include <QStringList>

TransferMoney::TransferMoney(int senderId, int receiverId, QString dt, double sum) //конструктор
    : _idOfReceiver(receiverId), _idOfSender(senderId), _dateTime(dt)
{
    this->_amount = sum;
}

TransferMoney::~TransferMoney()       //деструктор
{}

int TransferMoney::getIdOfReceiver()  //получение ID получателя
{
    return _idOfReceiver;
}
int TransferMoney::getIdOfSender()    //получение ID отправителя
{
    return _idOfSender;
}
QString TransferMoney::getDateTime()  //получения даты и времени перевода
{
    return _dateTime;
}
void TransferMoney::setIdOfReceiver(int id) //установка ID получателя
{
    _idOfReceiver = id;
}
void TransferMoney::setIdOfSender(int id)   //установка ID отправителя
{
    _idOfSender = id;
}
void TransferMoney::setDateTime(QString dt) //установка даты и времени перевода
{
    _dateTime = dt;
}

QTextStream& operator<<(QTextStream& out, TransferMoney& trMoney)  //оператор для записи в файл
{
    out << trMoney.getDateTime() << ' ' << trMoney.getIdOfSender() << ' '
        << trMoney.getIdOfReceiver() << ' ' << trMoney.getAmount() << '\n';
    return out;
}

QTextStream& operator>>(QTextStream& in, TransferMoney& trMoney)   //оператор для чтения из файла
{
    QStringList list;
    list = in.readLine().split(' ');
    trMoney.setDateTime(list.at(0) + ' ' + list.at(1));
    trMoney.setIdOfSender(list.at(3).toInt());
    trMoney.setIdOfReceiver(list.at(4).toInt());
    trMoney.setAmount(list.at(5).toDouble());
    return in;
}

