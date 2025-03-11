import socket
import os
import time
import select

globalFlag = 1

globalFlag = 1
globalStartTime = 0
globalEndTime = 0

RECONNECT_INTERVAL = 1000
RECONNECT_COUNT = 3
READING_SIZE = 4096

server_address = ('192.168.89.123', 8081)



def connection(clientSocket, interval, count):
    clientSocket.connect(server_address)
    clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 0)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, interval)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, interval)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPCNT, count)

    return clientSocket



def reconnect(clientSocket):
    clientSocket.close()
    print("Connection lost. Trying to reconnect...")
    print("Do you want to reconnect?(Y/N)")

    user_input = input("-> ").split()
    if user_input[0] == 'Y':
        clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        connection(clientSocket, RECONNECT_INTERVAL, RECONNECT_COUNT)

        return clientSocket
    else:
        return None



def sendSocket(clientSocket, data):
    clientSocket.send(str(data).encode('utf-8'))



def recvSocket(clientSocket, size):
    return clientSocket.recv(size).decode('utf-8')


def startUploadSynchronization(clientSocket, filename):
    sendSocket(clientSocket, os.path.getsize(filename))
    offset = int(recvSocket(clientSocket, READING_SIZE))
    sendSocket(clientSocket, os.path.getsize(filename))
    print(f"Server response: {recvSocket(clientSocket, READING_SIZE)}")

    return offset



def endUploadSynchronization(clientSocket, filename):
    print(f"Server response: {recvSocket(clientSocket, READING_SIZE)}")



def startDownloadSynchronization(clientSocket, filename):

    offset = os.path.getsize(filename)
    sendSocket(clientSocket, offset)

    fileSize = int(recvSocket(clientSocket, READING_SIZE))

    formatedResponseData = "{:.2f}".format(offset / 1024)
    formatedFileSize = "{:.2f}".format(fileSize / 1024)
    print(f"Current size of {filename}: {formatedResponseData} KB  of {formatedFileSize} KB")

    sendSocket(clientSocket, "Ready")

    return fileSize



def endDownloadSynchronization(clientSocket):
    sendSocket(clientSocket, "OK")
    print(f"Server response: {recvSocket(clientSocket, READING_SIZE)}")



def uploadFile(client_socket, filename):
    try:
        with open(filename, 'rb') as file:
            offset = startUploadSynchronization(client_socket, filename)
            file.seek(offset, 0)

            while True:
                data = file.read(1024)
                if not data:
                    break
                client_socket.send(data)

        endUploadSynchronization(client_socket, filename)

        return (offset, os.path.getsize(filename))

    finally:
        file.close()



def isFileExist(clientSocket):
    message = recvSocket(clientSocket, READING_SIZE)
    print(f"Server response: {message}")
    if message == "File dosn't exist":
        return 1
    else:
        return 0


def downloadFile(clientSocket, filename):
    try:
        mode  = 'ab' if os.path.exists(filename) else 'wb+'

        with open(filename, mode) as file:

            fileSize = startDownloadSynchronization(clientSocket, filename)
            offset = os.path.getsize(filename)
            file.seek(0, os.SEEK_END)
            i = 0

            while fileSize > offset:
                # Устанавливаем таймаут в 1 секунду
                ready, _, _ = select.select([clientSocket], [], [], 1)

                if ready:
                    data = clientSocket.recv(4096)
                    offset += len(data)
                    i += 1
                    file.write(data)
                    # print(data)
                else:
                    print("Timeout: No data received for 1 second.")
                    print(f"i = {i},    offset = {offset}")
                    sendSocket(clientSocket, "DOWNLOAD " + filename)
                    # fileSize = startDownloadSynchronization(clientSocket, filename)
                    # offset = os.path.getsize(filename)
                    # file.seek(0, os.SEEK_END)
                    return 1

        endDownloadSynchronization(clientSocket)
        return 0

    finally:
        file.close()



def timeCommand(clientSocket):
    sendSocket(clientSocket, "TIME")
    data = recvSocket(clientSocket, READING_SIZE)
    print(f"Server response: {data}")



def echoCommand(clientSocket, data):
    sendSocket(clientSocket, data)
    data = recvSocket(clientSocket, READING_SIZE)
    print(f"Server response: {data}")



def quitCommand(clientSocket):
    global globalFlag
    globalFlag = 0

    sendSocket(clientSocket, "QUIT")
    data = recvSocket(clientSocket, READING_SIZE)
    print(f"Server response: {data}")



def downloadCommand(clientSocket, data):
    sendSocket(clientSocket, data)

    result = 1

    while result:
        if isFileExist(clientSocket):
            return

        result = downloadFile(clientSocket, data.split()[1])
    



def uploadCommand(clientSocket, data):
    if not os.path.exists(data.split()[1]):
        print(f"File {data.split()[1]} doesn't exist")
        return
    sendSocket(clientSocket, data)

    startTime = time.time()
    offset, fileSize = uploadFile(clientSocket, data.split()[1])
    endTime = time.time()
    elapsedTime = endTime - startTime

    formattedValue = "{:.2f}".format((fileSize - offset) / elapsedTime / 1024)
    print(f"Download Speed: {formattedValue} KB/s")


def handleCommand(arguments, clientSocket):
    global globalFlag

    firstWordUpper = ' '.join([arguments[0].upper()] + arguments[1:])

    if firstWordUpper.startswith("UPLOAD"):
        uploadCommand(clientSocket, firstWordUpper)

    elif firstWordUpper.startswith("DOWNLOAD"):
        downloadCommand(clientSocket, firstWordUpper)

    elif firstWordUpper.startswith("TIME"):
        timeCommand(clientSocket)

    elif firstWordUpper.startswith("ECHO"):
        echoCommand(clientSocket, firstWordUpper)

    elif firstWordUpper.startswith("QUIT"):
        quitCommand(clientSocket)

    else:
        print(f"There is no command {arguments[0]}")



def send_command():
    try:
        clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        connection(clientSocket, RECONNECT_INTERVAL, RECONNECT_COUNT)

        global globalFlag

        while globalFlag:
            try:
                arguments = input("-> ").split()
                if not arguments:
                    continue

                handleCommand(arguments, clientSocket)

            except socket.error:
                #clientSocket = reconnect(clientSocket)
                if clientSocket == None:
                    break

    finally:
        clientSocket.close()

if __name__ == "__main__":
    send_command()

