#ifndef BTHCLIENT_H
#define BTHCLIENT_H

#include "SystemLibs.h"
#include "Config.h"
#include "BluetoothMonitor.h"

class BTHClient : public QThread
{
    Q_OBJECT

signals:
    void serverIsOffSignal();

private:
    WSADATA wsd;
    SOCKET client_socket;
    SOCKADDR_BTH server_struct;
    bool is_running;
    bool to_send = false;

public:
    RadioStruct radio_struct;
    QString file_name;

    explicit BTHClient(QObject* parent = nullptr);
    ~BTHClient();

    void run() override;

    bool Socket();
    bool Connect();
    void Disconnect();
    void setServerAddress(const BTH_ADDR& address);
    SOCKET getClientSocket() const;
    void sendClientInfo();
    void setToSend(bool value);
};

#endif // BTHCLIENT_H
