 #include "MainWindow.h"
#include "Frame.h"

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

bool MainWindow::tryToChangePort(QString newPortName)
{
    if(newPortName != this->port.portName())
    {
        if(canChangePort(portList, newPortName) == true)
        {
            port.close();
            this->port.setPortName(newPortName);
            if(!port.open(QIODevice::ReadWrite))
            {
                QMessageBox::critical(this, "Error", "Cannot change port");
                return false;
            }
            return true;
        }
        else
        {
            QMessageBox::critical(this, "Error", "Port is not available");
            ui->COMPort_comboBox->setCurrentText(port.portName().sliced(3, port.portName().length() - 3));
            return false;
        }
    }
    return true;
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


void MainWindow::sendMessage()
{
    port.setDataBits(QSerialPort::DataBits(ui->byteSize_spinBox->value()));
    if(tryToChangePort("COM" + ui->COMPort_comboBox->currentText()) == false)
        return;

    QString message = ui->input_textEdit->toPlainText(); // получаем текст из входной строки
    if(!message.isEmpty())                               // если сообщение не пустое
    {
        unsigned long bytesSent = 0;
        unsigned long countOfFrames = message.length() / DATA_SIZE;
        unsigned long position = 0;
        QString collisionStatus, modifiedFrame;
        for(size_t i = 0; i < countOfFrames; ++i)
        {
            Frame frame(message.mid(position, DATA_SIZE), port);
            modifiedFrame = frame.sendFrame(port, collisionStatus, ui);
            position += DATA_SIZE;
            bytesSent += collisionStatus.size();
        }
        // Если сообщение по длине меньше DATA_SIZE, то есть меньше одного кадра
        if(message.size() % DATA_SIZE != 0)
        {
            Frame frame(message.mid(position).leftJustified(DATA_SIZE, '?') , port);            
            modifiedFrame = frame.sendFrame(port, collisionStatus, ui);
            bytesSent += collisionStatus.size();
        }
        ui->status_textBrowser->append("Bytes sent: " + QString::number(bytesSent));
        ui->input_textEdit->clear();     // очищаем строку для ввода сообщений
    }
}


void MainWindow::receiveMessage()
{
    qDebug() << "\n-------------RECEIVE MESSAGE---------------";
    QString receivedData = "";
    Frame frame("", port);
    QStringList listOfFrames = QString(port.readAll()).split(frame.getFlag());
    listOfFrames.remove(0);

    QString modifiedFlag = frame.getFlag().mid(0, 7) + frame.getBitSymbolForBitStaffing(frame.getFlag());
    QString highlightFlag = modifiedFlag.mid(0, 7) + "<font color=\"#FF0000\">" + modifiedFlag[7] + "</font>";
    for(int i = 0; i < listOfFrames.length(); ++i)
    {
        // Покрасить все биты, которые появились в рез-те бит-стаффинга
        listOfFrames[i].replace(modifiedFlag, highlightFlag);

        // Запоминаем кадр без FCS
        QString receivedFrame = frame.getFlag() + listOfFrames[i].mid(0, listOfFrames[i].length() - 4) + " ";// + listOfFrames[i].mid(listOfFrames[i].length() - 4);

        // Отменить покраску битов, появившихся в рез-те бит-стаффинга
        listOfFrames[i].replace(highlightFlag, modifiedFlag);

        // Обновляем кадр
        frame.setFrame(frame.getFlag() + listOfFrames[i]);

        // Делаем обратную процедуру бит-стаффингу
        frame.setFrame(frame.doDeBitStaffing(frame.getFrame()));

        // Расшифровываем код Хэмминга в поле Data и исправляем ошибку, если она есть
        frame.decodeHammingCode();

        // Добавляем чистые данные в конечный массив данных
        receivedData += frame.getData().remove('?');
        ui->status_textBrowser->append(receivedFrame + frame.getFcs());
    }

    ui->output_textBrowser->append(receivedData);
}


