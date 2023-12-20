#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&server, &BTHServer::showClientInfoSignal, this, &MainWindow::showClientInfoSlot);
    connect(&server, &BTHServer::clientIsOffSignal, this, &MainWindow::clientIsOffSlot);
    connect(this, &MainWindow::closeServerThreadSignal, &server, &BTHServer::close);

    radioStruct = bthMonitor.findRadio();

    ui->serverInfo_listWidget->addItem("Instance name: " + radioStruct.instanceName);
    ui->serverInfo_listWidget->addItem("Class: 0x" + radioStruct.deviceClass.rightJustified(8, '0'));
    ui->serverInfo_listWidget->addItem("Manufacturer: 0x" + radioStruct.manufacturer.rightJustified(8, '0'));

    QString address = radioStruct.address.toUpper();
    for (int i = 2; i < address.length(); i += 3)
        address.insert(i, ':');
    ui->serverInfo_listWidget->addItem("Address: "+ address);

    server.start();
}

MainWindow::~MainWindow()
{
    server.Disconnect();
    server.close();
    delete ui;
}

void MainWindow::showClientInfoSlot()
{
    ui->clientInfo_listWidget->clear();
    ui->clientInfo_listWidget->addItem("Instance name: " + server.clientInfo.instanceName);
    ui->clientInfo_listWidget->addItem("Class: 0x" + server.clientInfo.deviceClass.rightJustified(8, '0'));
    ui->clientInfo_listWidget->addItem("Manufacturer: 0x" + server.clientInfo.manufacturer);//.rightJustified(8, '0'));
    QString address = server.clientInfo.address.toUpper();
    for (int i = 2; i < address.length(); i += 3)
        address.insert(i, ':');
    ui->clientInfo_listWidget->addItem("Address: "+ address);
}


void MainWindow::on_actionDisconnect_triggered()
{
    ui->clientInfo_listWidget->clear();
    server.Disconnect();
}


void MainWindow::clientIsOffSlot()
{
    QMessageBox::warning(this, "Warning", "Client disabled");
    on_actionDisconnect_triggered();
}

