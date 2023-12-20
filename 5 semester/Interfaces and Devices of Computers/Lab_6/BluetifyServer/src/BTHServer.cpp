#include "BTHServer.h"
#include <QtMultimedia>
#include <QMediaPlayer>

BTHServer::BTHServer(QObject *parent) : QThread(parent)
{
    is_running = false;
    to_recv = false;

    if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
        qDebug() << "Error: failed to initialize Winsock";
        exit(EXIT_FAILURE);
    }

    // Создание сокета для сервера
    this->server_socket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if (server_socket == INVALID_SOCKET) {
        qDebug() << "Error: socket() failed";
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    this->server_struct = {0};
    server_struct.addressFamily = AF_BTH;
    server_struct.serviceClassId = RFCOMM_PROTOCOL_UUID; // Уникальный идентификатор сервиса
    server_struct.port = CHANNEL;

    this->Bind();
    this->Listen();

    qDebug() << "Server socket created and bound to port " << server_struct.port;
}

BTHServer::~BTHServer()
{
    // Закрытие сокета
    closesocket(server_socket);

    // Прекращение использования служб WinSock
    WSACleanup();
}

void BTHServer::run()
{
    is_running = true;
    to_recv = true;
    while(is_running)
    {
        client_socket = this->Accept();
        getClientInfo(client_socket);

        while(to_recv)
        {
            qDebug() << "---{RECV}---";
            char cmd[STR_SIZE] = "";
            recv(client_socket, cmd, STR_SIZE, 0);

            qDebug() << "cmd: " << cmd;

            if(QString(cmd).startsWith("SEND_FILE"))
            {
                remove(FILE_TO_RECV);
                std::ofstream file(FILE_TO_RECV, std::ios::out | std::ios::binary | std::ios::trunc);
                int bytesReceived;
                char buffer[BUFFER_SIZE] = "";

                while ((bytesReceived = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0)
                {
                    if(file.is_open() == false)
                    {
                        file.open(FILE_TO_RECV);
                    }

                    qDebug() << "Receiving " << bytesReceived << " bytes...";
                    qDebug() << "------------------------------------------";
                    qDebug() << buffer;
                    qDebug() << "------------------------------------------";


                    if(QString(buffer).startsWith("EOF"))
                    {
                        break;
                    }
                    file.write(buffer, bytesReceived);
                }
                file.close();
                qDebug() << "File is received successfully";

                // Создание экземпляра QMediaPlayer
                QMediaPlayer *player = new QMediaPlayer;

                // Установка пути к аудиофайлу
                QString audioFile = FILE_TO_RECV;
                player->setMedia(QUrl::fromLocalFile(audioFile));

                // Воспроизведение аудиофайла
                player->play();


            }
            if(QString(cmd).startsWith("BREAK_CONNECTION"))
            {
                emit clientIsOffSignal();
                to_recv = false;
            }
        }
    }
}

void BTHServer::getClientInfo(SOCKET client_socket)
{
    char clientBuffer[BUFFER_SIZE] = "";
    int bytesRead = 0;
    bytesRead += recv(client_socket, clientBuffer, BUFFER_SIZE, 0);
    clientInfo.deviceClass = clientBuffer;
    qDebug() << "Class: " << clientBuffer;
    strcpy_s(clientBuffer, "");
    bytesRead += recv(client_socket, clientBuffer, BUFFER_SIZE, 0);
    clientInfo.address = clientBuffer;
    qDebug() << "Address: " << clientBuffer;
    strcpy_s(clientBuffer, "");
    bytesRead += recv(client_socket, clientBuffer, BUFFER_SIZE, 0);
    clientInfo.instanceName = clientBuffer;
    qDebug() << "Name: " << clientBuffer;
    strcpy_s(clientBuffer, "");
    bytesRead += recv(client_socket, clientBuffer, BUFFER_SIZE, 0);
    clientInfo.manufacturer = QString(clientBuffer).rightJustified(8, '0');
    qDebug() << "Manufacturer: " << clientBuffer;
    strcpy_s(clientBuffer, "");


    qDebug() << "Byted client info: " << bytesRead;
    if (bytesRead > 0)
    {
        emit showClientInfoSignal();
    }
}

bool BTHServer::Bind()
{
    // Привязка сокета к адресу
    if(::bind(server_socket, reinterpret_cast<sockaddr*>(&server_struct), sizeof(server_struct)) == SOCKET_ERROR)
    {
        qDebug() << "Error: bind() failed";
        closesocket(server_socket);
        WSACleanup();
        return false;
    }
    return true;
}

bool BTHServer::Listen()
{
    // Ожидание подключения клиента
    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
        qDebug() << "Error: listen() failed";
        closesocket(server_socket);
        WSACleanup();
        return false;
    }
    return true;
}

SOCKET BTHServer::Accept()
{
    qDebug() << "Waiting for client connection...";

    SOCKADDR_BTH client_struct = { 0 };
    int client_addr_size = sizeof(client_struct);

    // Принятие подключения от клиента
    this->client_socket = accept(server_socket, reinterpret_cast<sockaddr*>(&client_struct), &client_addr_size);
    if (client_socket == INVALID_SOCKET) {
        qDebug() << "Error: accept() failed";
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    qDebug() << "Client connected";

    return client_socket;
}

void BTHServer::Disconnect()
{
    closesocket(client_socket);
    to_recv = false;
}

void BTHServer::close()
{
    closesocket(server_socket);
    to_recv = false;
    is_running = false;
    this->wait();
}

SOCKET BTHServer::getServerSocket() const
{
    return server_socket;
}

void BTHServer::setIsRunning(bool value)
{
    is_running = value;
}
