#include "Calculator.h"
#include "ui_Calculator.h"
#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <QFont>
#include <QDateTime>
#include "TxtFile.h"
#include "Functions.h"
#include "Exception.h"

//==============================================КОНСТРУКТОР И ДЕСТРУКТОР===============================================

Calculator::Calculator(int num_window, QWidget *parent) : //конструктор
    QDialog(parent),
    ui(new Ui::Calculator),
    _num_window(num_window)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(_num_window); //установка рабочего окна

    QString data;    //временная строка для чтения из файла
    QStringList lst; //список прочитанной ифнормации
    QFile file(PATH"CurrencyExchangeRate.txt");         //рабочий файл
    if(file.open(QIODevice::ReadOnly |QIODevice::Text)) //открыть файл для чтения
    {
        data = file.readLine(); //читаем очередную строку
        lst = data.split(" ");  //делим строку на слова разделенные пробелом
        ui->last_update_date_label->setText(lst.at(0)+" "+lst.at(1)); //установка даты и времени
     }
     else
        QMessageBox::critical(this, "Ошибка!", "Не удалось открыть файл валют!");
    file.close(); //закрыть файл

    connect(ui->close_window_pushButton, SIGNAL(clicked()), this, SLOT(close_calculator()));
    connect(ui->close_window_pushButton_2, SIGNAL(clicked()), this, SLOT(close_calculator()));
    connect(ui->close_window_pushButton_3, SIGNAL(clicked()), this, SLOT(close_calculator()));
}

Calculator::~Calculator()            //деструктор
{
    delete ui;
}

//==============================================МЕТОДЫ(кнопки)=========================================================

void Calculator::close_calculator()  //закрыть калькулятор
{
    this->close();
}

void Calculator::on_convert_pushButton_clicked()  //конвертировать валюты
{
    bool ok1, ok2;
    QString left_currency_str = ui->lineEdit_left->text();      //получение валюты1 в виде строки
    QString right_currency_str = ui->lineEdit_right->text();    //получение валюты2 в виде строки
    float left_cur_float = left_currency_str.toFloat(&ok1);     //приведение строки(валюта1) к числу
    float right_cur_float = right_currency_str.toFloat(&ok2);   //приведение строки(валюта2) к числу
    float cur1 = choosing_currency(ui->comboBox_left->currentText());  //получение курса соответствующей выбранной валюте1
    float cur2 = choosing_currency(ui->comboBox_right->currentText()); //получение курса соответствующей выбранной валюте2
    try
    {
        if(left_cur_float < 0 || right_cur_float < 0)
            throw Exception(this, "Ошибка!", "Введенные значения не могут быть отрицательными числами");
        if(ok1 && left_currency_str != "")                 //валюта1 -> валюта2
        {
            float rez = (cur1/cur2)*left_cur_float;             //конвертирование валюты
            ui->lineEdit_right->setText(QString::number(rez));  //запись результата в строку LineEdit
        }
        else if(ok2 && right_currency_str != "")                //валюта1 <- валюта2
        {
            float rez = (cur2/cur1)*right_cur_float;            //конвертирование валюты
            ui->lineEdit_left->setText(QString::number(rez));   //запись результата в строку LineEdit
        }
        else
            throw Exception(this, "Ошибка!", "Неправильно введены значения валют для конвертирования");
    }
    catch(Exception& err) {
        err.what();
    }
}

void Calculator::on_calc_credit_Button_clicked() //рассчет кредита
{
    QFont font;
    font.setBold(true);
    ui->tableView->setFont(font);
    QStandardItemModel* model = new QStandardItemModel(5, 1, this);
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Vertical, "Сумма кредита, BYN");
    model->setHeaderData(1, Qt::Vertical, "Ежемесячный платеж, BYN");
    model->setHeaderData(2, Qt::Vertical, "Переплата, BYN");
    model->setHeaderData(3, Qt::Vertical, "Общая сумма выплат, BYN");
    model->setHeaderData(4, Qt::Vertical, "Процент переплат, %");
    model->setHeaderData(0, Qt::Horizontal, "Результаты");
    ui->tableView->setShowGrid(true); // Включаем сетку
    ui->tableView->horizontalHeader()->setStretchLastSection(true);  //Растягиваем последнюю колонку на всё доступное пространство
    ui->tableView->verticalHeader()->setStretchLastSection(true);
    bool ok1, ok2, ok3;
    float creditSum_float = ui->creditSum_lineEdit->text().toFloat(&ok1); //приведение строки(валюта1) к числу
    float percent_float = ui->procent_lineEdit->text().toFloat(&ok2);     //приведение строки(валюта2) к числу
    float term_float = ui->term_lineEdit->text().toFloat(&ok3);

    if(creditSum_float <= 0 || percent_float <= 0 || term_float <= 0)
        QMessageBox::critical(this, "Ошибка!", "Введенные значения не могут быть отрицательными числами или равными нулю");
    else if(ok1 && ok2 && ok3)
    {
        float i = percent_float/(100*12);
        float sumForMonth = creditSum_float*((i*pow(1+i, 12*term_float))/(pow(1+i, 12*term_float)-1));
        float fullSumCredit = sumForMonth*term_float*12;
        float overpayment = fullSumCredit-creditSum_float;
        float percentOfOverpayments = (overpayment/creditSum_float)*100;
        for(int row = 0; row < model->rowCount(); row++)
        {
            model->setData(model->index(0, 0), creditSum_float);
            model->setData(model->index(1, 0), sumForMonth);
            model->setData(model->index(2, 0), overpayment);
            model->setData(model->index(3, 0), fullSumCredit);
            model->setData(model->index(4, 0), percentOfOverpayments);
        }
    }
    else
        QMessageBox::critical(this, "Ошибка!", "Неправильно введенные значения");
}

void Calculator::on_calc_deposit_Button_clicked()    //рассчет депозита
{
    QFont font;
    font.setBold(true);
    ui->depositTableView->setFont(font);
    QStandardItemModel* model = new QStandardItemModel(3, 1, this);
    ui->depositTableView->setModel(model);
    model->setHeaderData(0, Qt::Vertical, "Сумма вклада, BYN");
    model->setHeaderData(1, Qt::Vertical, "Конечная сумма вклада, BYN");
    model->setHeaderData(2, Qt::Vertical, "Доход, BYN");
    model->setHeaderData(3, Qt::Vertical, "Эффективная процентная ставка, %");
    model->setHeaderData(0, Qt::Horizontal, "Результаты");
    ui->depositTableView->setShowGrid(true); // Включаем сетку
    ui->depositTableView->horizontalHeader()->setStretchLastSection(true);  // Растягиваем последнюю колонку на всё доступное пространство
    ui->depositTableView->verticalHeader()->setStretchLastSection(true);
    bool ok1, ok2, ok3;
    float depositSum_float = ui->depositSum_lineEdit->text().toFloat(&ok1);  //приведение строки(валюта1) к числу
    float percent_float = ui->depositPercent_lineEdit->text().toFloat(&ok2);  //приведение строки(валюта2) к числу
    float term_float = ui->depositTerm_lineEdit->text().toFloat(&ok3);
    if(depositSum_float <= 0 || percent_float <= 0 || term_float <= 0)
        QMessageBox::critical(this, "Ошибка!", "Введенные значения не могут быть отрицательными числами или равными нулю");
    else if(ok1 && ok2 && ok3)
    {
        float profit = (depositSum_float*percent_float*term_float)/100;
        model->setData(model->index(0, 0), depositSum_float);
        model->setData(model->index(1, 0), depositSum_float+profit);
        model->setData(model->index(2, 0), profit);
    }
    else
        QMessageBox::critical(this, "Ошибка!", "Неправильно введенные значения");
}
