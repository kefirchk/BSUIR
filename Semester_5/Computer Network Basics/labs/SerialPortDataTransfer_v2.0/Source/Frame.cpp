#include "Frame.h"

void Frame::setFrame(const QString &newFrame)
{
    frame = newFrame;
    flag = frame.mid(0, 8);
    destinationAddress = frame.mid(8, 4);
    sourceAddress = frame.mid(12, 4);
    data = frame.mid(16, 11);
    fcs = frame.mid(27, 1);
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
    flag = toBinary(QString::number(STUDENT_LIST_NUMBER), 8);
    sourceAddress = "0000";
    destinationAddress = "0000";
    fcs = "0";
    data = "00000000000";
    updateFrame();
}


Frame::Frame(QString newData, QSerialPort& port)
{
    flag = toBinary(QString::number(STUDENT_LIST_NUMBER), 8);
    sourceAddress = toBinary(port.portName().mid(3, port.portName().length() - 3), 4);
    destinationAddress = "0000";
    fcs = "0";
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
    while (pos != -1) {
        modifiedFrame.remove(pos + 7, 1);
        pos = modifiedFrame.indexOf(flag.mid(0, 7), pos + 1);
    }
    return modifiedFrame;
}

char Frame::getBitSymbolForBitStaffing(QString flag)
{
    char bitSymbol;
    if((flag[6] == '1' && flag[7] == '1')
        || (flag[6] == '0' && flag[7] == '1'))
    {
        bitSymbol = '0';
    }
    else
        bitSymbol = '1';
    return bitSymbol;
}


void Frame::updateFrame()
{
    frame = flag + destinationAddress + sourceAddress + data + fcs;
}
