#include "ChangeMenu.h"
#include "ui_ChangeMenu.h"
#include <QDateTime>
#include <QStandardItemModel>

#include "Functions.h"
#include "TxtFile.cpp"
#include "ActiveMoney.h"

ChangeMenu::ChangeMenu(int newStatus, float* newSum, User* user, QWidget *parent) : //конструктор
    QDialog(parent),
    ui(new Ui::ChangeMenu),
    _status(newStatus),
    _sum(newSum),
    _curr_user(user)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(_status);
    ui->newRUBRate_lineEdit->setPlaceholderText("Российский рубль");
    ui->newDOLRate_lineEdit->setPlaceholderText("Доллар США");
    ui->newEURRate_lineEdit->setPlaceholderText("Евро");
    if(user)
    {
        ui->changeLogin_lineEdit->setText(this->_curr_user->getAccountData()->getLogin());
        ui->changePassword_lineEdit->setText(this->_curr_user->getAccountData()->getPassword());
        ui->changeName_lineEdit->setText(this->_curr_user->getName());
        ui->changeSurname_lineEdit->setText(this->_curr_user->getSurname());
    }
}

ChangeMenu::~ChangeMenu() //деструктор
{
    delete ui;
}

void ChangeMenu::on_ExchCurrRate_buttonBox_accepted() //изменение курса валют
{
    bool ok1, ok2, ok3;
    float dol_float = ui->newDOLRate_lineEdit->text().toFloat(&ok1);
    float eur_float = ui->newEURRate_lineEdit->text().toFloat(&ok2);
    float rub_float = ui->newRUBRate_lineEdit->text().toFloat(&ok3);
    try
    {
        if(ok1 && ok2 && ok3)
        {
            QFile ExchRate_file(PATH"CurrencyExchangeRate.txt");
            if(!ExchRate_file.open(QIODevice::WriteOnly | QIODevice::Text))
                throw Exception(this, "Ошибка!", "Не удалось открыть файл!");
            QTextStream out(&ExchRate_file);
            out << QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss") << ' ';
            out << rub_float << ' ' << dol_float << ' ' << eur_float;
            ExchRate_file.close();
            QMessageBox::information(this, "Уведомление", "Курс валют успешно обновлен!");
        }
        else
           throw Exception(this, "Ошибка!", "Неправильно введены курсы валют!");
    }
    catch(Exception& err) {
        err.what();
    }
}

void ChangeMenu::on_addToAccSum_Button_clicked()     //закрыть окно пополнения баланса с возвращением суммы для пополнения
{
    get_float(_sum, ui->addingSum_lineEdit->text());
    try
    {
        if(!_sum)
            throw Exception(this, "Ошибка!", "Неправильно введены курсы валют!");
    }
    catch(Exception& err)
    {
        err.what();
    }
    this->close();
}

void ChangeMenu::on_takeFromAccSum_Button_clicked()  //закрыть окно снятия денег со счета с возвращением суммы для снятия
{
    get_float(_sum, ui->takkingFromSum_lineEdit->text());
    try
    {
        if(!_sum)
            throw Exception(this, "Ошибка!", "Неправильно введены курсы валют!");
    }
    catch(Exception& err)
    {
        err.what();
    }
    this->close();
}

void ChangeMenu::on_payForCreditSum_Button_clicked() //закрыть окно для оплаты кредита с возвращением суммы для оплаты кредита
{
    get_float(_sum, ui->payingCreditSum_lineEdit->text());
    try
    {
        if(!_sum)
            throw Exception(this, "Ошибка!", "Неправильно введены курсы валют!");
    }
    catch(Exception& err)
    {
        err.what();
    }
    this->close();
}

void ChangeMenu::on_closeGivenCredits_pushButton_clicked() //закрыть окно выдаваемых кредитов
{
    this->close();
}
void ChangeMenu::on_closeGivenDeposits_pushButton_clicked() //закрыть окно выдаваемых депозитов
{
    this->close();
}


void ChangeMenu::on_showPossibleCredits_pushButton_clicked() //показать выдаваемые кредиты
{
    QStandardItemModel* model = new QStandardItemModel(30, 3, this);
    ui->givenCredits_tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, "Срок действия, годы");
    model->setHeaderData(1, Qt::Horizontal, "Ставка, %");
    model->setHeaderData(2, Qt::Horizontal, "Описание");
    ui->givenCredits_tableView->setShowGrid(true); // Включаем сетку
    ui->givenCredits_tableView->horizontalHeader()->setMinimumSectionSize(140);
    ui->givenCredits_tableView->horizontalHeader()->setStretchLastSection(true);  // Растягиваем последнюю колонку на всё доступное пространство
    ui->givenCredits_tableView->verticalHeader()->setStretchLastSection(true);
    TxtFile<ActiveMoney> creditsFile;
    QList<ActiveMoney> list;
    if(ui->creditsOnConsumer_checkBox->isChecked())
    {
        creditsFile.getQFile().setFileName(PATH"AllConsumerCredits.txt");
        if(creditsFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
        {
            creditsFile.readFromFile(list);
            creditsFile.getQFile().close();
        }
    }
    if(ui->creditsOnConcessional_checkBox->isChecked())
    {
        creditsFile.getQFile().setFileName(PATH"AllConcessionalCredits.txt");
        if(creditsFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
        {
            creditsFile.readFromFile(list);
            creditsFile.getQFile().close();
        }
    }
    if(ui->creditdsOnRealState_checkBox->isChecked())
    {
        creditsFile.getQFile().setFileName(PATH"AllRealStateCredits.txt");
        if(creditsFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
        {
            creditsFile.readFromFile(list);
            creditsFile.getQFile().close();
        }
    }
    for(int row = 0; row < list.size(); row++)
    {
        model->setData(model->index(row, 0), list[row].getTerm());
        model->setData(model->index(row, 1), list[row].getPercent());
        model->setData(model->index(row, 2), list[row].getApplication());
    }
}

void ChangeMenu::on_showPossibleDeposits_pushButton_clicked()  //показать выдаваемые депозиты
{
    QStandardItemModel* model = new QStandardItemModel(30, 3, this);
    ui->givenDeposits_tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, "Срок действия, годы");
    model->setHeaderData(1, Qt::Horizontal, "Ставка, %");
    model->setHeaderData(2, Qt::Horizontal, "Описание");
    ui->givenDeposits_tableView->setShowGrid(true); // Включаем сетку
    ui->givenDeposits_tableView->horizontalHeader()->setMinimumSectionSize(140);
    ui->givenDeposits_tableView->horizontalHeader()->setStretchLastSection(true);  // Растягиваем последнюю колонку на всё доступное пространство
    ui->givenDeposits_tableView->verticalHeader()->setStretchLastSection(true);
    TxtFile<ActiveMoney> depositsFile(PATH"AllDeposits.txt");
    QList<ActiveMoney> list;
    if(depositsFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
    {
        depositsFile.readFromFile(list);
        depositsFile.getQFile().close();
        for(int row = 0; row < list.size(); row++)
        {
            model->setData(model->index(row, 0), list[row].getTerm());
            model->setData(model->index(row, 1), list[row].getPercent());
            model->setData(model->index(row, 2), list[row].getApplication());
        }
    }
}

void ChangeMenu::on_saveChanges_pushButton_clicked() //сохранить изменененные поля
{
    _curr_user->getAccountData()->setLogin(ui->changeLogin_lineEdit->text());
    _curr_user->getAccountData()->setPassword(ui->changePassword_lineEdit->text());
    _curr_user->setName(ui->changeName_lineEdit->text());
    _curr_user->setSurname(ui->changeSurname_lineEdit->text());
    QMessageBox::information(this, "Уведомление", "Информация успешно изменена!");
    *_sum = 1;  //признак, что была нажата кнопка "Сохранить"
}

