/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *input_label;
    QLabel *output_label;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *input_textEdit;
    QTextBrowser *output_textBrowser;
    QVBoxLayout *verticalLayout;
    QLabel *status_label;
    QTextBrowser *status_textBrowser;
    QPushButton *updatePortList_pushButton;
    QFormLayout *formLayout;
    QLabel *ChooseSerialPort_label;
    QComboBox *COMPort_comboBox;
    QLabel *ByteSize_label;
    QSpinBox *byteSize_spinBox;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(630, 360);
        MainWindow->setMaximumSize(QSize(16777215, 360));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        input_label = new QLabel(centralwidget);
        input_label->setObjectName(QString::fromUtf8("input_label"));

        horizontalLayout->addWidget(input_label);

        output_label = new QLabel(centralwidget);
        output_label->setObjectName(QString::fromUtf8("output_label"));

        horizontalLayout->addWidget(output_label);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        input_textEdit = new QTextEdit(centralwidget);
        input_textEdit->setObjectName(QString::fromUtf8("input_textEdit"));

        horizontalLayout_2->addWidget(input_textEdit);

        output_textBrowser = new QTextBrowser(centralwidget);
        output_textBrowser->setObjectName(QString::fromUtf8("output_textBrowser"));

        horizontalLayout_2->addWidget(output_textBrowser);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        status_label = new QLabel(centralwidget);
        status_label->setObjectName(QString::fromUtf8("status_label"));

        verticalLayout->addWidget(status_label);

        status_textBrowser = new QTextBrowser(centralwidget);
        status_textBrowser->setObjectName(QString::fromUtf8("status_textBrowser"));

        verticalLayout->addWidget(status_textBrowser);

        updatePortList_pushButton = new QPushButton(centralwidget);
        updatePortList_pushButton->setObjectName(QString::fromUtf8("updatePortList_pushButton"));

        verticalLayout->addWidget(updatePortList_pushButton);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        ChooseSerialPort_label = new QLabel(centralwidget);
        ChooseSerialPort_label->setObjectName(QString::fromUtf8("ChooseSerialPort_label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, ChooseSerialPort_label);

        COMPort_comboBox = new QComboBox(centralwidget);
        COMPort_comboBox->setObjectName(QString::fromUtf8("COMPort_comboBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, COMPort_comboBox);

        ByteSize_label = new QLabel(centralwidget);
        ByteSize_label->setObjectName(QString::fromUtf8("ByteSize_label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, ByteSize_label);

        byteSize_spinBox = new QSpinBox(centralwidget);
        byteSize_spinBox->setObjectName(QString::fromUtf8("byteSize_spinBox"));
        byteSize_spinBox->setMinimum(5);
        byteSize_spinBox->setMaximum(8);

        formLayout->setWidget(1, QFormLayout::FieldRole, byteSize_spinBox);


        verticalLayout->addLayout(formLayout);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 630, 21));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        input_label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:700;\">INPUT</span></p></body></html>", nullptr));
        output_label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:700;\">OUTPUT</span></p></body></html>", nullptr));
        status_label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:700;\">STATUS</span></p></body></html>", nullptr));
        updatePortList_pushButton->setText(QCoreApplication::translate("MainWindow", "Update port list", nullptr));
        ChooseSerialPort_label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">COM-port number:</span></p></body></html>", nullptr));
        COMPort_comboBox->setCurrentText(QString());
        ByteSize_label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">Byte size (bits):</span></p></body></html>", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
