#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "SerialPortFunctions.h"
#include "Frame.h"

#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool getErrorFlag() const;

private slots:
    void keyReleaseEvent(QKeyEvent *event) override;
    void sendMessage();
    void receiveMessage();
    void on_actionExit_triggered();
    void on_updatePortList_pushButton_clicked();
    void on_input_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    QSerialPort port;
    QList<QSerialPortInfo> portList;
    bool errorFlag = false;
};
#endif // MAINWINDOW_H
