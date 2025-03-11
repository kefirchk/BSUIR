#include "CSMA_CD.h"

QString CSMA_CD::sendBit(QSerialPort& port, QChar bit)
{
    QString collisionStatus = "";
    unsigned int attemptNumber = 0;
    while (true)
    {
        if(!this->isChannelBusy())
        {
            port.write(QString(bit).toStdString().c_str());
            waitForCollisionWindow();
            if(!this->isCollisionDetected())
            {
                collisionStatus += '-';
                break;
            }
            else
            {
                collisionStatus += '+';
                //sendJamSignal();
                //waitForCollisionWindow();
                ++attemptNumber;
                if(attemptNumber > MAX_ATTEMPT_NUMBER)
                {
                    collisionStatus = "Error: bit collision";
                    break;
                } else {
                    randomDelay(attemptNumber);
                }
            }
        }
    }
    return collisionStatus + " ";
}

bool CSMA_CD::isChannelBusy()
{
    return rand() % 10 < 7 ? true : false;
}

bool CSMA_CD::isCollisionDetected()
{
    return rand() % 10 < 3 ? true : false;
}

void CSMA_CD::waitForCollisionWindow()
{
    Sleep(COLLISION_WINDOW_TIME);
}

void CSMA_CD::randomDelay(unsigned int attemptNumber)
{
    unsigned int power = attemptNumber < MAX_ATTEMPT_NUMBER ? attemptNumber : MAX_ATTEMPT_NUMBER;
    unsigned int delay = rand() % (unsigned int)(pow(2, power) + 1);
    Sleep(delay);
}

void CSMA_CD::sendJamSignal()
{
    Sleep(JAM_SIGNAL_TIME);
}
