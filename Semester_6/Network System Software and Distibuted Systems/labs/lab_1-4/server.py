import socket
import os
import time
import timeit
import select 
from datetime import datetime

globalFlag = 1
globalStartTime = 0
globalEndTime = 0

RECONNECT_INTERVAL = 1000
RECONNECT_COUNT = 3
READING_SIZE = 4096

QUIT_MESSAGE = "Connection closed"
DOWNLOAD_MESSAGE = "File downloaded successfully"
UPLOAD_MESSAGE = "File uploaded successfully"
UNKNOWN_MESSAGE = "Unknown command"

SERVER_ADDRESS = ('192.168.89.123', 8081)



def sendSocket(clientSocket, data):
    clientSocket.send(str(data).encode('utf-8'))



def recvSocket(clientSocket, size):
    return clientSocket.recv(size).decode('utf-8')



def connection(client_socket, interval, count):
    client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
    client_socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, interval)
    client_socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, interval)
    client_socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPCNT, count)

    return client_socket



def reconnect(serverSocket, clientSocket):
    print("Connection lost. Trying to reconnect...")
    clientSocket.close()
    clientSocket, addr = serverSocket.accept()
    clientSocket = connection(clientSocket, RECONNECT_INTERVAL, RECONNECT_COUNT)
    print(f"Reconnected: {addr}")

    return clientSocket



def startDownloadSynchronization(clientSocket, filename):
    offset = int(recvSocket(clientSocket, READING_SIZE))
    sendSocket(clientSocket, os.path.getsize(filename))
    print(f"Server response: {recvSocket(clientSocket, READING_SIZE)}")

    return offset



def endDownloadSynchronization(clientSocket, filename):
    print(f"Server response: {recvSocket(clientSocket, READING_SIZE)}")



def startUploadSynchronization(clientSocket, filename):
    responseData = int(recvSocket(clientSocket, READING_SIZE))
    sendSocket(clientSocket, os.path.getsize(filename))
    responseData = int(recvSocket(clientSocket, READING_SIZE))

    print(f"Synchronization data = {responseData}")

    clientSocket.send("Ready".encode('utf-8'))

    return responseData



def uploadFile(client_socket, filename):
    try:
        mode  = 'ab' if os.path.exists(filename) else 'wb+'

        with open(filename, mode) as file:
            fileSize = int(startUploadSynchronization(client_socket, filename))
            offset = os.path.getsize(filename)
            file.seek(0, os.SEEK_END)
            
            while fileSize > offset:

                data = client_socket.recv(4096)
                fileSize = fileSize - len(data);
                file.write(data)

    except Exception as e:
        print(f"Error uploading file: {e}")
    
    finally:
        file.close()



def isFileExist(clientSocket, filename):
    if not os.path.exists(filename):
        print(f"File {filename} doesn't exist")
        sendSocket(clientSocket, "File dosn't exist")
        return 1
    else:
        sendSocket(clientSocket, "Start sending")
        return 0



def downloadFile(client_socket, filename):
    offset = 0
    time = 0.0

    with open(filename, 'rb') as file:
        offset = startDownloadSynchronization(client_socket, filename)
        file.seek(offset, 0)

        i = 0
        while True:
            data = file.read(4096)
            if not data:
                break
            client_socket.send(data)
            if i == 1024:
                return (0, 0)
            i += 1

            

    endDownloadSynchronization(client_socket, filename)

    return (offset, os.path.getsize(filename))



def echoCommand(clientSocket, data):
    response = data[5:]
    sendSocket(clientSocket, response)
    print("-----<<<<< ECHO >>>>>-----")
    print(f"REQUEST: {data}")
    print(f"RESPONSE: {response}\n")



def timeCommand(clientSocket, request):
    response = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    sendSocket(clientSocket, response)
    print("-----<<<<< TIME >>>>>-----")
    print(f"REQUEST: {request}")
    print(f"RESPONSE: {response}\n")



def quitCommand(clientSocket, request):
    global globalFlag
    globalFlag = 0

    sendSocket(clientSocket, QUIT_MESSAGE)
    print("-----<<<<< QUIT >>>>>-----")
    print(f"REQUEST: {request}")
    print(f"RESPONSE: {QUIT_MESSAGE}\n")



def downloadCommand(clientSocket, data):
    print("-----<<<<< DOWNLOAD >>>>>-----")
    print(f"REQUEST: {data}")

    if isFileExist(clientSocket, data.split()[1]):
        return

    startTime = time.time()
    offset, fileSize = downloadFile(clientSocket, data.split()[1])
    if offset == 0 and fileSize == 0:
        return
    sendSocket(clientSocket, DOWNLOAD_MESSAGE)
    print(f"RESPONSE: {DOWNLOAD_MESSAGE}\n")
    endTime = time.time()
    elapsedTime = endTime - startTime

    formattedValue = "{:.2f}".format((fileSize - offset) / elapsedTime / 1024)
    print(f"Download Speed: {formattedValue} KB/s")


def uploadCommand(clientSocket, data):
    print("-----<<<<< UPLOAD >>>>>-----")
    print(f"REQUEST: {data}")
    uploadFile(clientSocket, data.split()[1])
    sendSocket(clientSocket, UPLOAD_MESSAGE)
    print(f"RESPONSE: {UPLOAD_MESSAGE}\n")



def unknownCommand(clientSocket, data):
    print("-----<<<<< UNKNOWN >>>>>-----")
    print(f"REQUEST: {data}")
    sendSocket(clientSocket, UNKNOWN_MESSAGE)
    print(f"RESPONSE: {UNKNOWN_MESSAGE}\n")


def handleCommand(request, clientSocket):
    global globalFlag 
    commandParts = request.split()
    
    if request.startswith("ECHO"):
        echoCommand(clientSocket, request)
    
    elif request == "TIME":
        timeCommand(clientSocket, request)

    elif request == "QUIT":
        quitCommand(clientSocket, request)

    elif commandParts[0] == "DOWNLOAD":
        downloadCommand(clientSocket, request)

    elif commandParts[0] == "UPLOAD":
        uploadCommand(clientSocket, request)

    else:
        unknownCommand(clientSocket, request)



def main():
    global globalFlag

    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket.bind(SERVER_ADDRESS)
    serverSocket.listen(5)

    print(f"Server listening on {SERVER_ADDRESS}")

    while globalFlag:

        inputs = [serverSocket]

        while globalFlag:

            inputready, outputready, exceptready = select.select(inputs,[], inputs)

            for readySocket in inputready:
                if readySocket == serverSocket:
                    clientSocket, addr = serverSocket.accept()
                    clientSocket = connection(clientSocket, RECONNECT_INTERVAL, 3)
                    print(f"Connection from {addr}")

                    inputs.append(clientSocket)

                else:
                    try:
                        request = b''
                        request = recvSocket(readySocket, READING_SIZE)

                        handleCommand(request, readySocket)

                    except socket.error:
                        readySocket = reconnect(serverSocket, readySocket)

        clientSocket.close()

if __name__ == "__main__":
    main()
