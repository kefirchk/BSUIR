#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&usbMonitor, &USBMonitor::usbConnectionSignal, this, &MainWindow::newUsbConnectionSlot);

    if(usbMonitor.getDeviceInfoSet() == NULL)
    {
        QMessageBox::critical(this, "Error", "Cannot get USB device set");
        exit(EXIT_FAILURE);
    }
    updateUSBList();
    usbMonitor.start();
}

MainWindow::~MainWindow()
{
    this->usbMonitor.setIsRunning(false);
    this->usbMonitor.wait();
    delete ui;
}


void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::newUsbConnectionSlot(int status)
{
    switch(status)
    {
    case DBT_DEVICEARRIVAL:
        QMessageBox::information(this, "Information", "New device detected");
        break;
    case DBT_DEVICEREMOVECOMPLETE:
        if(msgBoxLock == false)
            QMessageBox::warning(this, "Warning", "Device disconnected unsafely");
        break;
    case DBT_DEVICEQUERYREMOVE:
        QMessageBox::information(this, "Information", "Try to disconnect device safely");
        break;
    case DBT_DEVICEQUERYREMOVEFAILED:
        QMessageBox::warning(this, "Warning", "Device cannot be disconnected safely");
        break;
    }
    updateUSBList();
}


void MainWindow::updateUSBList()
{
    usbMonitor.getDeviceInfoSet();
    usbMonitor.getDeviceInfoSetSize();
    ui->listWidget->clear();

    for(size_t i = 0; i < usbMonitor.getDeviceInfoSetSize(); ++i)
    {
        QString data = usbMonitor.getData(i, SPDRP_DEVICEDESC);
        QListWidgetItem* listItem = new QListWidgetItem("USB Device №" + QString::number(i + 1) + " | " + data.toUtf8());
        listItem->setCheckState(Qt::Unchecked);
        ui->listWidget->addItem(listItem);
    }
}


void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    usbMonitor.getDeviceInfoSet();
    usbMonitor.getDeviceInfoSetSize();

    for(size_t i = 0; i < usbMonitor.getDeviceInfoSetSize(); ++i)
    {
        if(i == (size_t)index.row())
        {
            QDialog infoWindow;
            QVBoxLayout infoLayout(&infoWindow);
            QListWidget infoListWidget(&infoWindow);
            infoListWidget.setParent(&infoWindow);
            infoWindow.setWindowTitle("USB device №" + QString::number(i + 1) + " information");
            infoWindow.setFixedSize(400, 400);
            infoLayout.addWidget(&infoListWidget);
            for(size_t j = 0; j < AMOUNT_OF_PROPERTIES; ++j)
                infoListWidget.addItem(usbMonitor.property_names[j] + ": " + usbMonitor.getData(i, usbMonitor.property[j]));
            infoWindow.exec();
        }
    }
}


void MainWindow::on_actionDisconnect_triggered()
{
    QList<size_t> devicesToDisconnect;
    for(int i = 0; i < ui->listWidget->count(); ++i)
    {
        if(ui->listWidget->item(i)->checkState() == Qt::Checked)
        {
            qDebug() << "USB device №" + QString::number(i + 1) + " is chosen for disconnection safely";
            devicesToDisconnect.append(i);
        }
    }
    ui->statusbar->showMessage("Trying to disconnect devices safely...", 2000);
    for(size_t i = 0; i < devicesToDisconnect.size(); ++i)
    {
        msgBoxLock = true;
        if(usbMonitor.ejectDevice(devicesToDisconnect[i]) == CR_SUCCESS)
            QMessageBox::information(this, "Information", "The device " + QString::number(i + 1) + " disconnected safely");
        else
            QMessageBox::warning(this, "Warning", "The device " + QString::number(i + 1) + " cannot be safely disconnected");
        msgBoxLock = false;
    }
    updateUSBList();
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About USBMonitor", "💻 USBMonitor is an intelligent program designed to monitor and track all connected USB devices to your computer!\n\n"
    "Key features of USBMonitor:\n"
    "🔎 Full monitoring: The program tracks and records all connected and disconnected USB devices.\n"
    "📋 Detailed information: You'll receive comprehensive details about each connected USB device, including manufacturer, location information, hardwareid and more. This helps you easily track and identify devices.\n\n"
    "USBMonitor - your reliable assistant for USB device monitoring! 💪✨\n"
                                                 "                                                                 Developed by Alexey Klimovich, 08.11.2023");
}


void MainWindow::on_actionTechnical_Support_triggered()
{
    QMessageBox::about(this, "Contact", "USBMonitor developer can be reached at the following email:\n\n"
                                        "                               prostolex2004@mail.ru\n\n"
                                        "Or you can find me at:\n"
                                        "University: BSUIR\nFaculty: FCNS\nGroup: 150501");
}


void MainWindow::on_actionView_Help_triggered()
{
    QMessageBox::information(this, "Guide to USBMonitor", "1️. Device Detection: USB devices will automatically appear and disappear in the device list as they are connected or disconnected to your computer.\n"
                             "2️. Safe Disconnection: To safely disconnect a device, simply click on the checkbox next to the device in the list and then go to Connection -> Disconnect. This ensures a secure removal of the device.\n"
                             "3️. Menu Options: In the menu, you will find an option to exit the program when you're done using it.\n"
                                                          "4️. Help Tab: The Help tab provides a brief overview and reference information about the program.");
}

