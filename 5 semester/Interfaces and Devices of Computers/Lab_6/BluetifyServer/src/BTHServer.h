#ifndef BTHSERVER_H
#define BTHSERVER_H

#include "SystemLibs.h"
#include "Config.h"
#include "BluetoothMonitor.h"

class BTHServer : public QThread
{
    Q_OBJECT

signals:
    void showClientInfoSignal();
    void clientIsOffSignal();

private:
    WSADATA wsd;
    SOCKET server_socket;
    SOCKADDR_BTH server_struct;
    SOCKET client_socket;
    bool is_running;
    bool to_recv;

public:
    RadioStruct clientInfo;

    explicit BTHServer(QObject* parent = nullptr);
    ~BTHServer();

    void run() override;

    void getClientInfo(SOCKET client_socket);
    bool Bind();
    bool Listen();
    SOCKET Accept();
    void Disconnect();
    void close();
    SOCKET getServerSocket() const;
    void setIsRunning(bool value);
};

#endif // BTHSERVER_H
