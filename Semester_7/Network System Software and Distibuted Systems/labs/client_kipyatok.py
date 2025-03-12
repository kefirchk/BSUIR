import socket
import os
import time
import select

globalFlag = 1

globalFlag = 1
globalStartTime = 0
globalEndTime = 0

RECONNECT_INTERVAL = 10
RECONNECT_COUNT = 3
READING_SIZE = 4096
WINDOW_SIZE = 1024
STOP_SENDING = 100
NUMBER_SIZE = 3

server_address = ('192.168.123.198', 12347)


def progress_bar(full, current):
    percent = (current / full) * 100
    s = f"{round(percent, 2)}%"
    print("Progress: " + s, end="\r")



def sendSocket(clientSocket, data):
    clientSocket.sendto(str(data).encode('utf-8'), server_address)



def recvSocket(clientSocket, size):
    data, serverAddress = clientSocket.recvfrom(size)
    data = data.decode('utf-8')
    return data



def waitForData(sock, timeout):
    ready_to_read, _, _ = select.select([sock], [], [], timeout)
    return ready_to_read


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

    while True:
        if waitForData(clientSocket, 1):
            data, client_address = clientSocket.recvfrom(READING_SIZE)
        else:
            break

    print(f"Server response: {data.decode('utf-8')}")



def uploadFile(clientSocket, filename):
    try:
        with open(filename, 'rb') as file:
            offset = startUploadSynchronization(clientSocket, filename)
            file.seek(offset, 0)
            filesize = os.path.getsize(filename)

            an = offset // (READING_SIZE - 4)
            data = b''
            i = 0
            sn = 0
            while True:
                data = file.read(READING_SIZE - 4)
                clientSocket.sendto(an.to_bytes(4, byteorder='big') + data, server_address)
                an += 1
                i += 1

                if i == WINDOW_SIZE or an * (READING_SIZE - 4) >= filesize:
                    if waitForData(clientSocket, 1):
                        sn = recvSocket(clientSocket, READING_SIZE)
                    else:
                        print(f"[ERROR]")
                        clientSocket.sendto((an - 1).to_bytes(4, byteorder='big') + data, server_address)
                        print(f"sn = {sn}")
                    if int(sn) != an:
                        file.seek((READING_SIZE - 4) * int(sn), 0)
                        an = int(sn)
                    i = 0

                if an * (READING_SIZE - 4) >= filesize:
                    break

        endUploadSynchronization(clientSocket, filename)

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


def clearBuffer(clientSocket):
    clientSocket.setblocking(False)

    try:
        while True:
            data, _ = clientSocket.recvfrom(READING_SIZE)
            if not data:
                break
    except BlockingIOError:
        pass




def downloadFile(clientSocket, filename):
    mode  = 'ab' if os.path.exists(filename) else 'wb+'

    with open(filename, mode) as file:
        fileSize = startDownloadSynchronization(clientSocket, filename)
        offset = os.path.getsize(filename)
        file.seek(0, os.SEEK_END)

        an = offset // READING_SIZE
        an_count = fileSize // READING_SIZE
        while an < an_count:

            frame, _ = clientSocket.recvfrom(READING_SIZE)
            file.write(frame)
            an = an + 1

        endDownloadSynchronization(clientSocket)



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

    if isFileExist(clientSocket):
        return
    
    downloadFile(clientSocket, data.split()[1])



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

    if firstWordUpper.startswith("DOWNLOAD"):
        downloadCommand(clientSocket, firstWordUpper)

    elif firstWordUpper.startswith("TIME"):
        timeCommand(clientSocket)

    elif firstWordUpper.startswith("ECHO"):
        echoCommand(clientSocket, firstWordUpper)

    elif firstWordUpper.startswith("QUIT"):
        quitCommand(clientSocket)

    else:
        print(f"[ERROR]: command '{arguments[0]}' is not exist")



def send_command():
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, READING_SIZE * WINDOW_SIZE)
    clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, READING_SIZE * WINDOW_SIZE)

    global globalFlag

    while globalFlag:
        arguments = input("> ").split()
        if not arguments:
            continue

        handleCommand(arguments, clientSocket)

if __name__ == "__main__":
    send_command()
