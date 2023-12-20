#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BluetoothMonitor.h"
#include "BTHServer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void closeServerThreadSignal();

private slots:
    void showClientInfoSlot();
    void on_actionDisconnect_triggered();
    void clientIsOffSlot();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    Ui::MainWindow *ui;
    BluetoothMonitor bthMonitor;

    RadioStruct radioStruct;
    BTHServer server;
};
#endif // MAINWINDOW_H
