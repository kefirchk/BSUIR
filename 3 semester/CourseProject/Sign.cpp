#include "Sign.h"
#include "ui_Sign.h"
#include "Exception.h"

#define MAX_LEN 15  //максимальная длина вводимых строковых данных

//================================КОНСТРУКТОР И ДЕСТРУКТОР=================================

Sign::Sign(short* status, User *user, short win_num, QWidget *parent) : //конструктор
    QDialog(parent),
    ui(new Ui::Sign),
    _st(status),
    _win_num(win_num),
    _user(user)
{
    ui->setupUi(this);
    ui->sign_stackedWidget->setCurrentIndex(_win_num);

    ui->loginSignIn_lineEdit->setMaxLength(MAX_LEN);
    ui->passwordSignIn_lineEdit->setMaxLength(MAX_LEN);
    ui->passwordSignIn_lineEdit->setEchoMode(QLineEdit::Password);
    ui->loginSignUp_lineEdit->setMaxLength(MAX_LEN);
    ui->passwordSignUp_lineEdit->setMaxLength(MAX_LEN);
    ui->repeatPasswordSignUp_lineEdit->setMaxLength(MAX_LEN);
    ui->surnameSignUp_lineEdit->setMaxLength(MAX_LEN);
    ui->nameSignUp_lineEdit->setMaxLength(MAX_LEN);
}

Sign::~Sign()  //деструктор
{
    delete ui;
}

//=========================================================================================

void Sign::on_signIn_buttonBox_accepted() //подтверждение входа
{
    QString login = ui->loginSignIn_lineEdit->text();
    QString password = ui->passwordSignIn_lineEdit->text();
    _user->getAccountData()->setLogin(login);        //установка логина
    _user->getAccountData()->setPassword(password);  //установка пароля
    try
    {
        if (login == "admin" && password == "admin") //вход для администратора
            (*_st) = 2;
        else if(login != "" && login != "admin" && password != "" && password != "admin")   //вход для обычного пользователя
            (*_st) = 1;
        else
            throw Exception(this, "Ошибка!", "Ошибка авторизации!\nПроверьте правильность логина или пароля");
        close();
    }
    catch (Exception& err)
    {
        err.what();
        (*_st) = 0;   //остаемся в том же окне входа/регистрации
    }
}

//=========================================================================================

void Sign::on_signUp_buttonBox_accepted()  //подтверждение регистрации
{
    QString login = ui->loginSignUp_lineEdit->text();
    QString password = ui->passwordSignUp_lineEdit->text();
    QString repeatPassword = ui->repeatPasswordSignUp_lineEdit->text();
    QString name = ui->nameSignUp_lineEdit->text();
    QString surname = ui->surnameSignUp_lineEdit->text();
    QDate dateOfBirth = ui->dateOfBirthSignUp_lineEdit->date();
    _user->getAccountData()->setLogin(login);
    _user->getAccountData()->setPassword(password);
    _user->setName(name);
    _user->setSurname(surname);
    try
    {
        if(dateOfBirth.year() < 1900 || dateOfBirth.year() > 2022)
            throw Exception(this, "Ошибка!", "Ошибка регистрации!\nПроверьте правильность введенной даты рождения");
        else if(!ui->agree_checkBox->isChecked())
        {
            QMessageBox::warning(this, "Предупреждение!", "Вы должны дать свое согласие на обработку личных данных.");
            (*_st) = 0;
        }
        else if(password != repeatPassword || !ui->agree_checkBox->isChecked())
            throw Exception(this, "Ошибка!", "Ошибка регистрации!\nПароли не совпадают");
        else if(login != "" && password != "" && password == repeatPassword && name != "" && surname != "")
            (*_st) = 1;
        else
            throw Exception(this, "Ошибка!", "Ошибка регистрации!\nПроверьте правильность введенных данных");
        close();
    }
    catch(Exception& err)
    {
        err.what();
        (*_st) = 0;
    }
}

User* Sign::getUserData() //получение указателя на пользователя
{
    return _user;
}

void Sign::on_agree_checkBox_stateChanged(int arg1) //подтверждение лицензионного соглашения
{
    ui->agree_checkBox->setCheckState((Qt::CheckState)arg1);
}

void Sign::on_signIn_buttonBox_rejected()  //закрыть окно входа в аккаунт
{
    close();
}

void Sign::on_signUp_buttonBox_rejected()  //закрыть окно регистрации
{
    close();
}

