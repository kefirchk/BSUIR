/********************************************************************************
** Form generated from reading UI file 'ChangeMenu.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEMENU_H
#define UI_CHANGEMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangeMenu
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QDialogButtonBox *ExchCurrRate_buttonBox;
    QLineEdit *newRUBRate_lineEdit;
    QLineEdit *newDOLRate_lineEdit;
    QLineEdit *newEURRate_lineEdit;
    QLabel *inviteToEnterNewExchRate_label;
    QWidget *page_2;
    QPushButton *addToAccSum_Button;
    QLineEdit *addingSum_lineEdit;
    QLabel *inviteToAddAccSum_label;
    QWidget *page_3;
    QPushButton *takeFromAccSum_Button;
    QLabel *inviteToTakeFromAccSum_label;
    QLineEdit *takkingFromSum_lineEdit;
    QWidget *page_4;
    QPushButton *closeGivenCredits_pushButton;
    QTableView *givenCredits_tableView;
    QCheckBox *creditsOnConcessional_checkBox;
    QCheckBox *creditsOnConsumer_checkBox;
    QCheckBox *creditdsOnRealState_checkBox;
    QPushButton *showPossibleCredits_pushButton;
    QWidget *page_5;
    QTableView *givenDeposits_tableView;
    QPushButton *closeGivenDeposits_pushButton;
    QPushButton *showPossibleDeposits_pushButton;
    QWidget *page_6;
    QPushButton *payForCreditSum_Button;
    QLineEdit *payingCreditSum_lineEdit;
    QLabel *inviteToPayCreditSum_label;
    QWidget *page_7;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *undo_pushButton;
    QPushButton *redo_pushButton;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *changeLogin_label;
    QLineEdit *changeLogin_lineEdit;
    QLabel *changePassword_label;
    QLineEdit *changePassword_lineEdit;
    QLabel *changeName_label;
    QLineEdit *changeName_lineEdit;
    QLabel *changeSurname_label;
    QLineEdit *changeSurname_lineEdit;
    QPushButton *saveChanges_pushButton;

    void setupUi(QDialog *ChangeMenu)
    {
        if (ChangeMenu->objectName().isEmpty())
            ChangeMenu->setObjectName("ChangeMenu");
        ChangeMenu->resize(685, 482);
        stackedWidget = new QStackedWidget(ChangeMenu);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 681, 461));
        page = new QWidget();
        page->setObjectName("page");
        ExchCurrRate_buttonBox = new QDialogButtonBox(page);
        ExchCurrRate_buttonBox->setObjectName("ExchCurrRate_buttonBox");
        ExchCurrRate_buttonBox->setGeometry(QRect(40, 250, 341, 32));
        ExchCurrRate_buttonBox->setOrientation(Qt::Horizontal);
        ExchCurrRate_buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        newRUBRate_lineEdit = new QLineEdit(page);
        newRUBRate_lineEdit->setObjectName("newRUBRate_lineEdit");
        newRUBRate_lineEdit->setGeometry(QRect(30, 90, 331, 31));
        newDOLRate_lineEdit = new QLineEdit(page);
        newDOLRate_lineEdit->setObjectName("newDOLRate_lineEdit");
        newDOLRate_lineEdit->setGeometry(QRect(30, 140, 331, 31));
        newEURRate_lineEdit = new QLineEdit(page);
        newEURRate_lineEdit->setObjectName("newEURRate_lineEdit");
        newEURRate_lineEdit->setGeometry(QRect(30, 190, 331, 31));
        inviteToEnterNewExchRate_label = new QLabel(page);
        inviteToEnterNewExchRate_label->setObjectName("inviteToEnterNewExchRate_label");
        inviteToEnterNewExchRate_label->setGeometry(QRect(20, 40, 439, 37));
        QFont font;
        font.setFamilies({QString::fromUtf8("Tahoma")});
        font.setPointSize(18);
        font.setBold(true);
        inviteToEnterNewExchRate_label->setFont(font);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        addToAccSum_Button = new QPushButton(page_2);
        addToAccSum_Button->setObjectName("addToAccSum_Button");
        addToAccSum_Button->setGeometry(QRect(120, 90, 151, 45));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Tahoma")});
        font1.setPointSize(14);
        addToAccSum_Button->setFont(font1);
        addingSum_lineEdit = new QLineEdit(page_2);
        addingSum_lineEdit->setObjectName("addingSum_lineEdit");
        addingSum_lineEdit->setGeometry(QRect(140, 60, 113, 26));
        inviteToAddAccSum_label = new QLabel(page_2);
        inviteToAddAccSum_label->setObjectName("inviteToAddAccSum_label");
        inviteToAddAccSum_label->setGeometry(QRect(50, 20, 340, 28));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Tahoma")});
        font2.setPointSize(14);
        font2.setBold(true);
        inviteToAddAccSum_label->setFont(font2);
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        takeFromAccSum_Button = new QPushButton(page_3);
        takeFromAccSum_Button->setObjectName("takeFromAccSum_Button");
        takeFromAccSum_Button->setGeometry(QRect(120, 90, 151, 45));
        takeFromAccSum_Button->setFont(font1);
        inviteToTakeFromAccSum_label = new QLabel(page_3);
        inviteToTakeFromAccSum_label->setObjectName("inviteToTakeFromAccSum_label");
        inviteToTakeFromAccSum_label->setGeometry(QRect(60, 20, 327, 28));
        inviteToTakeFromAccSum_label->setFont(font2);
        takkingFromSum_lineEdit = new QLineEdit(page_3);
        takkingFromSum_lineEdit->setObjectName("takkingFromSum_lineEdit");
        takkingFromSum_lineEdit->setGeometry(QRect(140, 60, 113, 26));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        closeGivenCredits_pushButton = new QPushButton(page_4);
        closeGivenCredits_pushButton->setObjectName("closeGivenCredits_pushButton");
        closeGivenCredits_pushButton->setGeometry(QRect(570, 420, 93, 29));
        givenCredits_tableView = new QTableView(page_4);
        givenCredits_tableView->setObjectName("givenCredits_tableView");
        givenCredits_tableView->setGeometry(QRect(10, 10, 661, 401));
        givenCredits_tableView->setSortingEnabled(true);
        creditsOnConcessional_checkBox = new QCheckBox(page_4);
        creditsOnConcessional_checkBox->setObjectName("creditsOnConcessional_checkBox");
        creditsOnConcessional_checkBox->setGeometry(QRect(180, 420, 94, 24));
        creditsOnConsumer_checkBox = new QCheckBox(page_4);
        creditsOnConsumer_checkBox->setObjectName("creditsOnConsumer_checkBox");
        creditsOnConsumer_checkBox->setGeometry(QRect(20, 420, 149, 24));
        creditdsOnRealState_checkBox = new QCheckBox(page_4);
        creditdsOnRealState_checkBox->setObjectName("creditdsOnRealState_checkBox");
        creditdsOnRealState_checkBox->setGeometry(QRect(290, 420, 153, 24));
        showPossibleCredits_pushButton = new QPushButton(page_4);
        showPossibleCredits_pushButton->setObjectName("showPossibleCredits_pushButton");
        showPossibleCredits_pushButton->setGeometry(QRect(450, 420, 93, 29));
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        givenDeposits_tableView = new QTableView(page_5);
        givenDeposits_tableView->setObjectName("givenDeposits_tableView");
        givenDeposits_tableView->setGeometry(QRect(10, 10, 661, 401));
        givenDeposits_tableView->setSortingEnabled(true);
        closeGivenDeposits_pushButton = new QPushButton(page_5);
        closeGivenDeposits_pushButton->setObjectName("closeGivenDeposits_pushButton");
        closeGivenDeposits_pushButton->setGeometry(QRect(570, 420, 93, 29));
        showPossibleDeposits_pushButton = new QPushButton(page_5);
        showPossibleDeposits_pushButton->setObjectName("showPossibleDeposits_pushButton");
        showPossibleDeposits_pushButton->setGeometry(QRect(450, 420, 93, 29));
        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        payForCreditSum_Button = new QPushButton(page_6);
        payForCreditSum_Button->setObjectName("payForCreditSum_Button");
        payForCreditSum_Button->setGeometry(QRect(120, 90, 151, 45));
        payForCreditSum_Button->setFont(font1);
        payingCreditSum_lineEdit = new QLineEdit(page_6);
        payingCreditSum_lineEdit->setObjectName("payingCreditSum_lineEdit");
        payingCreditSum_lineEdit->setGeometry(QRect(140, 60, 113, 26));
        inviteToPayCreditSum_label = new QLabel(page_6);
        inviteToPayCreditSum_label->setObjectName("inviteToPayCreditSum_label");
        inviteToPayCreditSum_label->setGeometry(QRect(60, 20, 340, 28));
        inviteToPayCreditSum_label->setFont(font2);
        stackedWidget->addWidget(page_6);
        page_7 = new QWidget();
        page_7->setObjectName("page_7");
        groupBox = new QGroupBox(page_7);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 10, 261, 211));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 231, 205));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        undo_pushButton = new QPushButton(layoutWidget);
        undo_pushButton->setObjectName("undo_pushButton");

        horizontalLayout->addWidget(undo_pushButton);

        redo_pushButton = new QPushButton(layoutWidget);
        redo_pushButton->setObjectName("redo_pushButton");

        horizontalLayout->addWidget(redo_pushButton);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        changeLogin_label = new QLabel(layoutWidget);
        changeLogin_label->setObjectName("changeLogin_label");

        formLayout->setWidget(0, QFormLayout::LabelRole, changeLogin_label);

        changeLogin_lineEdit = new QLineEdit(layoutWidget);
        changeLogin_lineEdit->setObjectName("changeLogin_lineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, changeLogin_lineEdit);

        changePassword_label = new QLabel(layoutWidget);
        changePassword_label->setObjectName("changePassword_label");

        formLayout->setWidget(1, QFormLayout::LabelRole, changePassword_label);

        changePassword_lineEdit = new QLineEdit(layoutWidget);
        changePassword_lineEdit->setObjectName("changePassword_lineEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, changePassword_lineEdit);

        changeName_label = new QLabel(layoutWidget);
        changeName_label->setObjectName("changeName_label");

        formLayout->setWidget(2, QFormLayout::LabelRole, changeName_label);

        changeName_lineEdit = new QLineEdit(layoutWidget);
        changeName_lineEdit->setObjectName("changeName_lineEdit");

        formLayout->setWidget(2, QFormLayout::FieldRole, changeName_lineEdit);

        changeSurname_label = new QLabel(layoutWidget);
        changeSurname_label->setObjectName("changeSurname_label");

        formLayout->setWidget(3, QFormLayout::LabelRole, changeSurname_label);

        changeSurname_lineEdit = new QLineEdit(layoutWidget);
        changeSurname_lineEdit->setObjectName("changeSurname_lineEdit");

        formLayout->setWidget(3, QFormLayout::FieldRole, changeSurname_lineEdit);


        verticalLayout->addLayout(formLayout);


        verticalLayout_2->addLayout(verticalLayout);

        saveChanges_pushButton = new QPushButton(layoutWidget);
        saveChanges_pushButton->setObjectName("saveChanges_pushButton");

        verticalLayout_2->addWidget(saveChanges_pushButton);

        stackedWidget->addWidget(page_7);

        retranslateUi(ChangeMenu);
        QObject::connect(ExchCurrRate_buttonBox, &QDialogButtonBox::accepted, ChangeMenu, qOverload<>(&QDialog::accept));
        QObject::connect(ExchCurrRate_buttonBox, &QDialogButtonBox::rejected, ChangeMenu, qOverload<>(&QDialog::reject));
        QObject::connect(undo_pushButton, &QPushButton::clicked, changeLogin_lineEdit, qOverload<>(&QLineEdit::undo));
        QObject::connect(undo_pushButton, &QPushButton::clicked, changePassword_lineEdit, qOverload<>(&QLineEdit::undo));
        QObject::connect(undo_pushButton, &QPushButton::clicked, changeName_lineEdit, qOverload<>(&QLineEdit::undo));
        QObject::connect(undo_pushButton, &QPushButton::clicked, changeSurname_lineEdit, qOverload<>(&QLineEdit::undo));
        QObject::connect(redo_pushButton, &QPushButton::clicked, changeLogin_lineEdit, qOverload<>(&QLineEdit::redo));
        QObject::connect(redo_pushButton, &QPushButton::clicked, changePassword_lineEdit, qOverload<>(&QLineEdit::redo));
        QObject::connect(redo_pushButton, &QPushButton::clicked, changeName_lineEdit, qOverload<>(&QLineEdit::redo));
        QObject::connect(redo_pushButton, &QPushButton::clicked, changeSurname_lineEdit, qOverload<>(&QLineEdit::redo));

        stackedWidget->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(ChangeMenu);
    } // setupUi

    void retranslateUi(QDialog *ChangeMenu)
    {
        ChangeMenu->setWindowTitle(QCoreApplication::translate("ChangeMenu", "Dialog", nullptr));
        inviteToEnterNewExchRate_label->setText(QCoreApplication::translate("ChangeMenu", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\262\321\213\320\271 \320\272\321\203\321\200\321\201 \320\262\320\260\320\273\321\216\321\202:", nullptr));
        addToAccSum_Button->setText(QCoreApplication::translate("ChangeMenu", "\320\237\320\276\320\277\320\276\320\273\320\275\320\270\321\202\321\214", nullptr));
        inviteToAddAccSum_label->setText(QCoreApplication::translate("ChangeMenu", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\201\321\203\320\274\320\274\321\203 \320\277\320\276\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217:", nullptr));
        takeFromAccSum_Button->setText(QCoreApplication::translate("ChangeMenu", "\320\241\320\275\321\217\321\202\321\214", nullptr));
        inviteToTakeFromAccSum_label->setText(QCoreApplication::translate("ChangeMenu", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\201\321\203\320\274\320\274\321\203 \320\264\320\273\321\217 \321\201\320\275\321\217\321\202\320\270\321\217:", nullptr));
        closeGivenCredits_pushButton->setText(QCoreApplication::translate("ChangeMenu", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
        creditsOnConcessional_checkBox->setText(QCoreApplication::translate("ChangeMenu", "\320\233\321\214\320\263\320\276\321\202\320\275\321\213\320\265", nullptr));
        creditsOnConsumer_checkBox->setText(QCoreApplication::translate("ChangeMenu", "\320\237\320\276\321\202\321\200\320\265\320\261\320\270\321\202\320\265\320\273\321\214\321\201\320\272\320\270\320\265", nullptr));
        creditdsOnRealState_checkBox->setText(QCoreApplication::translate("ChangeMenu", "\320\235\320\260 \320\275\320\265\320\264\320\262\320\270\320\266\320\270\320\274\320\276\321\201\321\202\321\214", nullptr));
        showPossibleCredits_pushButton->setText(QCoreApplication::translate("ChangeMenu", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214", nullptr));
        closeGivenDeposits_pushButton->setText(QCoreApplication::translate("ChangeMenu", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
        showPossibleDeposits_pushButton->setText(QCoreApplication::translate("ChangeMenu", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214", nullptr));
        payForCreditSum_Button->setText(QCoreApplication::translate("ChangeMenu", "\320\236\320\277\320\273\320\260\321\202\320\270\321\202\321\214", nullptr));
        payingCreditSum_lineEdit->setText(QString());
        inviteToPayCreditSum_label->setText(QCoreApplication::translate("ChangeMenu", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\201\321\203\320\274\320\274\321\203 \320\264\320\273\321\217 \320\276\320\277\320\273\320\260\321\202\321\213:", nullptr));
        groupBox->setTitle(QString());
        undo_pushButton->setText(QCoreApplication::translate("ChangeMenu", "Undo", nullptr));
        redo_pushButton->setText(QCoreApplication::translate("ChangeMenu", "Redo", nullptr));
        changeLogin_label->setText(QCoreApplication::translate("ChangeMenu", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        changePassword_label->setText(QCoreApplication::translate("ChangeMenu", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        changeName_label->setText(QCoreApplication::translate("ChangeMenu", "\320\230\320\274\321\217", nullptr));
        changeSurname_label->setText(QCoreApplication::translate("ChangeMenu", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217", nullptr));
        saveChanges_pushButton->setText(QCoreApplication::translate("ChangeMenu", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeMenu: public Ui_ChangeMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEMENU_H
