#ifndef CSMA_CD_H
#define CSMA_CD_H

#include <windows.h>
#include <random>
#include <QString>
#include "MainWindow.h"
#include <QSerialPort>

#define MAX_ATTEMPT_NUMBER 10
#define COLLISION_WINDOW_TIME 40
#define JAM_SIGNAL_TIME 5

class CSMA_CD
{
public:
    QString sendBit(QSerialPort& port, QChar bit);
    bool isChannelBusy();
    bool isCollisionDetected();
    void waitForCollisionWindow();
    void randomDelay(unsigned int attemptNumber);
    void sendJamSignal();
private:
    Ui::MainWindow* mainWindowUi;
    QSerialPort port;
};

#endif // CSMA_CD_H
