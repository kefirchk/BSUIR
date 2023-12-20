/********************************************************************************
** Form generated from reading UI file 'Calculator.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATOR_H
#define UI_CALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
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

class Ui_Calculator
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    QFrame *horizont_line_top;
    QLabel *invite_label;
    QLabel *label_4;
    QFrame *horizont_line_bottom;
    QPushButton *convert_pushButton;
    QLabel *label_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *last_upgrade_label;
    QLabel *last_update_date_label;
    QPushButton *close_window_pushButton;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox_left;
    QLineEdit *lineEdit_left;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox_right;
    QLineEdit *lineEdit_right;
    QWidget *page_4;
    QLabel *invite_label_2;
    QFrame *horizont_line_top_2;
    QLineEdit *creditSum_lineEdit;
    QLabel *creditSum_label;
    QLabel *term_label;
    QLineEdit *term_lineEdit;
    QLabel *procent_label;
    QLineEdit *procent_lineEdit;
    QPushButton *calc_credit_Button;
    QTableView *tableView;
    QPushButton *close_window_pushButton_2;
    QLabel *label;
    QLabel *label_3;
    QWidget *page;
    QLabel *invite_label_3;
    QFrame *horizont_line_top_3;
    QLabel *depositSum_label;
    QLineEdit *depositSum_lineEdit;
    QLabel *depositTerm_label;
    QLineEdit *depositTerm_lineEdit;
    QLabel *depositPercent_label;
    QLineEdit *depositPercent_lineEdit;
    QPushButton *calc_deposit_Button;
    QLabel *countingDepositRezults_label;
    QLabel *countDepositRez_label;
    QTableView *depositTableView;
    QPushButton *close_window_pushButton_3;

    void setupUi(QDialog *Calculator)
    {
        if (Calculator->objectName().isEmpty())
            Calculator->setObjectName("Calculator");
        Calculator->resize(607, 396);
        stackedWidget = new QStackedWidget(Calculator);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(11, 11, 601, 381));
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        horizont_line_top = new QFrame(page_3);
        horizont_line_top->setObjectName("horizont_line_top");
        horizont_line_top->setGeometry(QRect(11, 11, 572, 16));
        horizont_line_top->setFrameShape(QFrame::HLine);
        horizont_line_top->setFrameShadow(QFrame::Sunken);
        invite_label = new QLabel(page_3);
        invite_label->setObjectName("invite_label");
        invite_label->setGeometry(QRect(11, 21, 268, 37));
        QFont font;
        font.setFamilies({QString::fromUtf8("Tahoma")});
        font.setPointSize(18);
        font.setBold(true);
        invite_label->setFont(font);
        label_4 = new QLabel(page_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(355, 65, 184, 20));
        horizont_line_bottom = new QFrame(page_3);
        horizont_line_bottom->setObjectName("horizont_line_bottom");
        horizont_line_bottom->setGeometry(QRect(10, 130, 572, 16));
        horizont_line_bottom->setFrameShape(QFrame::HLine);
        horizont_line_bottom->setFrameShadow(QFrame::Sunken);
        convert_pushButton = new QPushButton(page_3);
        convert_pushButton->setObjectName("convert_pushButton");
        convert_pushButton->setGeometry(QRect(220, 80, 124, 29));
        label_2 = new QLabel(page_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(590, 21, 16, 20));
        layoutWidget = new QWidget(page_3);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 150, 451, 28));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        last_upgrade_label = new QLabel(layoutWidget);
        last_upgrade_label->setObjectName("last_upgrade_label");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Times New Roman")});
        font1.setPointSize(12);
        font1.setItalic(true);
        last_upgrade_label->setFont(font1);

        horizontalLayout_2->addWidget(last_upgrade_label);

        last_update_date_label = new QLabel(layoutWidget);
        last_update_date_label->setObjectName("last_update_date_label");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Times New Roman")});
        font2.setPointSize(14);
        font2.setBold(true);
        last_update_date_label->setFont(font2);

        horizontalLayout_2->addWidget(last_update_date_label);

        close_window_pushButton = new QPushButton(page_3);
        close_window_pushButton->setObjectName("close_window_pushButton");
        close_window_pushButton->setGeometry(QRect(460, 150, 93, 29));
        layoutWidget1 = new QWidget(page_3);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(10, 60, 204, 61));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        comboBox_left = new QComboBox(layoutWidget1);
        comboBox_left->addItem(QString());
        comboBox_left->addItem(QString());
        comboBox_left->addItem(QString());
        comboBox_left->addItem(QString());
        comboBox_left->setObjectName("comboBox_left");

        verticalLayout_2->addWidget(comboBox_left);

        lineEdit_left = new QLineEdit(layoutWidget1);
        lineEdit_left->setObjectName("lineEdit_left");

        verticalLayout_2->addWidget(lineEdit_left);

        layoutWidget2 = new QWidget(page_3);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(350, 60, 204, 61));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        comboBox_right = new QComboBox(layoutWidget2);
        comboBox_right->addItem(QString());
        comboBox_right->addItem(QString());
        comboBox_right->addItem(QString());
        comboBox_right->addItem(QString());
        comboBox_right->setObjectName("comboBox_right");

        verticalLayout->addWidget(comboBox_right);

        lineEdit_right = new QLineEdit(layoutWidget2);
        lineEdit_right->setObjectName("lineEdit_right");

        verticalLayout->addWidget(lineEdit_right);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        invite_label_2 = new QLabel(page_4);
        invite_label_2->setObjectName("invite_label_2");
        invite_label_2->setGeometry(QRect(10, 10, 268, 37));
        invite_label_2->setFont(font);
        horizont_line_top_2 = new QFrame(page_4);
        horizont_line_top_2->setObjectName("horizont_line_top_2");
        horizont_line_top_2->setGeometry(QRect(10, 0, 572, 16));
        horizont_line_top_2->setFrameShape(QFrame::HLine);
        horizont_line_top_2->setFrameShadow(QFrame::Sunken);
        creditSum_lineEdit = new QLineEdit(page_4);
        creditSum_lineEdit->setObjectName("creditSum_lineEdit");
        creditSum_lineEdit->setGeometry(QRect(20, 80, 221, 26));
        creditSum_label = new QLabel(page_4);
        creditSum_label->setObjectName("creditSum_label");
        creditSum_label->setGeometry(QRect(20, 60, 221, 20));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Verdana")});
        font3.setItalic(true);
        creditSum_label->setFont(font3);
        term_label = new QLabel(page_4);
        term_label->setObjectName("term_label");
        term_label->setGeometry(QRect(20, 120, 221, 20));
        term_label->setFont(font3);
        term_lineEdit = new QLineEdit(page_4);
        term_lineEdit->setObjectName("term_lineEdit");
        term_lineEdit->setGeometry(QRect(20, 140, 221, 26));
        procent_label = new QLabel(page_4);
        procent_label->setObjectName("procent_label");
        procent_label->setGeometry(QRect(20, 180, 221, 20));
        procent_label->setFont(font3);
        procent_lineEdit = new QLineEdit(page_4);
        procent_lineEdit->setObjectName("procent_lineEdit");
        procent_lineEdit->setGeometry(QRect(20, 200, 221, 26));
        calc_credit_Button = new QPushButton(page_4);
        calc_credit_Button->setObjectName("calc_credit_Button");
        calc_credit_Button->setGeometry(QRect(20, 250, 221, 61));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Verdana")});
        font4.setPointSize(20);
        calc_credit_Button->setFont(font4);
        tableView = new QTableView(page_4);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(260, 90, 301, 181));
        close_window_pushButton_2 = new QPushButton(page_4);
        close_window_pushButton_2->setObjectName("close_window_pushButton_2");
        close_window_pushButton_2->setGeometry(QRect(480, 300, 93, 29));
        label = new QLabel(page_4);
        label->setObjectName("label");
        label->setGeometry(QRect(310, 30, 240, 28));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Tahoma")});
        font5.setPointSize(14);
        label->setFont(font5);
        label_3 = new QLabel(page_4);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(300, 60, 240, 28));
        label_3->setFont(font5);
        stackedWidget->addWidget(page_4);
        page = new QWidget();
        page->setObjectName("page");
        invite_label_3 = new QLabel(page);
        invite_label_3->setObjectName("invite_label_3");
        invite_label_3->setGeometry(QRect(10, 10, 268, 37));
        invite_label_3->setFont(font);
        horizont_line_top_3 = new QFrame(page);
        horizont_line_top_3->setObjectName("horizont_line_top_3");
        horizont_line_top_3->setGeometry(QRect(10, 0, 572, 16));
        horizont_line_top_3->setFrameShape(QFrame::HLine);
        horizont_line_top_3->setFrameShadow(QFrame::Sunken);
        depositSum_label = new QLabel(page);
        depositSum_label->setObjectName("depositSum_label");
        depositSum_label->setGeometry(QRect(10, 60, 221, 20));
        depositSum_label->setFont(font3);
        depositSum_lineEdit = new QLineEdit(page);
        depositSum_lineEdit->setObjectName("depositSum_lineEdit");
        depositSum_lineEdit->setGeometry(QRect(10, 80, 221, 26));
        depositTerm_label = new QLabel(page);
        depositTerm_label->setObjectName("depositTerm_label");
        depositTerm_label->setGeometry(QRect(10, 120, 221, 20));
        depositTerm_label->setFont(font3);
        depositTerm_lineEdit = new QLineEdit(page);
        depositTerm_lineEdit->setObjectName("depositTerm_lineEdit");
        depositTerm_lineEdit->setGeometry(QRect(10, 140, 221, 26));
        depositPercent_label = new QLabel(page);
        depositPercent_label->setObjectName("depositPercent_label");
        depositPercent_label->setGeometry(QRect(10, 180, 221, 20));
        depositPercent_label->setFont(font3);
        depositPercent_lineEdit = new QLineEdit(page);
        depositPercent_lineEdit->setObjectName("depositPercent_lineEdit");
        depositPercent_lineEdit->setGeometry(QRect(10, 200, 221, 26));
        calc_deposit_Button = new QPushButton(page);
        calc_deposit_Button->setObjectName("calc_deposit_Button");
        calc_deposit_Button->setGeometry(QRect(10, 250, 221, 61));
        calc_deposit_Button->setFont(font4);
        countingDepositRezults_label = new QLabel(page);
        countingDepositRezults_label->setObjectName("countingDepositRezults_label");
        countingDepositRezults_label->setGeometry(QRect(310, 40, 240, 28));
        countingDepositRezults_label->setFont(font5);
        countDepositRez_label = new QLabel(page);
        countDepositRez_label->setObjectName("countDepositRez_label");
        countDepositRez_label->setGeometry(QRect(310, 60, 240, 28));
        countDepositRez_label->setFont(font5);
        depositTableView = new QTableView(page);
        depositTableView->setObjectName("depositTableView");
        depositTableView->setGeometry(QRect(260, 90, 301, 141));
        close_window_pushButton_3 = new QPushButton(page);
        close_window_pushButton_3->setObjectName("close_window_pushButton_3");
        close_window_pushButton_3->setGeometry(QRect(470, 280, 93, 29));
        stackedWidget->addWidget(page);

        retranslateUi(Calculator);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Calculator);
    } // setupUi

    void retranslateUi(QDialog *Calculator)
    {
        Calculator->setWindowTitle(QCoreApplication::translate("Calculator", "Dialog", nullptr));
        invite_label->setText(QCoreApplication::translate("Calculator", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\320\260\320\275\320\275\321\213\320\265:", nullptr));
        label_4->setText(QString());
        convert_pushButton->setText(QCoreApplication::translate("Calculator", "\320\232\320\276\320\275\320\262\320\265\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        label_2->setText(QString());
        last_upgrade_label->setText(QCoreApplication::translate("Calculator", "*\320\237\320\276\321\201\320\273\320\265\320\264\320\275\320\265\320\265 \320\276\320\261\320\275\320\276\320\262\320\273\320\265\320\275\320\270\320\265 \320\272\321\203\321\200\321\201\320\260 \320\262\320\260\320\273\321\216\321\202:", nullptr));
        last_update_date_label->setText(QCoreApplication::translate("Calculator", "00/00/0000", nullptr));
        close_window_pushButton->setText(QCoreApplication::translate("Calculator", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
        comboBox_left->setItemText(0, QCoreApplication::translate("Calculator", "\320\221\320\265\320\273\320\276\321\200\321\203\321\201\321\201\320\272\320\270\320\271 \321\200\321\203\320\261\320\273\321\214(BYN)", nullptr));
        comboBox_left->setItemText(1, QCoreApplication::translate("Calculator", "\320\240\320\276\321\201\321\201\320\270\320\271\321\201\320\272\320\270\320\271 \321\200\321\203\320\261\320\273\321\214(RUB)", nullptr));
        comboBox_left->setItemText(2, QCoreApplication::translate("Calculator", "\320\224\320\276\320\273\320\273\320\260\321\200 \320\241\320\250\320\220(USD)", nullptr));
        comboBox_left->setItemText(3, QCoreApplication::translate("Calculator", "\320\225\320\262\321\200\320\276(EUR)", nullptr));

        comboBox_right->setItemText(0, QCoreApplication::translate("Calculator", "\320\221\320\265\320\273\320\276\321\200\321\203\321\201\321\201\320\272\320\270\320\271 \321\200\321\203\320\261\320\273\321\214(BYN)", nullptr));
        comboBox_right->setItemText(1, QCoreApplication::translate("Calculator", "\320\240\320\276\321\201\321\201\320\270\320\271\321\201\320\272\320\270\320\271 \321\200\321\203\320\261\320\273\321\214(RUB)", nullptr));
        comboBox_right->setItemText(2, QCoreApplication::translate("Calculator", "\320\224\320\276\320\273\320\273\320\260\321\200 \320\241\320\250\320\220(USD)", nullptr));
        comboBox_right->setItemText(3, QCoreApplication::translate("Calculator", "\320\225\320\262\321\200\320\276(EUR)", nullptr));

        invite_label_2->setText(QCoreApplication::translate("Calculator", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\320\260\320\275\320\275\321\213\320\265:", nullptr));
        creditSum_label->setText(QCoreApplication::translate("Calculator", "\320\241\321\203\320\274\320\274\320\260 \320\272\321\200\320\265\320\264\320\270\321\202\320\260, BYN", nullptr));
        term_label->setText(QCoreApplication::translate("Calculator", "\320\241\321\200\320\276\320\272 \320\272\321\200\320\265\320\264\320\270\321\202\320\260, \320\262 \320\263\320\276\320\264\320\260\321\205", nullptr));
        procent_label->setText(QCoreApplication::translate("Calculator", "\320\241\321\202\320\260\320\262\320\272\320\260, %", nullptr));
        calc_credit_Button->setText(QCoreApplication::translate("Calculator", "\320\240\320\260\321\201\321\201\321\207\320\270\321\202\320\260\321\202\321\214", nullptr));
        close_window_pushButton_2->setText(QCoreApplication::translate("Calculator", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("Calculator", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\277\320\276\320\264\321\201\321\207\320\265\321\202\320\260", nullptr));
        label_3->setText(QCoreApplication::translate("Calculator", "<html><head/><body><p><span style=\" text-decoration: underline;\">\320\260\320\275\320\275\321\203\320\270\321\202\320\265\321\202\320\275\320\276\320\263\320\276 \320\277\320\273\320\260\321\202\320\265\320\266\320\260</span></p></body></html>", nullptr));
        invite_label_3->setText(QCoreApplication::translate("Calculator", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\320\260\320\275\320\275\321\213\320\265:", nullptr));
        depositSum_label->setText(QCoreApplication::translate("Calculator", "\320\241\321\203\320\274\320\274\320\260 \320\262\320\272\320\273\320\260\320\264\320\260, BYN", nullptr));
        depositTerm_label->setText(QCoreApplication::translate("Calculator", "\320\241\321\200\320\276\320\272 \320\262\320\272\320\273\320\260\320\264\320\260, \320\262 \320\263\320\276\320\264\320\260\321\205", nullptr));
        depositPercent_label->setText(QCoreApplication::translate("Calculator", "\320\241\321\202\320\260\320\262\320\272\320\260, %", nullptr));
        calc_deposit_Button->setText(QCoreApplication::translate("Calculator", "\320\240\320\260\321\201\321\201\321\207\320\270\321\202\320\260\321\202\321\214", nullptr));
        countingDepositRezults_label->setText(QCoreApplication::translate("Calculator", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\277\320\276\320\264\321\201\321\207\320\265\321\202\320\260", nullptr));
        countDepositRez_label->setText(QCoreApplication::translate("Calculator", "<html><head/><body><p>\320\262\320\262\320\265\320\264\320\265\320\275\320\275\320\276\320\263\320\276 \320\264\320\265\320\277\320\276\320\267\320\270\321\202\320\260</p></body></html>", nullptr));
        close_window_pushButton_3->setText(QCoreApplication::translate("Calculator", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Calculator: public Ui_Calculator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATOR_H
