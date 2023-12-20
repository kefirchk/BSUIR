#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Sign.h"
#include "Functions.h"
#include "Calculator.h"
#include "User.h"
#include "ChangeMenu.h"
#include "TxtFile.cpp"
#include "TransferMoney.h"
#include "ActiveMoney.h"
#include <QList>
#include <QDateTime>
using namespace std;

//===========================КОНСТРУКТОР И ДЕСТРУКТОР======================================

MainWindow::MainWindow(QWidget *parent, short newStatus) //конструктор
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , status(newStatus)
{
    ui->setupUi(this);
    ui->search_lineEdit->setPlaceholderText("Поиск");
    ui->sumOfTransfer_lineEdit->setPlaceholderText("Сумма перевода, BYN");
    ui->idOfReceiver_lineEdit->setPlaceholderText("ID получателя");
    ui->passwordConfirm_lineEdit->setPlaceholderText("Введите пароль");
    ui->idOfReceiver_lineEdit->setMaxLength(5);
    ui->passwordConfirm_lineEdit->setMaxLength(15);

    connect(ui->signExit_pushButton, SIGNAL(clicked()), this, SLOT(exits()));
    connect(ui->mainPageExit_pushButton, SIGNAL(clicked()), this, SLOT(exits()));

    ui->credit_calculator_pushButton->setStyleSheet("text-align: left");
    ui->deposit_calculator_pushButton->setStyleSheet("text-align: left");
    ui->currency_converter_pushButton->setStyleSheet("text-align: left");
    ui->options_pushButton->setStyleSheet("text-align: left");
    ui->mainPageExit_pushButton->setStyleSheet("text-align: left");

    this->on_cleanHistory_pushButton_clicked();    
}

MainWindow::~MainWindow() //деструктор
{
    delete ui;
}

//=========================================================================================

void MainWindow::on_signIn_pushButton_clicked() //вход в аккаунт
{
    Sign window(&status, &_current_user, 0);
    window.setWindowTitle("Вход");
    window.resize(285, 160);
    window.show();
    window.exec();
    if(status)
    {
        TxtFile<User> UserFile(PATH"Users.txt");
        tree.clean(tree.getRoot());
        tree.setRoot(nullptr);
        try
        {
            if(UserFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
            {
                UserFile.readUsers(tree);
                UserFile.getQFile().close();
                if(window._user->getAccountData()->getLogin() == "admin" && window._user->getAccountData()->getPassword() == "admin")
                {
                    QMessageBox::information(this, "Уведомление", "Вы успешно вошли!");
                    ui->main_stackedWidget->setCurrentIndex(status);
                    window.close();
                }
                else if(tree.find(tree.getRoot(), _current_user))
                {
                    QMessageBox::information(this, "Уведомление", "Вы успешно вошли!");
                    _current_user.getAccountData()->setId(tree.find(tree.getRoot(), _current_user)->getData().getAccountData()->getId());
                    ui->main_stackedWidget->setCurrentIndex(status);
                    window.close();
                }
                else
                    throw Exception(&window, "Ошибка!", "Ошибка авторизации!\nПроверьте правильность логина или пароля");
            }
        }
        catch(Exception& err) {
            err.what();
        }
    }
}


void MainWindow::on_signUp_pushButton_clicked() //регистрация пользователя
{
    Sign window(&status, &_current_user, 1);
    window.setWindowTitle("Регистрация");
    window.resize(400, 290);
    window.show();
    window.exec();
    window.close();
    if (status)  //если данные введены верно, то создаем аккаунт для пользователя
    {
        tree.clean(tree.getRoot());
        TxtFile<User> UsersFile(PATH"Users.txt");
        try
        {
            if(UsersFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
            {
                UsersFile.readUsers(tree);
                UsersFile.getQFile().close();
                int id = generate_id(tree);
                _current_user.getAccountData()->setLogin(window.getUserData()->getAccountData()->getLogin());
                if (tree.find(tree.getRoot(), _current_user))
                    throw Exception(&window, "Ошибка!", "Ошибка регистрации!\nПопробуйте использовать другой логин");
                if (id == -1)
                    throw Exception(this, "Ошибка!", "Подходящее ID не было найдено!");
                _current_user.getAccountData()->setPassword(window.getUserData()->getAccountData()->getPassword());
                _current_user.setName(window.getUserData()->getName());
                _current_user.setSurname(window.getUserData()->getSurname());
                _current_user.getAccountData()->setId(id);
                if(UsersFile.openFile(QIODevice::Append | QIODevice::Text))
                {
                    UsersFile.writeUsers(_current_user);
                    UsersFile.getQFile().close();
                    tree.add(tree.getRoot(), _current_user);
                    QMessageBox::information(this, "Уведомление", "Вы успешно зарегиcтрировались!");
                    ui->main_stackedWidget->setCurrentIndex(status);
                    status = 0;
                    window.close();
                }
            }
        }
        catch(Exception& err) {
            err.what();
        }
    }
}

void MainWindow::exits() //выходы из программы
{
    QPushButton *button = (QPushButton*)sender();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Выход", "Хотите выйти?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        if(button->text() == "Выйти из аккаунта")
            ui->main_stackedWidget->setCurrentIndex(0);
        else if(button->text() == "Выход")
            QApplication::quit();
    }
}

void MainWindow::on_backForAdmin_pushButton_clicked() //кнопка "Назад" из окна режима администратора
{
    ui->main_stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_backFromUserOptions_pushButton_clicked() //кнопка "Назад" из окна настроек
{
    ui->main_stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_options_pushButton_clicked() //кнопка "Настройки"
{
    ui->main_stackedWidget->setCurrentIndex(3);
    QStandardItemModel* model = new QStandardItemModel(1, 5, this);
    ui->infoAboutUser_tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Логин");
    model->setHeaderData(2, Qt::Horizontal, "Пароль");
    model->setHeaderData(3, Qt::Horizontal, "Имя");
    model->setHeaderData(4, Qt::Horizontal, "Фамилия");

    TxtFile<User> UserFile(PATH"Users.txt");
    BinaryTree<User> usersTree;
    if(UserFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
    {
        UserFile.readUsers(usersTree);
        TreeNode<User>* founded = usersTree.find(usersTree.getRoot(), _current_user);
        _current_user.setName(founded->getData().getName());
        _current_user.setSurname(founded->getData().getSurname());
    }
    model->setData(model->index(0, 0), _current_user.getAccountData()->getId());
    model->setData(model->index(0, 1), _current_user.getAccountData()->getLogin());
    model->setData(model->index(0, 2), _current_user.getAccountData()->getPassword());
    model->setData(model->index(0, 3), _current_user.getName());
    model->setData(model->index(0, 4), _current_user.getSurname());
}

void MainWindow::on_currency_converter_pushButton_clicked() //конвертер валют
{
    Calculator calc(0);
    calc.setWindowTitle("Конвертер валют");
    calc.resize(600, 200);
    calc.show();
    calc.exec();
}

void MainWindow::on_credit_calculator_pushButton_clicked() //кредитный калькулятор
{
    Calculator calc(1);
    calc.setWindowTitle("Кредитный калькулятор");
    calc.resize(600, 370);
    calc.show();
    calc.exec();
}

void MainWindow::on_deposit_calculator_pushButton_clicked() //депозитный калькулятор
{
    Calculator calc(2);
    calc.setWindowTitle("Депозитный калькулятор");
    calc.resize(600, 370);
    calc.show();
    calc.exec();
}

void MainWindow::on_transferTo_pushButton_clicked() //перевод денежных средств
{
    bool ok1, ok2;
    QString IDReceiver_str = ui->idOfReceiver_lineEdit->text();
    QString password = ui->passwordConfirm_lineEdit->text();
    QString sumToTransfer_str = ui->sumOfTransfer_lineEdit->text();
    int IDReceiver_int = IDReceiver_str.toInt(&ok1);
    float sumToTransfer_float = sumToTransfer_str.toFloat(&ok2);
    try
    {
        if(!ok1 || !ok2 || password != _current_user.getAccountData()->getPassword())
            throw Exception(this, "Ошибка!", "Проверьте правильность введенных данных");
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение перевода", "Вы действительно хотите перевести указанную сумму?", QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            User user2;
            user2.getAccountData()->setId(IDReceiver_int);
            user2.getMoney()->setCurrencyName("BYN");
            BinaryTree<User> cashTree;
            TreeNode<User>* founded = nullptr, *curr;
            TxtFile<User> CashFile(PATH"Cash.txt");
            if(CashFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
            {
                CashFile.readCash(cashTree);
                CashFile.getQFile().close();
                if(!(founded = cashTree.find(cashTree.getRoot(), user2)))
                    throw Exception(this, "Ошибка!", "Не удалось найти пользователя с указанными данными!");
                User cur_user;
                cur_user.getAccountData()->setId(_current_user.getAccountData()->getId());
                cur_user.getMoney()[0].setCurrencyName("BYN");
                curr = cashTree.find(cashTree.getRoot(), cur_user);
                if(curr->getData().getMoney()[0].getCurrencyName() != "BYN")
                    throw Exception(this, "Ошибка!", "У вас не открыт данный счет!");
                if(curr->getData().getMoney()[0].getAmount() < sumToTransfer_float)
                    throw Exception(this, "Ошибка!", "Нехватка денежных средств для перевода!");
                if(sumToTransfer_float > 1000)
                    throw Exception(this, "Ошибка!", "Превышена максимальная сумма перевода!");
                founded->getData().getMoney()[0].setAmount(founded->getData().getMoney()[0].getAmount()+sumToTransfer_float);
                curr->getData().getMoney()[0].setAmount(curr->getData().getMoney()[0].getAmount()-sumToTransfer_float);
                if(CashFile.openFile(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
                {
                    BinaryTree<User> fwTree;
                    fwTree.setRoot(copyTree(cashTree.getRoot()));
                    fwTree.firmwareOfTree();
                    for(auto it = fwTree.begin(); it != fwTree.end(); it++)
                    {
                        for(int j = 0; j < 4; j++)
                            if ((*it).getMoney()[j].getCurrencyName() != "")
                                CashFile.writeCash(*it, j);
                    }
                    CashFile.getQFile().close();
                    QMessageBox::information(this, "Уведомление", "Перевод успешно завершен!");

                    QTableWidgetItem *item;
                    ui->transferHistory_tableWidget->setRowCount(ui->transferHistory_tableWidget->rowCount() + 1);
                    item = new QTableWidgetItem(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss"));
                    ui->transferHistory_tableWidget->setItem(ui->transferHistory_tableWidget->rowCount() - 1, 0, item);
                    item = new QTableWidgetItem(QString::number(_current_user.getAccountData()->getId())); // выделяем память под ячейку
                    ui->transferHistory_tableWidget->setItem(ui->transferHistory_tableWidget->rowCount() - 1, 1, item);
                    item = new QTableWidgetItem(ui->idOfReceiver_lineEdit->text()); // выделяем память под ячейку
                    ui->transferHistory_tableWidget->setItem(ui->transferHistory_tableWidget->rowCount() - 1, 2, item);
                    item = new QTableWidgetItem(ui->sumOfTransfer_lineEdit->text()); // выделяем память под ячейку
                    ui->transferHistory_tableWidget->setItem(ui->transferHistory_tableWidget->rowCount() - 1, 3, item);

                    TransferMoney trMoney;
                    trMoney.setDateTime(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss"));
                    trMoney.setIdOfReceiver(ui->idOfReceiver_lineEdit->text().toInt());
                    trMoney.setIdOfSender(_current_user.getAccountData()->getId());
                    trMoney.setAmount(ui->sumOfTransfer_lineEdit->text().toDouble());

                    TxtFile<TransferMoney> transferFile(PATH"TransferHistory.txt");
                    if(transferFile.openFile(QIODevice::Append | QIODevice::Text))
                    {
                        QList<TransferMoney> list;
                        list.push_back(trMoney);
                        transferFile.writeInFile(list);
                        transferFile.getQFile().close();
                    }
                }
            }
        }
    }
    catch (Exception& err) {
        err.what();
    }
}

void MainWindow::on_openNewAcc_pushButton_clicked() //открыть новый счет
{
    TxtFile<User> CashFile(PATH"Cash.txt");         //файл с открытыми счетами
    BinaryTree<User> cashTree;                      //дерево открытых счетов
    QString ch_curr = ui->chooseCurrency_comboBox->currentText(); //получение валюты, на которую пользователь хочет открыть счет
    try
    {
        if(CashFile.openFile(QIODevice::ReadOnly | QIODevice::Text)) //открыть файл для чтения
        {
            CashFile.readCash(cashTree);      //чтение из файла счетов пользователей
            CashFile.getQFile().close();      //закрыть файл
            User user;                        //временный объект класса User для поиска в дереве
            int i = matchCurrAndNum(ch_curr); //функция возвращает индекс валюты в массиве валют по ее названию
            user.getAccountData()->setId(_current_user.getAccountData()->getId()); //установка ID пользователю user
            user.getMoney()[i].setCurrencyName(ch_curr);  //установка названия валюты в соответсвующию ячейку массива счетов пользователя user
            if(cashTree.find(cashTree.getRoot(), user))   //если счет с такой валютой на такой ID уже существует
                throw Exception(this, "Ошибка!", "Вам запрещено открывать счет с данной валютой");
            if(CashFile.openFile(QIODevice::Append | QIODevice::Text)) //открыть файл для дозаписи
            {
                user.getMoney()[i].setAmount(0); //установить значение кол-ва валюты
                CashFile.writeCash(user, i);     //записать новый счет в файл
                CashFile.getQFile().close();     //закрыть файл
                QMessageBox::information(this, "Уведомление", "Новый счет успешно открыт!");
            }
        }
    }
    catch (Exception& err) {
        err.what();
    }
}

void MainWindow::on_updateAccountInfo_pushButton_clicked() //обновить таблицу со счетами
{
    QStandardItemModel* model = new QStandardItemModel(4, 3, this);
    ui->personalAccounts_tableView->setModel(model);
    ui->personalAccounts_tableView->setShowGrid(true); // Включаем сетку
    ui->personalAccounts_tableView->horizontalHeader()->setStretchLastSection(true);  // Растягиваем последнюю колонку на всё доступное пространство
    ui->personalAccounts_tableView->verticalHeader()->setStretchLastSection(true);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Сумма");
    model->setHeaderData(2, Qt::Horizontal, "Валюта");
    TxtFile<User> CashFile(PATH"Cash.txt");
    BinaryTree<User> cashTree, thisUserCashTree;
    User user;
    if(CashFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
    {
        CashFile.readCash(cashTree);
        CashFile.getQFile().close();
        user.getAccountData()->setId(_current_user.getAccountData()->getId());
        cashTree.findAll(cashTree.getRoot(), user, thisUserCashTree);
        vector <User> v_u;
        thisUserCashTree.treeToArray(thisUserCashTree.getRoot(), v_u);
        for(unsigned int i = 0; i < v_u.size(); i++)
            for(int j = 0; j < 4; j++)
                if(v_u[i].getMoney()[j].getCurrencyName() != "")
                {
                    model->setData(model->index(i, 0), v_u[i].getAccountData()->getId());
                    model->setData(model->index(i, 1), v_u[i].getMoney()[j].getAmount());
                    model->setData(model->index(i, 2), v_u[i].getMoney()[j].getCurrencyName());
                }
    }
}

void MainWindow::on_closeAcc_pushButton_clicked() //закрыть счет
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Закрытие счета", "Вы действительно хотите закрыть счет?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        TxtFile<User> CashFile(PATH"Cash.txt");
        BinaryTree<User> cashTree;
        try
        {
            if(CashFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
            {
                CashFile.readCash(cashTree);
                CashFile.getQFile().close();
                User user;
                QString ch_curr = ui->chooseCurrency_comboBox->currentText();
                int ii = matchCurrAndNum(ch_curr);
                user.getAccountData()->setId(_current_user.getAccountData()->getId());
                user.getMoney()[ii].setCurrencyName(ch_curr);
                if(!cashTree.find(cashTree.getRoot(), user))
                    throw Exception(this, "Ошибка!", "Не удалось найти такой счет для его закрытия!");
                cashTree.deleteNode(cashTree.getRoot(), user);
                CashFile.getQFile().remove();
                TxtFile<User> CashFile(PATH"Cash.txt");
                if(CashFile.openFile(QIODevice::Append | QIODevice::Text))
                {
                    BinaryTree<User> fwTree;
                    fwTree.setRoot(copyTree(cashTree.getRoot()));
                    fwTree.firmwareOfTree();
                    for(auto it = fwTree.begin(); it != fwTree.end(); it++)
                    {
                        for(int j = 0; j < 4; j++)
                            if ((*it).getMoney()[j].getCurrencyName() != "")
                                CashFile.writeCash(*it, j);
                    }
                    CashFile.getQFile().close();
                    QMessageBox::information(this, "Уведомление", "Счет успешно закрыт!");
                }
            }
        }
        catch(Exception& err) {
            err.what();
        }
    }
}

void MainWindow::on_changeCurrRate_pushButton_clicked() //обновление курса валют
{
    ChangeMenu menu(0);
    menu.setWindowTitle("Обновление курса валют");
    menu.resize(400, 300);
    menu.show();
    menu.exec();
}

void MainWindow::on_addMoney_pushButton_clicked() //пополнение счета
{
    float sum = 0;
    ChangeMenu window(1, &sum);
    window.setWindowTitle("Пополнение счета");
    window.resize(400, 145);
    window.show();
    window.exec();
    try
    {
        if(!sum)
            throw Exception(this, "Ошибка!", "Неправильно введена сумма пополнения!");
        BinaryTree<User> cashTree;
        TxtFile<User> CashFile(PATH"Cash.txt");
        if(CashFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
        {
            CashFile.readCash(cashTree);
            CashFile.getQFile().close();
            int i = matchCurrAndNum(ui->chooseCurrency_comboBox->currentText());
            User user;
            TreeNode<User>* foundedAcc;
            user.getAccountData()->setId(_current_user.getAccountData()->getId());
            user.getMoney()[i].setCurrencyName(ui->chooseCurrency_comboBox->currentText());
            if(!(foundedAcc = cashTree.find(cashTree.getRoot(), user)))
                throw Exception(this, "Ошибка!", "Не удалось найти выбранный счет для пополнения баланса");
            double old_sum = foundedAcc->getData().getMoney()[i].getAmount();
            foundedAcc->getData().getMoney()[i].setAmount(old_sum+sum);
            if(CashFile.openFile(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
            {
                vector <User> v_u;
                cashTree.treeToArray(cashTree.getRoot(), v_u);
                for(unsigned int j = 0; j < v_u.size(); j++)
                    for(int k = 0; k < 4; k++)
                        if (v_u[j].getMoney()[k].getCurrencyName() != "")
                            CashFile.writeCash(v_u[j], k);
                CashFile.getQFile().close();
                QMessageBox::information(this, "Уведомление", "Баланс успешно пополнен!");
            }
        }
    }
    catch (Exception& err) {
        err.what();
    }
}

void MainWindow::on_takeMoneyFrom_pushButton_clicked() //снятие денежных средств со счета
{
    float sum = 0;
    ChangeMenu window(2, &sum);
    window.setWindowTitle("Снятие денежных средств");
    window.resize(400, 145);
    window.show();
    window.exec();
    try
    {
        if(!sum)
            throw Exception(this, "Ошибка!", "Неправильно введена сумма для снятия!");
        BinaryTree<User> cashTree;
        TxtFile<User> CashFile(PATH"Cash.txt");
        if(CashFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
        {
            CashFile.readCash(cashTree);
            CashFile.getQFile().close();
            int i = matchCurrAndNum(ui->chooseCurrency_comboBox->currentText());
            User user;
            TreeNode<User>* foundedAcc;
            user.getAccountData()->setId(_current_user.getAccountData()->getId());
            user.getMoney()[i].setCurrencyName(ui->chooseCurrency_comboBox->currentText());
            if(!(foundedAcc = cashTree.find(cashTree.getRoot(), user)))
                throw Exception(this, "Ошибка!", "Не удалось найти выбранный счет для пополнения баланса");
            double old_sum = foundedAcc->getData().getMoney()[i].getAmount();
            if(old_sum < sum)
                throw Exception(this, "Ошибка!", "Попытка снять сумму большую, чем есть на счете");
            foundedAcc->getData().getMoney()[i].setAmount(old_sum-sum);
            if(CashFile.openFile(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
            {
                vector <User> v_u;
                cashTree.treeToArray(cashTree.getRoot(), v_u);
                for(unsigned int j = 0; j < v_u.size(); j++)
                    for(int k = 0; k < 4; k++)
                        if (v_u[j].getMoney()[k].getCurrencyName() != "")
                            CashFile.writeCash(v_u[j], k);
                CashFile.getQFile().close();
                QMessageBox::information(this, "Уведомление", "Деньги успешно сняты!");
            }
        }
    }
    catch (Exception& err) {
        err.what();
    }
}

void MainWindow::on_given_credits_triggered() //показать выдаваемые кредиты
{
    ChangeMenu window(3);
    window.setWindowTitle("Выдаваемые кредиты");
    window.resize(680, 470);
    window.show();
    window.exec();
}

void MainWindow::on_given_deposits_triggered() //показать выдаваемые депозиты
{
    ChangeMenu window(4);
    window.setWindowTitle("Выдаваемые депозиты");
    window.resize(680, 470);
    window.show();
    window.exec();
}

void MainWindow::on_cleanHistory_pushButton_clicked() //очистить историю переводов
{
    for(int column = 0; column < ui->transferHistory_tableWidget->columnCount(); column++)
        ui->transferHistory_tableWidget->removeColumn(column);
    TxtFile<TransferMoney> trFile(PATH"TransferHistory.txt");
    ui->transferHistory_tableWidget->setRowCount(0);
    ui->transferHistory_tableWidget->setColumnCount(4);
    ui->transferHistory_tableWidget->horizontalHeader()->setMinimumSectionSize(120);
    ui->transferHistory_tableWidget->horizontalHeader()->setStretchLastSection(true);  // Растягиваем последнюю колонку на всё доступное пространство
    QTableWidgetItem *item = new QTableWidgetItem("Дата и время"); // выделяем память под ячейку
    ui->transferHistory_tableWidget->setHorizontalHeaderItem(0, item);
    item = new QTableWidgetItem(); // выделяем память под ячейку
    item->setText("ID отправителя");
    ui->transferHistory_tableWidget->setHorizontalHeaderItem(1, item);
    item = new QTableWidgetItem(); // выделяем память под ячейку
    item->setText("ID получателя");
    ui->transferHistory_tableWidget->setHorizontalHeaderItem(2, item);
    item = new QTableWidgetItem(); // выделяем память под ячейку
    item->setText("Сумма");
    ui->transferHistory_tableWidget->setHorizontalHeaderItem(3, item);    
}


void MainWindow::on_takeNewCredit_pushButton_clicked() //взять новый кредит
{
    ActiveMoney credit;
    TxtFile<ActiveMoney> allCredFile;
    QString typeOfCredit = ui->typeOfNewCredit_comboBox->currentText();
    bool ok;
    credit.setPercent(ui->percentNewCreditdoubleSpinBox->value());
    credit.setTerm(ui->termNewCreddit_spinBox->value());
    double creditSum = ui->sumNewCredit_lineEdit->text().toDouble(&ok);
    try
    {
        if(!ok && creditSum > 0)
            throw Exception(this, "Ошибка!", "Неправильно введена сумма кредита!");
        float i = credit.getPercent()/(100*12);
        float sumForMonth = creditSum*((i*pow(1+i, 12*credit.getTerm()))/(pow(1+i, 12*credit.getTerm())-1));
        float fullSumCredit = sumForMonth*credit.getTerm()*12;
        credit.setAmount(fullSumCredit);
        if(typeOfCredit == "Потребительский")
            allCredFile.getQFile().setFileName(PATH"AllConsumerCredits.txt");
        else if(typeOfCredit == "На недвижимость")
            allCredFile.getQFile().setFileName(PATH"AllRealStateCredits.txt");
        else if(typeOfCredit == "Льготный")
            allCredFile.getQFile().setFileName(PATH"AllConcessionalCredits.txt");
        if(allCredFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
        {
            QList<ActiveMoney> list1;
            allCredFile.readFromFile(list1);
            allCredFile.getQFile().close();
            bool flag = false;
            for(int i = 0; i < list1.size(); i++)
            {
                if(credit == list1[i])
                {
                    credit.setApplication(list1[i].getApplication());
                    credit.setNumber(_current_user.getAccountData()->getId());
                    TxtFile<ActiveMoney> creditsFile(PATH"CreditsHistory.txt");
                    if(creditsFile.openFile(QIODevice::Append | QIODevice::Text))
                    {
                        QList<ActiveMoney> list2;
                        list2.push_back(credit);
                        creditsFile.writeInFile(list2);
                        creditsFile.getQFile().close();
                        QMessageBox::information(this, "Уведомление!", "Кредит успешно оформлен!");
                    }
                    flag = true;
                    break;
                }
            }
            if(!flag)
                throw Exception(this, "Ошибка!", "Введенный кредит не выдается!");
        }
    }
    catch(Exception& err) {
        err.what();
    }
}

void MainWindow::on_updateMyCredits_pushButton_clicked() //обновить табоицу взятых кредитов
{
    TxtFile<ActiveMoney> creditsFile(PATH"CreditsHistory.txt");
    if(creditsFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
    {
        QList<ActiveMoney> list;
        creditsFile.readFromFile(list);
        creditsFile.getQFile().close();

        ui->myCredits_tableWidget->setRowCount(0);
        ui->myCredits_tableWidget->setColumnCount(4);
        ui->myCredits_tableWidget->horizontalHeader()->setMinimumSectionSize(160);
        QTableWidgetItem *item = new QTableWidgetItem("Срок кредита, годы"); // выделяем память под ячейку
        ui->myCredits_tableWidget->setHorizontalHeaderItem(0, item);
        item = new QTableWidgetItem(); // выделяем память под ячейку
        item->setText("Ставка, %");
        ui->myCredits_tableWidget->setHorizontalHeaderItem(1, item);
        item = new QTableWidgetItem(); // выделяем память под ячейку
        item->setText("Задолженность, BYN");
        ui->myCredits_tableWidget->setHorizontalHeaderItem(2, item);
        item = new QTableWidgetItem(); // выделяем память под ячейку
        item->setText("Описание");
        ui->myCredits_tableWidget->setHorizontalHeaderItem(3, item);

        for(int i = 0; i < list.size(); i++)
        {
            if(list[i].getNumber() == _current_user.getAccountData()->getId())
            {
                ui->myCredits_tableWidget->setRowCount(ui->myCredits_tableWidget->rowCount() + 1);
                item = new QTableWidgetItem(QString::number(list[i].getTerm()));
                ui->myCredits_tableWidget->setItem(ui->myCredits_tableWidget->rowCount() - 1, 0, item);
                item = new QTableWidgetItem(QString::number(list[i].getPercent())); // выделяем память под ячейку
                ui->myCredits_tableWidget->setItem(ui->myCredits_tableWidget->rowCount() - 1, 1, item);
                item = new QTableWidgetItem(QString::number(list[i].getAmount()));  //выделяем память под ячейку
                ui->myCredits_tableWidget->setItem(ui->myCredits_tableWidget->rowCount() - 1, 2, item);
                item = new QTableWidgetItem(list[i].getApplication()); //выделяем память под ячейку
                ui->myCredits_tableWidget->setItem(ui->myCredits_tableWidget->rowCount() - 1, 3, item);
            }
        }
    }
}

void MainWindow::on_payForCredit_pushButton_clicked() //оплатить кредит
{
    QList<QTableWidgetItem*> selectedList = ui->myCredits_tableWidget->selectedItems();
    try
    {
        if(selectedList.empty())
            throw Exception(this, "Ошибка!", "Кредит не выбран!");
        float sum = 0;
        ChangeMenu window(5, &sum);
        window.setWindowTitle("Оплата кредита");
        window.resize(400, 145);
        window.show();
        window.exec();
        ActiveMoney credit;
        if(sum && sum <= ui->myCredits_tableWidget->item(selectedList.at(0)->row(), 2)->text().toDouble())
        {
            TxtFile<User> cashFile(PATH"Cash.txt");
            if(cashFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
            {
                BinaryTree<User> cashTree;
                cashFile.readCash(cashTree);
                cashFile.getQFile().close();
                TreeNode<User>* founded;
                User user;
                user.getAccountData()->setId(_current_user.getAccountData()->getId());
                user.getMoney()[0].setCurrencyName("BYN");
                if(!(founded = cashTree.find(cashTree.getRoot(), user)))
                    throw Exception(this, "Ошибка!", "На ваше имя не открыт счет с данной валютой!");
                if(sum <= founded->getData().getMoney()[0].getAmount())
                {
                    founded->getData().getMoney()[0].setAmount(founded->getData().getMoney()[0].getAmount()-sum);

                    if(cashFile.openFile(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
                    {
                        BinaryTree<User> fwTree;
                        fwTree.setRoot(copyTree(cashTree.getRoot()));
                        fwTree.firmwareOfTree();
                        for(auto it = fwTree.begin(); it != fwTree.end(); it++)
                        {
                            for(int j = 0; j < 4; j++)
                                if ((*it).getMoney()[j].getCurrencyName() != "")
                                    cashFile.writeCash(*it, j);
                        }
                        cashFile.getQFile().close();
                    }
                }
                else
                    throw Exception(this, "Ошибка!", "Недостаточно средств на балансе!");
            }
            credit.setNumber(_current_user.getAccountData()->getId());
            credit.setTerm(ui->myCredits_tableWidget->item(selectedList.at(0)->row(), 0)->text().toInt());
            credit.setPercent(ui->myCredits_tableWidget->item(selectedList.at(0)->row(), 1)->text().toFloat());
            credit.setAmount(ui->myCredits_tableWidget->item(selectedList.at(0)->row(), 2)->text().toDouble());
            credit.setApplication(ui->myCredits_tableWidget->item(selectedList.at(0)->row(), 3)->text());

            TxtFile<ActiveMoney> creditsFile(PATH"CreditsHistory.txt");
            if(creditsFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
            {
                QList<ActiveMoney> list;
                creditsFile.readFromFile(list);
                creditsFile.getQFile().close();

                for(int i = 0; i < list.size(); i++)
                {
                    if(credit == list[i])
                    {
                        if(sum == list[i].getAmount())
                        {
                            QList<ActiveMoney>::iterator it = list.begin();
                            std::advance(it, i);
                            list.erase(it);
                        }
                        else
                            list[i].setAmount(list[i].getAmount()-sum);
                        creditsFile.openFile(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
                        creditsFile.writeInFile(list);
                        creditsFile.getQFile().close();
                        QMessageBox::information(this, "Уведомление!", "Платеж кредита успешно завершен!");
                        break;
                    }
                }
            }
        }
        else
            throw Exception(this, "Ошибка!", "Неправильно введена сумма для платежа");
    }
    catch (Exception& err) {
        err.what();
    }
}

void MainWindow::on_updateMyDeposits_pushButton_clicked() //обновить таблицу взятых депозитов
{
    TxtFile<ActiveMoney> depositsFile(PATH"DepositsHistory.txt");
    if(depositsFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
    {
        QList<ActiveMoney> list;
        depositsFile.readFromFile(list);
        depositsFile.getQFile().close();

        ui->myDeposits_tableWidget->setRowCount(0);
        ui->myDeposits_tableWidget->setColumnCount(5);
        ui->myDeposits_tableWidget->horizontalHeader()->setMinimumSectionSize(160);
        QTableWidgetItem *item = new QTableWidgetItem("Срок депозита, годы"); // выделяем память под ячейку
        ui->myDeposits_tableWidget->setHorizontalHeaderItem(0, item);
        item = new QTableWidgetItem(); // выделяем память под ячейку
        item->setText("Ставка, %");
        ui->myDeposits_tableWidget->setHorizontalHeaderItem(1, item);
        item = new QTableWidgetItem(); // выделяем память под ячейку
        item->setText("Баланс, ед.");
        ui->myDeposits_tableWidget->setHorizontalHeaderItem(2, item);
        item = new QTableWidgetItem(); // выделяем память под ячейку
        item->setText("Валюта");
        ui->myDeposits_tableWidget->setHorizontalHeaderItem(3, item);
        item = new QTableWidgetItem(); // выделяем память под ячейку
        item->setText("Описание");
        ui->myDeposits_tableWidget->setHorizontalHeaderItem(4, item);

        for(int i = 0; i < list.size(); i++)
        {
            if(list[i].getNumber() == _current_user.getAccountData()->getId())
            {
                ui->myDeposits_tableWidget->setRowCount(ui->myDeposits_tableWidget->rowCount() + 1);
                item = new QTableWidgetItem(QString::number(list[i].getTerm()));
                ui->myDeposits_tableWidget->setItem(ui->myDeposits_tableWidget->rowCount() - 1, 0, item);
                item = new QTableWidgetItem(QString::number(list[i].getPercent())); // выделяем память под ячейку
                ui->myDeposits_tableWidget->setItem(ui->myDeposits_tableWidget->rowCount() - 1, 1, item);
                item = new QTableWidgetItem(QString::number(list[i].getAmount()));  //выделяем память под ячейку
                ui->myDeposits_tableWidget->setItem(ui->myDeposits_tableWidget->rowCount() - 1, 2, item);
                item = new QTableWidgetItem(list[i].getCurrencyName());  //выделяем память под ячейку
                ui->myDeposits_tableWidget->setItem(ui->myDeposits_tableWidget->rowCount() - 1, 3, item);
                item = new QTableWidgetItem(list[i].getApplication()); //выделяем память под ячейку
                ui->myDeposits_tableWidget->setItem(ui->myDeposits_tableWidget->rowCount() - 1, 4, item);
            }
        }
    }
}

void MainWindow::on_takeNewDeposit_pushButton_clicked() //взять новый депозит
{
    ActiveMoney deposit;
    TxtFile<ActiveMoney> allDepFile(PATH"AllDeposits.txt");
    QString typeOfCurrency = ui->currencyNewDeposit_comboBox->currentText();
    bool ok;
    deposit.setPercent(ui->percentNewDeposit_doubleSpinBox->value());
    deposit.setTerm(ui->termNewDeposit_spinBox->value());
    double depositSum = ui->sumNewDeposit_lineEdit->text().toDouble(&ok);
    try
    {
        if(!ok && depositSum > 0)
            throw Exception(this, "Ошибка!", "Неправильно введена сумма депозита!");
        if(allDepFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
        {
            QList<ActiveMoney> list1;
            allDepFile.readFromFile(list1);
            allDepFile.getQFile().close();
            bool flag = false;
            for(int i = 0; i < list1.size(); i++)
            {
                list1[i].setCurrencyName("");
                if(list1[i] == deposit)
                {
                    int ii = matchCurrAndNum(typeOfCurrency);
                    deposit.setCurrencyName(typeOfCurrency);
                    deposit.setAmount(depositSum);
                    deposit.setApplication(list1[i].getApplication());
                    deposit.setNumber(_current_user.getAccountData()->getId());
                    TxtFile<ActiveMoney> depositsFile(PATH"DepositsHistory.txt");
                    if(depositsFile.openFile(QIODevice::Append | QIODevice::Text))
                    {
                        QList<ActiveMoney> list2;
                        list2.push_back(deposit);
                        depositsFile.writeInFile(list2);
                        depositsFile.getQFile().close();

                        TxtFile<User> cashFile(PATH"Cash.txt");
                        BinaryTree<User> cashTree;
                        if(cashFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
                        {
                            cashFile.readCash(cashTree);
                            cashFile.getQFile().close();
                            User user;
                            user.getAccountData()->setId(_current_user.getAccountData()->getId());
                            user.getMoney()[ii].setCurrencyName(typeOfCurrency);
                            TreeNode<User>* founded;
                            founded = cashTree.find(cashTree.getRoot(), user);
                            if(founded)
                            {
                                founded->getData().getMoney()[ii].setAmount(founded->getData().getMoney()[ii].getAmount()-depositSum);
                                if(cashFile.openFile(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
                                {
                                    BinaryTree<User> fwTree;
                                    fwTree.setRoot(copyTree(cashTree.getRoot()));
                                    fwTree.firmwareOfTree();
                                    for(auto it = fwTree.begin(); it != fwTree.end(); it++)
                                    {
                                        for(int j = 0; j < 4; j++)
                                            if ((*it).getMoney()[j].getCurrencyName() != "")
                                                cashFile.writeCash(*it, j);
                                    }
                                    cashFile.getQFile().close();
                                }
                            }
                            else
                                throw Exception(this, "Ошибка!", "На ваше имя не открыт счет с данной валютой!");
                        }
                        QMessageBox::information(this, "Уведомление!", "Депозит успешно оформлен!");
                    }
                    flag = true;
                    break;
                }
            }
            if(!flag)
                throw Exception(this, "Ошибка!", "Введенный депозит не выдается!");
        }
    }
    catch(Exception& err) {
        err.what();
    }
}

void MainWindow::on_takeFromDeposit_pushButton_clicked() //снять деньги с депозитного счета
{
    QList<QTableWidgetItem*> selectedList = ui->myDeposits_tableWidget->selectedItems();
    try
    {
        if(selectedList.empty())
            throw Exception(this, "Ошибка!", "Депозит не выбран!");
        float sum = 0;
        ChangeMenu window(2, &sum);
        window.setWindowTitle("Снятие денег с депозитного счета");
        window.resize(400, 145);
        window.show();
        window.exec();
        ActiveMoney deposit;
        if(sum && sum <= ui->myDeposits_tableWidget->item(selectedList.at(0)->row(), 2)->text().toDouble())
        {
            TxtFile<User> cashFile(PATH"Cash.txt");
            if(cashFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
            {
                BinaryTree<User> cashTree;
                cashFile.readCash(cashTree);
                cashFile.getQFile().close();
                TreeNode<User>* founded;
                User user;
                user.getAccountData()->setId(_current_user.getAccountData()->getId());
                user.getMoney()[0].setCurrencyName(ui->myDeposits_tableWidget->item(selectedList.at(0)->row(), 3)->text());
                if(!(founded = cashTree.find(cashTree.getRoot(), user)))
                    throw Exception(this, "Ошибка!", "На ваше имя не открыт счет с данной валютой!");
                int ii = matchCurrAndNum(ui->myDeposits_tableWidget->item(selectedList.at(0)->row(), 3)->text());
                founded->getData().getMoney()[ii].setAmount(founded->getData().getMoney()[ii].getAmount()+sum);
                if(cashFile.openFile(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
                {
                    vector<User> v;
                    cashTree.treeToArray(cashTree.getRoot(), v);
                    for(unsigned int i = 0, j = 0; i < v.size(); i++, j++)
                        for(int j = 0; j < 4; j++)
                            if (v[i].getMoney()[j].getCurrencyName() != "")
                                cashFile.writeCash(v[i], j);
                    cashFile.getQFile().close();
                }
            }
            deposit.setNumber(_current_user.getAccountData()->getId());
            deposit.setTerm(ui->myCredits_tableWidget->item(selectedList.at(0)->row(), 0)->text().toInt());
            deposit.setPercent(ui->myCredits_tableWidget->item(selectedList.at(0)->row(), 1)->text().toFloat());
            deposit.setAmount(ui->myCredits_tableWidget->item(selectedList.at(0)->row(), 2)->text().toDouble());
            deposit.setApplication(ui->myCredits_tableWidget->item(selectedList.at(0)->row(), 3)->text());

            TxtFile<ActiveMoney> depositsFile(PATH"DepositsHistory.txt");
            if(depositsFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
            {
                QList<ActiveMoney> list;
                depositsFile.readFromFile(list);
                depositsFile.getQFile().close();

                for(int i = 0; i < list.size(); i++)
                {
                    if(deposit == list[i])
                    {
                        if(sum == list[i].getAmount())
                        {
                            QList<ActiveMoney>::iterator it = list.begin();
                            std::advance(it, i);
                            list.erase(it);
                        }
                        else
                            list[i].setAmount(list[i].getAmount()-sum);
                        depositsFile.openFile(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
                        depositsFile.writeInFile(list);
                        depositsFile.getQFile().close();
                        QMessageBox::information(this, "Уведомление!", "Деньги успешно сняты с депозитного счета!");
                        break;
                    }
                }
            }
        }
        else
            throw Exception(this, "Ошибка!", "Неправильно введена сумма для снятия денег");
    }
    catch (Exception& err) {
        err.what();
    }
}


void MainWindow::on_showAllUsers_pushButton_clicked() //показать всех зарегистрованных пользователей
{
    ui->forAdmin_tableWidget->setRowCount(0);
    ui->forAdmin_tableWidget->setColumnCount(5);
    ui->forAdmin_tableWidget->horizontalHeader()->setMinimumSectionSize(160);
    QTableWidgetItem *item = new QTableWidgetItem("ID"); // выделяем память под ячейку
    ui->forAdmin_tableWidget->setHorizontalHeaderItem(0, item);
    item = new QTableWidgetItem(); // выделяем память под ячейку
    item->setText("Логин");
    ui->forAdmin_tableWidget->setHorizontalHeaderItem(1, item);
    item = new QTableWidgetItem(); // выделяем память под ячейку
    item->setText("Пароль");
    ui->forAdmin_tableWidget->setHorizontalHeaderItem(2, item);
    item = new QTableWidgetItem(); // выделяем память под ячейку
    item->setText("Имя");
    ui->forAdmin_tableWidget->setHorizontalHeaderItem(3, item);
    item = new QTableWidgetItem(); // выделяем память под ячейку
    item->setText("Фамилия");
    ui->forAdmin_tableWidget->setHorizontalHeaderItem(4, item);

    TxtFile<User> usersFile(PATH"Users.txt");
    BinaryTree<User> usersTree;
    try
    {
        if(!usersFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
            throw Exception(this, "Ошибка открытия файла!", "Проверьте наличие и целостность файла");
        usersFile.readUsers(usersTree);
        usersFile.getQFile().close();
        vector<User> v;
        usersTree.treeToArray(usersTree.getRoot(), v);
        for(unsigned int i = 0; i < v.size(); i++)
        {
            ui->forAdmin_tableWidget->setRowCount(ui->forAdmin_tableWidget->rowCount() + 1);
            item = new QTableWidgetItem(QString::number(v[i].getAccountData()->getId()));
            ui->forAdmin_tableWidget->setItem(ui->forAdmin_tableWidget->rowCount() - 1, 0, item);
            item = new QTableWidgetItem(v[i].getAccountData()->getLogin()); // выделяем память под ячейку
            ui->forAdmin_tableWidget->setItem(ui->forAdmin_tableWidget->rowCount() - 1, 1, item);
            item = new QTableWidgetItem(v[i].getAccountData()->getPassword());  //выделяем память под ячейку
            ui->forAdmin_tableWidget->setItem(ui->forAdmin_tableWidget->rowCount() - 1, 2, item);
            item = new QTableWidgetItem(v[i].getName());  //выделяем память под ячейку
            ui->forAdmin_tableWidget->setItem(ui->forAdmin_tableWidget->rowCount() - 1, 3, item);
            item = new QTableWidgetItem(v[i].getSurname()); //выделяем память под ячейку
            ui->forAdmin_tableWidget->setItem(ui->forAdmin_tableWidget->rowCount() - 1, 4, item);
        }
    }
    catch(Exception& err)
    {
        err.what();
    }
}

void MainWindow::on_deleteUser_pushButton_clicked() //удалить пользователя из системы
{
    QList<QTableWidgetItem*> selectedList = ui->forAdmin_tableWidget->selectedItems();
    try
    {
        if(selectedList.empty())
            throw Exception(this, "Ошибка!", "Пользователь не выбран!");
        User user;
        user.getAccountData()->setId(ui->forAdmin_tableWidget->item(selectedList.at(0)->row(), 0)->text().toInt());
        user.getAccountData()->setLogin(ui->forAdmin_tableWidget->item(selectedList.at(0)->row(), 1)->text());
        user.getAccountData()->setPassword(ui->forAdmin_tableWidget->item(selectedList.at(0)->row(), 2)->text());
        user.setName(ui->forAdmin_tableWidget->item(selectedList.at(0)->row(), 3)->text());
        user.setSurname(ui->forAdmin_tableWidget->item(selectedList.at(0)->row(), 4)->text());

        BinaryTree<User> usersTree;
        TxtFile<User> usersFile(PATH"Users.txt");
        if(usersFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
        {
            usersFile.readUsers(usersTree);
            usersFile.getQFile().close();

            if(usersTree.find(usersTree.getRoot(), user))
            {
                usersTree.deleteNode(usersTree.getRoot(), user);
                usersFile.openFile(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
                vector <User> v;
                usersTree.treeToArray(usersTree.getRoot(), v);
                for(unsigned int i = 0; i < v.size(); i++)
                    usersFile.writeUsers(v[i]);
                usersFile.getQFile().close();

                usersTree.~BinaryTree();
                usersFile.getQFile().setFileName(PATH"Cash.txt");
                if(usersFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
                {
                    usersFile.readCash(usersTree);
                    usersFile.getQFile().close();
                    User user2;
                    user2.getAccountData()->setId(user.getAccountData()->getId());

                    while(!false)
                    {
                        if(usersTree.find(usersTree.getRoot(), user2))
                        {
                            usersTree.deleteNode(usersTree.getRoot(), user2);
                            usersFile.openFile(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
                            vector <User> v;
                            usersTree.treeToArray(usersTree.getRoot(), v);

                            for(unsigned int j = 0; j < v.size(); j++)
                                for(int k = 0; k < 4; k++)
                                    if (v[j].getMoney()[k].getCurrencyName() != "")
                                        usersFile.writeCash(v[j], k);
                            usersFile.getQFile().close();
                        }
                        else break;
                    }
                    QMessageBox::information(this, "Уведомление", "Пользователь успешно удален!");
                }
            }
            else
                throw Exception(this, "Ошибка!", "Не удалось найти выбранного пользователя в базе данных");
        }
    }
    catch (Exception& err) {
        err.what();
    }
}

void MainWindow::on_search_pushButton_clicked() //поиск информации в таблице зарегистрированных пользователей
{
    for(int i = 0; i < ui->forAdmin_tableWidget->rowCount(); i++)           //}
        for(int j = 0; j < ui->forAdmin_tableWidget->columnCount(); j++)    //}-белый цвет для всех ячеек таблицы
            ui->forAdmin_tableWidget->item(i, j)->setBackground(Qt::white); //}

    QString parametr = ui->search_lineEdit->text(); //получение запроса поиска в строку parametr
    if(parametr != "")
    {
        QStringList words = parametr.split(' ');    //разбиение строки parametr на отдельные слова для осуществления поиска с помощью метода split() и добавление их в контейнер words типа QStringList
        for(int i = 0; i < words.size(); i++)       //цикл по контейнеру
        {
            QList<QTableWidgetItem*> list = ui->forAdmin_tableWidget->findItems(words[i], Qt::MatchContains); //поиска информации в таблице по очередному слову из контейнера words и запись найденной информации в контейнер list типа QList<QTableWidgetItem*>
            for(int j = 0; j < list.size(); j++)    //если информация найдена
                list.at(j)->setBackground(Qt::red); //красим задний фон ячейки в красный цвет
            if(list.empty())                        //если по данному запросу(слову) ничего не найдено
                QMessageBox::information(this, "Уведомление", "По вашему запросу ничего не найдено:(");
        }
    }
}


void MainWindow::on_changeParametres_pushButton_clicked() //изменить параметры пользователя
{
    float saveBtn = 0;
    User oldUser = _current_user;
    ChangeMenu window(7, &saveBtn, &_current_user);
    window.setWindowTitle("Изменение параметров");
    window.resize(280, 230);
    window.show();
    window.exec();
    try
    {
        if(saveBtn)
        {
            TxtFile<User> usersFile(PATH"Users.txt");
            TreeNode<User>* founded;
            BinaryTree<User> usersTree;
            if(usersFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
            {
                usersFile.readUsers(usersTree);
                usersFile.getQFile().close();
                founded = usersTree.find(usersTree.getRoot(), oldUser);
                founded->getData() = _current_user;
                usersFile.openFile(QIODevice::WriteOnly | QIODevice::Text);
                usersTree.firmwareOfTree();
                for(auto it = usersTree.begin(); it != usersTree.end(); it++)
                    usersFile.writeUsers(*it);
                usersFile.getQFile().close();
                this->on_options_pushButton_clicked();
            }
        }
        else
            _current_user = oldUser;
    }
    catch (Exception& err) {
        err.what();
    }
}

void MainWindow::on_editUser_pushButton_clicked() //изменить поля пользователя
{
    QList<QTableWidgetItem*> selectedList = ui->forAdmin_tableWidget->selectedItems();
    try
    {
        if(selectedList.empty())
            throw Exception(this, "Ошибка!", "Пользователь не выбран!");

        User user, oldUser;
        user.getAccountData()->setId(ui->forAdmin_tableWidget->item(selectedList.at(0)->row(), 0)->text().toInt());
        user.getAccountData()->setLogin(ui->forAdmin_tableWidget->item(selectedList.at(0)->row(), 1)->text());
        user.getAccountData()->setPassword(ui->forAdmin_tableWidget->item(selectedList.at(0)->row(), 2)->text());
        user.setName(ui->forAdmin_tableWidget->item(selectedList.at(0)->row(), 3)->text());
        user.setSurname(ui->forAdmin_tableWidget->item(selectedList.at(0)->row(), 4)->text());
        oldUser = user;

        float saveBtn = 0;
        ChangeMenu window(7, &saveBtn, &user);
        window.setWindowTitle("Изменение параметров");
        window.resize(280, 230);
        window.show();
        window.exec();
        if(saveBtn)
        {
            TxtFile<User> usersFile(PATH"Users.txt");
            TreeNode<User>* founded;
            BinaryTree<User> usersTree;
            if(usersFile.openFile(QIODevice::ReadOnly | QIODevice::Text))
            {
                usersFile.readUsers(usersTree);
                usersFile.getQFile().close();
                founded = usersTree.find(usersTree.getRoot(), oldUser);
                founded->getData() = user;
                usersFile.openFile(QIODevice::WriteOnly | QIODevice::Text);
                usersTree.firmwareOfTree();
                for(auto it = usersTree.begin(); it != usersTree.end(); it++)
                    usersFile.writeUsers(*it);
                usersFile.getQFile().close();
                this->on_showAllUsers_pushButton_clicked();
            }
        }
    }
    catch (Exception& err) {
        err.what();
    }
}

void MainWindow::on_action_triggered()
{
    QMessageBox::aboutQt(this);
}


