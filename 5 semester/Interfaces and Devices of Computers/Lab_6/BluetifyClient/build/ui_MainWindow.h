/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionInformation;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *bthDeviceList_label;
    QLineEdit *choosenFile_lineEdit;
    QPushButton *sendFile_pushButton;
    QPushButton *selectFile_pushButton;
    QPushButton *updateList_pushButton;
    QListWidget *devices_listWidget;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QMenu *menuConnection;
    QMenu *menuAbout_radio;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(395, 299);
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("Segoe Print"));
        MainWindow->setFont(font);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QString::fromUtf8("actionDisconnect"));
        actionInformation = new QAction(MainWindow);
        actionInformation->setObjectName(QString::fromUtf8("actionInformation"));
        actionInformation->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        bthDeviceList_label = new QLabel(centralwidget);
        bthDeviceList_label->setObjectName(QString::fromUtf8("bthDeviceList_label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Segoe Print"));
        font1.setPointSize(14);
        bthDeviceList_label->setFont(font1);

        gridLayout->addWidget(bthDeviceList_label, 0, 0, 1, 1);

        choosenFile_lineEdit = new QLineEdit(centralwidget);
        choosenFile_lineEdit->setObjectName(QString::fromUtf8("choosenFile_lineEdit"));
        choosenFile_lineEdit->setFont(font);
        choosenFile_lineEdit->setReadOnly(true);
        choosenFile_lineEdit->setClearButtonEnabled(false);

        gridLayout->addWidget(choosenFile_lineEdit, 3, 1, 1, 1);

        sendFile_pushButton = new QPushButton(centralwidget);
        sendFile_pushButton->setObjectName(QString::fromUtf8("sendFile_pushButton"));
        sendFile_pushButton->setFont(font1);

        gridLayout->addWidget(sendFile_pushButton, 4, 1, 1, 1);

        selectFile_pushButton = new QPushButton(centralwidget);
        selectFile_pushButton->setObjectName(QString::fromUtf8("selectFile_pushButton"));
        selectFile_pushButton->setFont(font1);

        gridLayout->addWidget(selectFile_pushButton, 2, 1, 1, 1);

        updateList_pushButton = new QPushButton(centralwidget);
        updateList_pushButton->setObjectName(QString::fromUtf8("updateList_pushButton"));
        updateList_pushButton->setFont(font1);

        gridLayout->addWidget(updateList_pushButton, 1, 1, 1, 1);

        devices_listWidget = new QListWidget(centralwidget);
        devices_listWidget->setObjectName(QString::fromUtf8("devices_listWidget"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Segoe UI"));
        font2.setPointSize(10);
        devices_listWidget->setFont(font2);

        gridLayout->addWidget(devices_listWidget, 1, 0, 5, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 395, 26));
        menubar->setFont(font);
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        menuMenu->setFont(font);
        menuConnection = new QMenu(menubar);
        menuConnection->setObjectName(QString::fromUtf8("menuConnection"));
        menuConnection->setFont(font);
        menuAbout_radio = new QMenu(menubar);
        menuAbout_radio->setObjectName(QString::fromUtf8("menuAbout_radio"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());
        menubar->addAction(menuConnection->menuAction());
        menubar->addAction(menuAbout_radio->menuAction());
        menuMenu->addAction(actionQuit);
        menuConnection->addAction(actionConnect);
        menuConnection->addAction(actionDisconnect);
        menuAbout_radio->addAction(actionInformation);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        actionConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        actionDisconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        actionInformation->setText(QCoreApplication::translate("MainWindow", "Information", nullptr));
        bthDeviceList_label->setText(QCoreApplication::translate("MainWindow", "Bluetooth Device List", nullptr));
        sendFile_pushButton->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        selectFile_pushButton->setText(QCoreApplication::translate("MainWindow", "Select file", nullptr));
        updateList_pushButton->setText(QCoreApplication::translate("MainWindow", "Update list", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
        menuConnection->setTitle(QCoreApplication::translate("MainWindow", "Connection", nullptr));
        menuAbout_radio->setTitle(QCoreApplication::translate("MainWindow", "About radio", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
