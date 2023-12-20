#include "Exception.h"

Exception::Exception(QWidget* newWidget, QString newMessage, QString newDescription)   //конструктор с параметрами
    : _window(newWidget), _error_msg(newMessage), _error_description(newDescription)
{}

Exception::~Exception()        //деструктор
{}

void Exception::what()         //метод вывода ошибки с ее кодом
{
    QMessageBox::critical(_window, _error_msg, _error_description);
}
