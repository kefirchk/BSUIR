#include "Functions.h"
#include "Administrator.h"
#include "Calculator.h"
#include "TxtFile.h"
#include "User.h"

int generate_id(BinaryTree<User> &tree)    //функция генерирования ID
{
    User user;                             //временный пользователь для проверки
    int id;                                //переменная для хранения ID
    for(int i = 0; i <= INT_MAX; i++)
    {
        srand(time(0));                    //чтобы ID не повторялось при каждом запуске приложения
        id = rand() % RAND_MAX + 1;        //случайное число(ID)
        if(i == INT_MAX)                   //превышен лимит значений ID
            return -1;
        user.getAccountData()->setId(id);  //установка пользователю найденного ID
        if(!tree.find(tree.getRoot(), user)) //проверка на совпадение ID
            break;
    }
    return id;  //вернуть ID
}


float choosing_currency(QString option)   //метод получения курса валют по заданной строке
{
    Calculator temp;
    Administrator admin;
    QString str;
    QStringList lst;
    QFile CurrExchRateFile(PATH"CurrencyExchangeRate.txt");
    if(CurrExchRateFile.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        while(!CurrExchRateFile.atEnd())
        {
            str = CurrExchRateFile.readLine(); //читаем очередную строку
            lst = str.split(" "); //делим строку на слова разделенные пробелом
            admin.setRateRUB(lst.at(2).toFloat());
            admin.setRateDOL(lst.at(3).toFloat());
            admin.setRateEUR(lst.at(4).toFloat());
        }
        CurrExchRateFile.close();
    }
    else
    {
        QMessageBox::critical(&temp, "Ошибка!", "Не удается открыть файл!");
        return 0;
    }
    if(option == "Белорусский рубль(BYN)")
        return 1;
    else if(option =="Российский рубль(RUB)")
        return admin.getRateRUB();
    else if(option =="Доллар США(USD)")
        return admin.getRateDOL();
    else if(option == "Евро(EUR)")
        return admin.getRateEUR();
    else
    {
        QMessageBox::critical(&temp, "Ошибка!", "Не найдена соответствующая валюта");
        return 0;
    }
}

int matchCurrAndNum(QString ch_curr)  //функция соответствия строке названия валюты ее индексу
{
    if(ch_curr == "BYN")
        return 0;
    else if(ch_curr == "RUB")
        return 1;
    else if(ch_curr == "DOL")
        return 2;
    else //if(ch_curr == "EUR")
        return 3;
}

void get_float(float*& _sum, QString sum_str)  //функция проверки на вещественное число
{
    bool ok;
    float sum_float = sum_str.toFloat(&ok);
    if(ok && sum_float > 0 && sum_float <= 100)
        *_sum = sum_float;
    else
        *_sum = 0;
}
