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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionDisconnect;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *serverInfo_label;
    QLabel *clientInfo_label;
    QListWidget *serverInfo_listWidget;
    QListWidget *clientInfo_listWidget;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QMenu *menuConnection;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(625, 363);
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QFont font;
        font.setFamily(QString::fromUtf8("Segoe Print"));
        actionQuit->setFont(font);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QString::fromUtf8("actionDisconnect"));
        actionDisconnect->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        serverInfo_label = new QLabel(centralwidget);
        serverInfo_label->setObjectName(QString::fromUtf8("serverInfo_label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Segoe Print"));
        font1.setPointSize(14);
        font1.setBold(false);
        serverInfo_label->setFont(font1);

        gridLayout->addWidget(serverInfo_label, 0, 0, 1, 1);

        clientInfo_label = new QLabel(centralwidget);
        clientInfo_label->setObjectName(QString::fromUtf8("clientInfo_label"));
        clientInfo_label->setFont(font1);

        gridLayout->addWidget(clientInfo_label, 0, 1, 1, 1);

        serverInfo_listWidget = new QListWidget(centralwidget);
        serverInfo_listWidget->setObjectName(QString::fromUtf8("serverInfo_listWidget"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Segoe UI"));
        font2.setPointSize(10);
        serverInfo_listWidget->setFont(font2);

        gridLayout->addWidget(serverInfo_listWidget, 1, 0, 1, 1);

        clientInfo_listWidget = new QListWidget(centralwidget);
        clientInfo_listWidget->setObjectName(QString::fromUtf8("clientInfo_listWidget"));
        clientInfo_listWidget->setFont(font2);

        gridLayout->addWidget(clientInfo_listWidget, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 625, 32));
        menubar->setFont(font);
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        menuConnection = new QMenu(menubar);
        menuConnection->setObjectName(QString::fromUtf8("menuConnection"));
        menuConnection->setFont(font);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());
        menubar->addAction(menuConnection->menuAction());
        menuMenu->addAction(actionQuit);
        menuConnection->addAction(actionDisconnect);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        actionDisconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        serverInfo_label->setText(QCoreApplication::translate("MainWindow", "Server information", nullptr));
        clientInfo_label->setText(QCoreApplication::translate("MainWindow", "Client information", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
        menuConnection->setTitle(QCoreApplication::translate("MainWindow", "Connection", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
