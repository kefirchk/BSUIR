/********************************************************************************
** Form generated from reading UI file 'Sign.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGN_H
#define UI_SIGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sign
{
public:
    QStackedWidget *sign_stackedWidget;
    QWidget *page;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QFormLayout *formLayout;
    QLabel *loginSignIn_label;
    QLineEdit *loginSignIn_lineEdit;
    QLabel *passwordSignIn_label;
    QLineEdit *passwordSignIn_lineEdit;
    QDialogButtonBox *signIn_buttonBox;
    QWidget *page_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_3;
    QLineEdit *surnameSignUp_lineEdit;
    QLineEdit *repeatPasswordSignUp_lineEdit;
    QDateEdit *dateOfBirthSignUp_lineEdit;
    QLineEdit *loginSignUp_lineEdit;
    QLabel *passwordSignUp_label;
    QLabel *loginSignUp_label;
    QLabel *nameSignUp_label;
    QLineEdit *nameSignUp_lineEdit;
    QLabel *repeatPasswordSignUp_label;
    QLabel *dateOfBirthSignUp_label;
    QLineEdit *passwordSignUp_lineEdit;
    QLabel *surnameSignUp_label;
    QCheckBox *agree_checkBox;
    QLabel *agree_label;
    QDialogButtonBox *signUp_buttonBox;

    void setupUi(QDialog *Sign)
    {
        if (Sign->objectName().isEmpty())
            Sign->setObjectName("Sign");
        Sign->resize(521, 291);
        sign_stackedWidget = new QStackedWidget(Sign);
        sign_stackedWidget->setObjectName("sign_stackedWidget");
        sign_stackedWidget->setGeometry(QRect(0, 0, 501, 351));
        page = new QWidget();
        page->setObjectName("page");
        groupBox = new QGroupBox(page);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 10, 261, 131));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName("gridLayout_2");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        loginSignIn_label = new QLabel(groupBox);
        loginSignIn_label->setObjectName("loginSignIn_label");
        QFont font;
        font.setFamilies({QString::fromUtf8("Harrington")});
        font.setPointSize(10);
        loginSignIn_label->setFont(font);

        formLayout->setWidget(0, QFormLayout::LabelRole, loginSignIn_label);

        loginSignIn_lineEdit = new QLineEdit(groupBox);
        loginSignIn_lineEdit->setObjectName("loginSignIn_lineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, loginSignIn_lineEdit);

        passwordSignIn_label = new QLabel(groupBox);
        passwordSignIn_label->setObjectName("passwordSignIn_label");
        passwordSignIn_label->setFont(font);

        formLayout->setWidget(1, QFormLayout::LabelRole, passwordSignIn_label);

        passwordSignIn_lineEdit = new QLineEdit(groupBox);
        passwordSignIn_lineEdit->setObjectName("passwordSignIn_lineEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, passwordSignIn_lineEdit);

        signIn_buttonBox = new QDialogButtonBox(groupBox);
        signIn_buttonBox->setObjectName("signIn_buttonBox");
        signIn_buttonBox->setOrientation(Qt::Horizontal);
        signIn_buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(2, QFormLayout::SpanningRole, signIn_buttonBox);


        gridLayout_2->addLayout(formLayout, 0, 0, 1, 1);

        sign_stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        groupBox_2 = new QGroupBox(page_2);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 10, 381, 271));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        surnameSignUp_lineEdit = new QLineEdit(groupBox_2);
        surnameSignUp_lineEdit->setObjectName("surnameSignUp_lineEdit");

        gridLayout_3->addWidget(surnameSignUp_lineEdit, 3, 1, 1, 1);

        repeatPasswordSignUp_lineEdit = new QLineEdit(groupBox_2);
        repeatPasswordSignUp_lineEdit->setObjectName("repeatPasswordSignUp_lineEdit");

        gridLayout_3->addWidget(repeatPasswordSignUp_lineEdit, 2, 1, 1, 1);

        dateOfBirthSignUp_lineEdit = new QDateEdit(groupBox_2);
        dateOfBirthSignUp_lineEdit->setObjectName("dateOfBirthSignUp_lineEdit");

        gridLayout_3->addWidget(dateOfBirthSignUp_lineEdit, 5, 1, 1, 1);

        loginSignUp_lineEdit = new QLineEdit(groupBox_2);
        loginSignUp_lineEdit->setObjectName("loginSignUp_lineEdit");

        gridLayout_3->addWidget(loginSignUp_lineEdit, 0, 1, 1, 1);

        passwordSignUp_label = new QLabel(groupBox_2);
        passwordSignUp_label->setObjectName("passwordSignUp_label");

        gridLayout_3->addWidget(passwordSignUp_label, 1, 0, 1, 1);

        loginSignUp_label = new QLabel(groupBox_2);
        loginSignUp_label->setObjectName("loginSignUp_label");

        gridLayout_3->addWidget(loginSignUp_label, 0, 0, 1, 1);

        nameSignUp_label = new QLabel(groupBox_2);
        nameSignUp_label->setObjectName("nameSignUp_label");

        gridLayout_3->addWidget(nameSignUp_label, 4, 0, 1, 1);

        nameSignUp_lineEdit = new QLineEdit(groupBox_2);
        nameSignUp_lineEdit->setObjectName("nameSignUp_lineEdit");

        gridLayout_3->addWidget(nameSignUp_lineEdit, 4, 1, 1, 1);

        repeatPasswordSignUp_label = new QLabel(groupBox_2);
        repeatPasswordSignUp_label->setObjectName("repeatPasswordSignUp_label");

        gridLayout_3->addWidget(repeatPasswordSignUp_label, 2, 0, 1, 1);

        dateOfBirthSignUp_label = new QLabel(groupBox_2);
        dateOfBirthSignUp_label->setObjectName("dateOfBirthSignUp_label");

        gridLayout_3->addWidget(dateOfBirthSignUp_label, 5, 0, 1, 1);

        passwordSignUp_lineEdit = new QLineEdit(groupBox_2);
        passwordSignUp_lineEdit->setObjectName("passwordSignUp_lineEdit");

        gridLayout_3->addWidget(passwordSignUp_lineEdit, 1, 1, 1, 1);

        surnameSignUp_label = new QLabel(groupBox_2);
        surnameSignUp_label->setObjectName("surnameSignUp_label");

        gridLayout_3->addWidget(surnameSignUp_label, 3, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        agree_checkBox = new QCheckBox(groupBox_2);
        agree_checkBox->setObjectName("agree_checkBox");

        verticalLayout->addWidget(agree_checkBox);

        agree_label = new QLabel(groupBox_2);
        agree_label->setObjectName("agree_label");

        verticalLayout->addWidget(agree_label);

        signUp_buttonBox = new QDialogButtonBox(groupBox_2);
        signUp_buttonBox->setObjectName("signUp_buttonBox");
        signUp_buttonBox->setOrientation(Qt::Horizontal);
        signUp_buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(signUp_buttonBox);

        sign_stackedWidget->addWidget(page_2);

        retranslateUi(Sign);

        sign_stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Sign);
    } // setupUi

    void retranslateUi(QDialog *Sign)
    {
        Sign->setWindowTitle(QCoreApplication::translate("Sign", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Sign", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        loginSignIn_label->setText(QCoreApplication::translate("Sign", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        passwordSignIn_label->setText(QCoreApplication::translate("Sign", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Sign", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        passwordSignUp_label->setText(QCoreApplication::translate("Sign", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        loginSignUp_label->setText(QCoreApplication::translate("Sign", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        nameSignUp_label->setText(QCoreApplication::translate("Sign", "\320\230\320\274\321\217", nullptr));
        repeatPasswordSignUp_label->setText(QCoreApplication::translate("Sign", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        dateOfBirthSignUp_label->setText(QCoreApplication::translate("Sign", "\320\224\320\260\321\202\320\260 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217", nullptr));
        surnameSignUp_label->setText(QCoreApplication::translate("Sign", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217", nullptr));
        agree_checkBox->setText(QCoreApplication::translate("Sign", "\320\257 \320\277\320\276\320\264\321\202\320\262\320\265\321\200\320\266\320\264\320\260\321\216, \321\207\321\202\320\276 \320\277\321\200\320\276\321\207\320\270\321\202\320\260\320\273(a) \320\273\320\270\321\206\320\265\320\275\320\267\320\270\320\276\320\275\320\275\320\276\320\265 \321\201\320\276\320\263\320\273\320\260\321\210\320\265\320\275\320\270\320\265,", nullptr));
        agree_label->setText(QCoreApplication::translate("Sign", "\320\270 \320\264\320\260\321\216 \321\201\320\262\320\276\320\265 \321\201\320\276\320\263\320\273\320\260\321\201\320\270\320\265 \320\275\320\260 \320\276\320\261\321\200\320\260\320\261\320\276\321\202\320\272\321\203 \320\277\320\265\321\200\321\201\320\276\320\275\320\260\320\273\321\214\320\275\321\213\321\205 \320\264\320\260\320\275\320\275\321\213\321\205.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Sign: public Ui_Sign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGN_H
