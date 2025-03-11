#include "Frame.h"

void Frame::setFrame(const QString &newFrame)
{
    frame = newFrame;
    flag = frame.mid(0, 8);
    destinationAddress = frame.mid(8, 4);
    sourceAddress = frame.mid(12, 4);
    data = frame.mid(16, frame.length() - 20);
    fcs = frame.mid(frame.length() - 4);
}
void Frame::setFlag(const QString &newFlag) { flag = newFlag; updateFrame(); }
void Frame::setSourceAddress(const QString &newSourceAddress) { sourceAddress = newSourceAddress; updateFrame(); }
void Frame::setDestinationAddress(const QString &newDestinationAddress) { destinationAddress = newDestinationAddress; updateFrame(); }
void Frame::setData(const QString &newData) { data = newData; updateFrame(); }
void Frame::setFcs(const QString &newFcs) { fcs = newFcs; updateFrame(); }


QString Frame::getFrame() const { return frame; }
QString Frame::getFlag() const { return flag; }
QString Frame::getSourceAddress() const { return sourceAddress; }
QString Frame::getDestinationAddress() const { return destinationAddress; }
QString Frame::getData() const { return data; }
QString Frame::getFcs() const { return fcs; }


Frame::Frame()
{
    flag = toBinary(QString::number(DATA_SIZE), 8);
    sourceAddress = "0000";
    destinationAddress = "0000";
    fcs = "0000";
    data = "00000000000";
    updateFrame();
}

Frame::Frame(QString newData, QSerialPort& port)
{
    flag = toBinary(QString::number(DATA_SIZE), 8);
    sourceAddress = toBinary(port.portName().mid(3, port.portName().length() - 3), 4);
    destinationAddress = "0000";
    fcs = "0000";
    data = newData;
    updateFrame();
}

QString Frame::doBitStaffing()
{
    QString frameWithoutFlag = frame.mid(8, frame.length() - 8);
    int pos = frameWithoutFlag.indexOf(flag.mid(0, 7), 0);
    char bitSymbol = getBitSymbolForBitStaffing(flag);
    while (pos != -1) {
        frameWithoutFlag.insert(pos + 7, bitSymbol);
        pos = frameWithoutFlag.indexOf(flag.mid(0, 7), pos + 1);
    }
    return flag + frameWithoutFlag;
}

QString Frame::doDeBitStaffing(QString modifiedFrame)
{
    QString flag = modifiedFrame.mid(0, 8);
    int pos = modifiedFrame.indexOf(flag.mid(0, 7), 8);
    while (pos != -1)
    {
        modifiedFrame.remove(pos + 7, 1);
        pos = modifiedFrame.indexOf(flag.mid(0, 7), pos + 1);
    }
    return modifiedFrame;
}

char Frame::getBitSymbolForBitStaffing(QString flag)
{
    return flag[7] == '1' ? '0' : '1';
}

void Frame::updateFrame()
{
    frame = flag + destinationAddress + sourceAddress + data + fcs;
}

void Frame::encodeHammingCode()
{
    // Вставка контрольных битов.
    QString encodedData = data.leftJustified(DATA_SIZE, '?');
    int amountOfControlBits = 0;
    for(int i = 1; i <= encodedData.size(); i *= 2, ++amountOfControlBits)
        encodedData.insert(i - 1, '0');

    // Вычисляем значение каждого контрольно бита.
    QList<char> controlBits(amountOfControlBits);
    for(int i = 0, step = 1; i < controlBits.length(); ++i, step *= 2)
    {
        int counterOfOne = 0;
        for(int j = step - 1; j < encodedData.size(); j += 2 * step)
            // Если очередная последовательность, которая контролируется данным контрольным битом, имеет единицы
            counterOfOne += encodedData.mid(j, step).count('1');
        controlBits[i] = counterOfOne % 2 == 0 ? '0' : '1';
    }

    // Высчитываем FCS и обновляем поле fcs.
    fcs.clear();
    for(int i = 0; i < controlBits.size(); ++i)
        fcs.append(controlBits[i]);

    updateFrame();
}


void Frame::decodeHammingCode()
{
    Frame newFrame;
    newFrame.setData(data);

    // Заново кодируем Data c искаженным битом
    newFrame.encodeHammingCode();

    QString unmatchedControlBits = "";
    for(int i = 0; i < fcs.size(); ++i)
    {
        if(newFrame.getFcs()[i] != fcs[i])
            unmatchedControlBits.append('1');
        else
            unmatchedControlBits.append('0');
    }
    this->setFcs(unmatchedControlBits);

    // Получаем индекс искаженного бита
    unsigned long indexOfBadBit = 0;
    for(int i = 0, bitValue = 1; i < unmatchedControlBits.size(); ++i, bitValue *= 2)
        indexOfBadBit += unmatchedControlBits[i] == '1' ? bitValue : 0;

    auto isPowerOfTwo = [](int n) {
        return (n > 0) && ((n & (n - 1)) == 0);
    };

    // Исправляем ошибку в Data
    if(indexOfBadBit > 0 && !isPowerOfTwo(indexOfBadBit))
    {
        // Получаем вычисленное значение FCS
        unsigned long indexOfBadBit2 = indexOfBadBit;
        for(unsigned long i = 8, index = 3; i >= 0; i /= 2, --index)
        {
            if(indexOfBadBit > i)
            {
                indexOfBadBit2 -= index + 1;
                break;
            }
        }
        this->setFcs(QString::number(indexOfBadBit2, 2).rightJustified(4, '0'));


        QString encodedData = data;
        unsigned long controlBitIndex = 1;
        for(; controlBitIndex <= encodedData.size(); controlBitIndex *= 2)
            encodedData.insert(controlBitIndex - 1, '0');

        encodedData[indexOfBadBit - 1] = encodedData[indexOfBadBit - 1] == '1' ? '0' : '1';

        for(; controlBitIndex > 0; controlBitIndex /= 2)
            encodedData.remove(controlBitIndex - 1, 1);

        data = encodedData;
    }
    data = data.leftJustified(DATA_SIZE, '?');

    updateFrame();
}


QString Frame::sendFrame(QSerialPort& port, QString& collisionStatus, Ui::MainWindow* mainWindowUi)
{
    this->encodeHammingCode();
    this->setData(data.leftJustified(DATA_SIZE, '?'));

    // Искажение бита передаваемой информации с вероятностью 70%
    this->makeBitError();

    this->setFrame(this->doBitStaffing());

    collisionStatus = "";
    mainWindowUi->status_textBrowser->append("");
    // Передаем кадр посимвольно
    for(auto bit : frame)
    {
        collisionStatus += CSMA_CD::sendBit(port, bit);
        mainWindowUi->status_textBrowser->insertPlainText(collisionStatus);
    }
    return frame;
}

void Frame::makeBitError()
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dis(0, 100);
    int random_number = dis(gen);

    //srand(time(NULL));
    if(random_number <= 70)//(rand() % (100 - 0 + 1) + 0) <= 70) // вероятность искажения Data составляет 70%
    {
        qDebug() << "-------BEGIN GENERATE BAD BIT--------";

        // Конец поля Data
        unsigned long indexOfDataEnd = frame.indexOf('?') - 1;
        if(indexOfDataEnd == -2UL)
            indexOfDataEnd = frame.size() - fcs.size() - 1;

        std::pair<unsigned long, unsigned long> dataRange = {16, indexOfDataEnd};

        // Инициализируем генератор случайных чисел
        //srand(time(NULL));

        uniform_int_distribution<unsigned long> ind_dis(dataRange.first, dataRange.second);
        unsigned long randomIndex = ind_dis(gen);
        // Генерируем случайный индекс бита поля Data в диапазоне от 17 до indexOfDataEnd
        //unsigned long randomIndex = rand() % (dataRange.second - dataRange.first + 1) + dataRange.first;

        qDebug() << "Bad bit index:" << randomIndex;

        frame[randomIndex] = frame[randomIndex] == '1' ? '0' : '1';

        qDebug() << "-------END GENERATE BAD BIT--------";
    }
}



