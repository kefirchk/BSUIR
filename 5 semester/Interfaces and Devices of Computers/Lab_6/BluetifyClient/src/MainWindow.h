#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BluetoothMonitor.h"
#include "BTHClient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void serverIsOffSlot();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();
    void on_updateList_pushButton_clicked();
    void on_actionInformation_triggered();
    void on_devices_listWidget_doubleClicked(const QModelIndex &index);
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();
    void on_selectFile_pushButton_clicked();
    void on_sendFile_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    BluetoothMonitor bthMonitor;
    BTHClient client;

    RadioStruct radioStruct;
    QList<DeviceStruct> deviceStructs;
};
#endif // MAINWINDOW_H
