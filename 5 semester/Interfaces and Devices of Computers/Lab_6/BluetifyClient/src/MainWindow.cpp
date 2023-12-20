#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->choosenFile_lineEdit->setAlignment(Qt::AlignCenter);
    ui->choosenFile_lineEdit->setPlaceholderText("<< Your file >>");
    ui->devices_listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(&this->client, &BTHClient::serverIsOffSignal, this, &MainWindow::serverIsOffSlot);

    client.radio_struct = bthMonitor.findRadio();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionQuit_triggered()
{
    this->close();
}


void MainWindow::on_updateList_pushButton_clicked()
{
    ui->devices_listWidget->clear();
    deviceStructs = bthMonitor.findDevices();
    for(int i = 0; i < deviceStructs.size(); ++i)
    {
        QListWidgetItem* listItem = new QListWidgetItem(QString::number(i + 1).leftJustified(3, ' ') + "| " + deviceStructs[i].instanceName.toUtf8());
        ui->devices_listWidget->addItem(listItem);
    }
    ui->statusbar->clearMessage();
}


void MainWindow::on_actionInformation_triggered()
{
    QDialog infoWindow;
    QVBoxLayout infoLayout(&infoWindow);
    QListWidget infoListWidget(&infoWindow);
    infoListWidget.setParent(&infoWindow);
    infoWindow.setWindowTitle("Radio information");
    infoWindow.setFixedSize(350, 200);
    infoWindow.setStyleSheet("font-size: 16px;");
    infoLayout.addWidget(&infoListWidget);

    radioStruct = bthMonitor.findRadio();
    infoListWidget.addItem("Instance name: " + radioStruct.instanceName);
    infoListWidget.addItem("Class: 0x" + radioStruct.deviceClass.rightJustified(8, '0'));
    infoListWidget.addItem("Manufacturer: 0x" + radioStruct.manufacturer.rightJustified(8, '0'));

    QString address = radioStruct.address.toUpper();
    for (int i = 2; i < address.length(); i += 3)
        address.insert(i, ':');
    infoListWidget.addItem("Address: "+ address);

    infoWindow.exec();
}


void MainWindow::on_devices_listWidget_doubleClicked(const QModelIndex &index)
{
    for(size_t i = 0; i < deviceStructs.size(); ++i)
    {
        if(i == (size_t)index.row())
        {
            QDialog infoWindow;
            QVBoxLayout infoLayout(&infoWindow);
            QListWidget infoListWidget(&infoWindow);
            infoListWidget.setParent(&infoWindow);
            infoWindow.setWindowTitle("Information about " + deviceStructs[i].instanceName.toUtf8());
            infoWindow.setFixedSize(350, 200);
            infoWindow.setStyleSheet("font-size: 16px;");
            infoLayout.addWidget(&infoListWidget);

            infoListWidget.addItem("Instance name: " + deviceStructs[i].instanceName);
            infoListWidget.addItem("Class: 0x" + deviceStructs[i].deviceClass.rightJustified(8, '0'));
            QString address = deviceStructs[i].address.toUpper();
            for (int i = 2; i < address.length(); i += 3)
                address.insert(i, ':');
            infoListWidget.addItem("Address: "+ address);

            QString statusIs = "";

            infoListWidget.addItem("Is connected: " + statusIs + (deviceStructs[i].isConnected ? "true" : "false"));
            infoListWidget.addItem("Is authenticated: " + statusIs + (deviceStructs[i].isAuthenticated ? "true" : "false"));
            infoListWidget.addItem("Is remembered: " + statusIs + (deviceStructs[i].isRemembered ? "true" : "false"));

            infoWindow.exec();
        }
    }
}


void MainWindow::on_actionConnect_triggered()
{
    bool ok;
    size_t i = (size_t)ui->devices_listWidget->currentIndex().row();
    if(i == -1)
    {
        QMessageBox::critical(this, "Error", "Device is not selected");
        return;
    }
    if(ui->devices_listWidget->selectionMode() == QAbstractItemView::NoSelection)
    {
        QMessageBox::warning(this, "Warning", "You cannot join this device because you are already connected to another device");
        return;
    }

    client.Socket();
    client.setServerAddress(deviceStructs[i].address.toULongLong(&ok, 16));
    if(client.Connect() == false)
    {
        QMessageBox::critical(this, "Error", "Connect error");
        return;
    }
    ui->devices_listWidget->setSelectionMode(QAbstractItemView::NoSelection);
    qDebug() << "Connected to the server";
    ui->statusbar->showMessage("Connected to the server");
    client.sendClientInfo();
    client.start();
}


void MainWindow::on_actionDisconnect_triggered()
{
    ui->statusbar->clearMessage();
    ui->devices_listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    send(client.getClientSocket(), "BREAK_CONNECTION", 20, 0);
    client.Disconnect();
    client.wait();
}


void MainWindow::on_selectFile_pushButton_clicked()
{
    // Открытие диалогового окна выбора файла
    QString fileName = QFileDialog::getOpenFileName(this, "Select file");

    // Проверка, был ли выбран файл
    if (!fileName.isEmpty()) {
        ui->choosenFile_lineEdit->setText(fileName);
        client.file_name = ui->choosenFile_lineEdit->text();
    }
}


void MainWindow::on_sendFile_pushButton_clicked()
{
    if(ui->devices_listWidget->selectionMode() == QAbstractItemView::SingleSelection)
    {
        QMessageBox::warning(this, "Warning", "No connection established");
        return;
    }
    if(ui->choosenFile_lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "No file selected for sending");
        return;
    }
    client.file_name = ui->choosenFile_lineEdit->text();
    client.setToSend(true);
}


void MainWindow::serverIsOffSlot()
{
    QMessageBox::critical(this, "Error", "Server is not available");
    on_actionDisconnect_triggered();
}


