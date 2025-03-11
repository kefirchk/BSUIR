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
    if(!message.isEmpty())                               // если сообщение не пустое
    {
        QString messageLength = QString::number(message.toUtf8().size());
        unsigned long countOfFrames = message.length() / STUDENT_LIST_NUMBER;
        unsigned long position = 0;
        for(size_t i = 0; i < countOfFrames; ++i)
        {
            Frame frame(message.mid(position, STUDENT_LIST_NUMBER), port);
            QString modifiedFrame = frame.doBitStaffing();

            // Передаем кадр посимвольно
            for(auto bit : modifiedFrame)
                port.write(QString(bit).toStdString().c_str());
            position += STUDENT_LIST_NUMBER;
        }
        // Если сообщение по длине меньше STUDENT_LIST_NUMBER, то есть меньше одного кадра
        if(messageLength.toInt() % STUDENT_LIST_NUMBER != 0)
        {
            QString lastMessage = message.mid(position);
            while(lastMessage.length() < STUDENT_LIST_NUMBER)
                lastMessage = lastMessage + '?';
            Frame frame(lastMessage, port);
            QString modifiedFrame = frame.doBitStaffing();
            messageLength = QString::number(modifiedFrame.length());

            // Передаем кадр посимвольно
            for(auto bit : modifiedFrame)
                port.write(QString(bit).toStdString().c_str());
        }
        ui->status_textBrowser->append("Bytes sent: " + messageLength);
        ui->input_textEdit->clear();     // очищаем строку для ввода сообщений
    }
}


void MainWindow::receiveMessage()
{
    QByteArray receivedBytes = port.readAll();
    QString receivedData = "";
    Frame frame("", port);
    QStringList listOfFrames = QString(receivedBytes).split(QRegularExpression(frame.getFlag()));
    char bitSymbol = frame.getBitSymbolForBitStaffing(frame.getFlag());
    QString modifiedFlag = frame.getFlag().mid(0, 7) + bitSymbol;// + frame.getFlag().mid(7, 1);
    QString highlightFlag = modifiedFlag.mid(0, 7) + "<font color=\"#FF0000\">" + modifiedFlag[7] + "</font>" + modifiedFlag[8];
    for(int i = 1; i < listOfFrames.length(); ++i)
    {
        listOfFrames[i].replace(modifiedFlag, highlightFlag);
        ui->status_textBrowser->append(frame.getFlag() + listOfFrames[i]);
        listOfFrames[i].replace(highlightFlag, modifiedFlag);
        frame.setFrame(frame.doDeBitStaffing(frame.getFlag() + listOfFrames[i]));
        receivedData += frame.getData().remove('?');
    }
    ui->output_textBrowser->append(receivedData);
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


void MainWindow::on_input_textEdit_textChanged()
{
    QString text = ui->input_textEdit->toPlainText();
    text.remove(QRegularExpression("[^01]"));
    if(ui->input_textEdit->toPlainText() != text)
    {
        ui->input_textEdit->blockSignals(true);
        ui->input_textEdit->setText(text);
        ui->input_textEdit->moveCursor(QTextCursor::EndOfBlock);
        ui->input_textEdit->blockSignals(false);
    }
}

