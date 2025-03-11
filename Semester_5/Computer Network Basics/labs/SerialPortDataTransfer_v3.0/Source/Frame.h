#ifndef FRAME_H
#define FRAME_H

#include <random>
#include "SerialPortFunctions.h"

#define DATA_SIZE 11 // номер студента по списку

class Frame
{
private:
    QString frame;
    QString flag;
    QString sourceAddress;
    QString destinationAddress;
    QString data;
    QString fcs;

public:
    Frame();
    Frame(QString data, QSerialPort& port);
    QString doBitStaffing();
    QString doDeBitStaffing(QString modifiedFrame);    
    char getBitSymbolForBitStaffing(QString flag);

    void encodeHammingCode();
    void decodeHammingCode();

    QString sendFrame(QSerialPort& port);
    void makeBitError();

    QString getFrame() const;
    QString getFlag() const;
    QString getSourceAddress() const;
    QString getDestinationAddress() const;
    QString getData() const;
    QString getFcs() const;

    void setFlag(const QString &newFlag);
    void setFrame(const QString &newFrame);
    void setSourceAddress(const QString &newSourceAddress);
    void setDestinationAddress(const QString &newDestinationAddress);
    void setData(const QString &newData);
    void setFcs(const QString &newFcs);

protected:
    void updateFrame();
};

#endif // FRAME_H
