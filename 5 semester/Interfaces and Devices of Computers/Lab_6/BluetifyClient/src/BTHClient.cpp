#include "BTHClient.h"

BTHClient::BTHClient(QObject *parent) : QThread(parent)
{
    is_running = false;

    // Подготовка WinSock
    if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
        qDebug() << "Failed to initialize Winsock";
        exit(EXIT_FAILURE);
    }
}

BTHClient::~BTHClient()
{
    this->Disconnect();
    this->wait();

    // Освобождаем сокет
    closesocket(client_socket);
    CloseHandle((LPVOID)client_socket); // убеждаемся, что освободили сокет

    // Прекращение использования служб WinSock
    WSACleanup();
}

void BTHClient::run()
{
    is_running = true;
    while(is_running)
    {
        if(to_send == true)
        {
            // Открытие файла для чтения
            qDebug() << "Sending << " + file_name + " >>";

            std::ifstream file(file_name.toStdString().c_str(), std::ios::binary);
            if (!file.is_open()) {
                qDebug() << "Error: cannot open file";
                closesocket(client_socket);
                WSACleanup();
                exit(EXIT_FAILURE);
            }


            // Чтение и передача файла по сокетам
            char buffer[BUFFER_SIZE];
            send(client_socket, "SEND_FILE", STR_SIZE, 0);
            while (!file.eof()) {
                file.read(buffer, BUFFER_SIZE);
                if (send(client_socket, buffer, BUFFER_SIZE, 0) == SOCKET_ERROR) {
                    emit serverIsOffSignal();
                    qDebug() << "Error: send() failed";
                    break;
                }
            }
            send(client_socket, "EOF", 3, 0);

            file.close();
            to_send = false;
            qDebug() << "File is sended successfully";
        }
    }
}

bool BTHClient::Socket()
{
    // Создание сокета для клиента
    client_socket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if (client_socket == INVALID_SOCKET) {
        qDebug() << "Error: socket() failed";
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    this->server_struct = {0};
    this->server_struct.addressFamily = AF_BTH;
    this->server_struct.serviceClassId = RFCOMM_PROTOCOL_UUID; // Уникальный идентификатор сервиса
    this->server_struct.port = CHANNEL;                        // Порт сервера, к которому мы подключаемся
    this->server_struct.btAddr = 0;                            // Адрес сервера, к которому подключаемся

    return true;
}

bool BTHClient::Connect()
{
    // Подключение к серверу
    if (::connect(client_socket, reinterpret_cast<sockaddr*>(&server_struct), sizeof(server_struct)) == SOCKET_ERROR)
    {
        qDebug() << "Error: connect() failed";
        return false;
    }

    qDebug() << "Port: " << this->server_struct.port;
    return true;
}

void BTHClient::Disconnect()
{
    is_running = false;
    closesocket(client_socket);
}

void BTHClient::setServerAddress(const BTH_ADDR& address)
{
    server_struct.btAddr = address;
}

SOCKET BTHClient::getClientSocket() const
{
    return client_socket;
}

void BTHClient::sendClientInfo()
{
    qDebug() << "class: " << this->radio_struct.deviceClass.toStdString().c_str();
    qDebug() << "address: " << this->radio_struct.address.toStdString().c_str();
    qDebug() << "name: " << this->radio_struct.instanceName.toStdString().c_str();
    qDebug() << "manufacturer: " << this->radio_struct.manufacturer.toStdString().c_str();

    send(client_socket, this->radio_struct.deviceClass.toStdString().c_str(), BUFFER_SIZE, 0);
    send(client_socket, this->radio_struct.address.toStdString().c_str(), BUFFER_SIZE, 0);
    send(client_socket, this->radio_struct.instanceName.toStdString().c_str(), BUFFER_SIZE, 0);
    send(client_socket, this->radio_struct.manufacturer.rightJustified(8, '0').toStdString().c_str(), BUFFER_SIZE, 0);
}

void BTHClient::setToSend(bool value)
{
    this->to_send = value;
}
