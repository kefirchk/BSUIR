#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include "USBMonitor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void newUsbConnectionSlot(int status);
    void updateUSBList();

    void on_listWidget_doubleClicked(const QModelIndex &index);
    void on_actionDisconnect_triggered();
    void on_actionAbout_triggered();
    void on_actionTechnical_Support_triggered();
    void on_actionView_Help_triggered();

private:
    Ui::MainWindow *ui;
    bool msgBoxLock = false;
    USBMonitor usbMonitor;
};
#endif // MAINWINDOW_H
