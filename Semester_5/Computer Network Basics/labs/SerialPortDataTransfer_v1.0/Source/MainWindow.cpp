 #include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->input_textEdit->setPlaceholderText("Write a message...");

    connect(&port, &QSerialPort::readyRead, this, &MainWindow::receiveMessage);

    on_updatePortList_pushButton_clicked();
    if(!portList.empty())
    {
        bool isSetPort = false;
        for(auto portInfo : portList)
        {
            initPort(port, portInfo);
            if(port.open(QIODevice::ReadWrite))
            {
                isSetPort = true;
                break;
            }
        }
        if(isSetPort == false)
        {
            QMessageBox::critical(this, "Error", "Cannot find COM-port");
            this->errorFlag = true;
            return;
        }

        ui->COMPort_comboBox->setCurrentText(port.portName().sliced(3, port.portName().length() - 3));
        ui->status_textBrowser->append("Port speed: " + QString::number(port.baudRate()) + " bits/sec");
    }
    else
    {
        QMessageBox::critical(this, "Error", "COM ports are not available!");
        errorFlag = true;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionExit_triggered()
{
    this->close();
}


void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    // Если нажата клавиша Enter
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        sendMessage();
}


void MainWindow::sendMessage()
{
    port.setDataBits(QSerialPort::DataBits(ui->byteSize_spinBox->value()));

    QString newPortName = "COM" + ui->COMPort_comboBox->currentText();
    if(newPortName != this->port.portName())
    {
        if(canChangePort(portList, newPortName) == true)
        {
            port.close();
            this->port.setPortName(newPortName);
            if(!port.open(QIODevice::ReadWrite))
            {
                QMessageBox::critical(this, "Error", "Cannot change port");
                exit(1);
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "Port is not available");
            ui->COMPort_comboBox->setCurrentText(port.portName().sliced(3, port.portName().length() - 3));
            return;
        }
    }

    QString message = ui->input_textEdit->toPlainText(); // получаем текст из входной строки
    if(!message.isEmpty())         // если сообщение не пустое или не состоит из одних \n
    {
        for(auto symbol : message.mid(0, message.length() - 1))   // передаем сообщение посимвольно
            port.write(QString(symbol).toStdString().c_str());
        ui->status_textBrowser->append("Bytes sent: " + QString::number(message.toUtf8().size() - 1));
        ui->input_textEdit->clear();                     // очищаем строку для ввода сообщений
    }
}


void MainWindow::receiveMessage()
{
    QByteArray receivedBytes = port.readAll();
    ui->output_textBrowser->append(receivedBytes);
}


void MainWindow::on_updatePortList_pushButton_clicked()
{
    QString portNumber;
    portList.clear();
    portList = QSerialPortInfo::availablePorts();
    ui->COMPort_comboBox->clear();
    for(auto portInfo : portList)
    {
        portNumber = portInfo.portName().mid(3, portInfo.portName().length() - 3);
        qDebug() << portInfo.portName() << "was founded";
        if(ui->COMPort_comboBox->findText(portNumber) == -1)
            ui->COMPort_comboBox->addItem(portNumber);
    }
}

bool MainWindow::getErrorFlag() const
{
    return errorFlag;
}
