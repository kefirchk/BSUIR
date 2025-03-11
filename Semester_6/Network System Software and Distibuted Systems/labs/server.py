import socket
import os
import time
import select
import timeit
import errno
import threading
from datetime import datetime

globalFlag = 1
globalStartTime = 0
globalEndTime = 0
globalTCP_UDP = 1

RECONNECT_INTERVAL = 10
RECONNECT_COUNT = 3
READING_SIZE = 4096
WINDOW_SIZE = 8
STOP_SENDING = 100
TIMEOUT_SECONDS = 1
NUMBER_SIZE = 3

QUIT_MESSAGE = "Connection closed"
DOWNLOAD_MESSAGE = "File downloaded successfully"
UPLOAD_MESSAGE = "File uploaded successfully"
UNKNOWN_MESSAGE = "Unknown command"

SERVER_ADDRESS = ('192.168.0.100', 12345)

MIN_T = 1
MAX_T = 2
mutex = threading.Lock()
globalIsWork = []
globalToKill = []

def sendSocket(serverSocket, clientAddress, data):
    serverSocket.sendto(str(data).encode('utf-8'), clientAddress)



def recvSocket(serverSocket, size):
    # isCommand
    # request, clientAddress = serverSocket.recvfrom(READING_SIZE, socket.MSG_PEEK)

    data, clientAddress = serverSocket.recvfrom(size)
    data = data.decode('utf-8')
    return (data, clientAddress)



def startDownloadSynchronization(serverSocket, clientAddress, filename):
    offset, clientAddress = recvSocket(serverSocket, READING_SIZE)
    offset = int(offset)
    sendSocket(serverSocket, clientAddress, os.path.getsize(filename))
    print(f"Server response: {recvSocket(serverSocket, READING_SIZE)}")

    return offset



def endDownloadSynchronization(serverSocket, filename):
    print(f"Server response: {recvSocket(serverSocket, READING_SIZE)}")



def startUploadSynchronization(serverSocket, clientAddress, filename):
    responseData, _ = recvSocket(serverSocket, READING_SIZE)
    responseData = int(responseData)
    sendSocket(serverSocket, clientAddress, os.path.getsize(filename))
    responseData, _ = recvSocket(serverSocket, READING_SIZE)
    responseData = int(responseData)

    print(f"Synchronization data = {responseData}")

    sendSocket(serverSocket, clientAddress, "Ready")

    return responseData



def uploadFile(serverSocket, clientAddress, filename):
    try:
        mode  = 'ab' if os.path.exists(filename) else 'wb+'

        with open(filename, mode) as file:
            fileSize = int(startUploadSynchronization(serverSocket, clientAddress, filename))
            offset = os.path.getsize(filename)
            file.seek(0, os.SEEK_END)
            
            an = offset // (READING_SIZE - 4)
            data = b''
            i = 0
            framsWithSn = {}
            while fileSize >= offset:
                frame, clientAddress = serverSocket.recvfrom(READING_SIZE)

                sn = int.from_bytes(frame[:4], byteorder='big')
                data = frame[4:]
                i += 1

                framsWithSn[sn] = data
                if i == WINDOW_SIZE or offset + i * (READING_SIZE - 4) >= fileSize:
                    framsWithSn = dict(sorted(framsWithSn.items()))
                    for key, value in framsWithSn.items():
                        if an == key:
                            file.write(value)
                            an += 1
                            offset += READING_SIZE - 4
                        else:
                            break
                    framsWithSn.clear()
                    sendSocket(serverSocket, clientAddress, an)
                    i = 0
    
    finally:
        file.close()



def isFileExist(serverSocket, clientAddress, filename):
    if not os.path.exists(filename):
        print(f"File {filename} doesn't exist")
        sendSocket(serverSocket, clientAddress, "File dosn't exist")
        return 1
    else:
        sendSocket(serverSocket, clientAddress, "Start sending")
        return 0



def sendBinary(serverSocket, file, clientAddress):
    serverSocket.sendto(file.read(READING_SIZE), clientAddress)


def downloadFile(serverSocket, clientAddress, filename):
    offset = 0

    with open(filename, 'rb') as file:
        offset = startDownloadSynchronization(serverSocket, clientAddress, filename)
        mutex.release()
        file.seek(offset, 0)
        filesize = os.path.getsize(filename)

        an = offset // READING_SIZE
        an_count = filesize // READING_SIZE
        downloadTime = 0.0
        while an != an_count:
            time.sleep(0.001)
            mutex.acquire()
            downloadTime += timeit.timeit(lambda: sendBinary(serverSocket, file, clientAddress), number=1)
            mutex.release()
            an += 1

            # print(f"an = {an}, pid = {threading.get_ident()}")

        mutex.acquire()
        endDownloadSynchronization(serverSocket, filename)

        formattedValue = "{:.2f}".format((filesize - offset) / downloadTime / 1024)
        print(f"Download Speed: {formattedValue} KB/s")
    return (offset, os.path.getsize(filename))



def echoCommand(serverSocket, clientAddress, data):
    response = data[5:]
    sendSocket(serverSocket, clientAddress, response)
    print(f"-----<<<<< ECHO {threading.get_ident()} >>>>>-----")
    print(f"REQUEST: {data}")
    print(f"RESPONSE: {response}\n")



def timeCommand(serverSocket, clientAddress, data):
    response = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    sendSocket(serverSocket, clientAddress, response)
    print(f"-----<<<<< TIME {threading.get_ident()} >>>>>-----")
    print(f"REQUEST: {data}")
    print(f"RESPONSE: {response}\n")



def quitCommand(serverSocket, clientAddress, data):
    global globalFlag
    globalFlag = 0

    sendSocket(serverSocket, clientAddress, QUIT_MESSAGE)
    print(f"-----<<<<< QUIT {threading.get_ident()} >>>>>-----")
    print(f"REQUEST: {data}")
    print(f"RESPONSE: {QUIT_MESSAGE}\n")



def downloadCommand(serverSocket, clientAddress, data):
    print(f"-----<<<<< DOWNLOAD {threading.get_ident()} >>>>>-----")
    print(f"REQUEST: {data}")

    if isFileExist(serverSocket, clientAddress, data.split()[1]):
        return

    startTime = time.time()
    offset, fileSize = downloadFile(serverSocket, clientAddress, data.split()[1])
    endTime = time.time()

    sendSocket(serverSocket, clientAddress, DOWNLOAD_MESSAGE)
    print(f"RESPONSE: {DOWNLOAD_MESSAGE}\n")
    download_time = endTime - startTime 
    formattedValue = "{:.2f}".format((fileSize - offset) / download_time / 1024)
    print(f"Download Speed: {formattedValue} KB/s")



def uploadCommand(serverSocket, clientAddress, data):
    print(f"-----<<<<< UPLOAD {threading.get_ident()} >>>>>-----")
    print(f"REQUEST: {data}")
    uploadFile(serverSocket, clientAddress, data.split()[1])
    sendSocket(serverSocket, clientAddress, UPLOAD_MESSAGE)
    print(f"RESPONSE: {UPLOAD_MESSAGE}\n")



def unknownCommand(clientAddress, data):
    print(f"-----<<<<< UNKNOWN {threading.get_ident()} >>>>>-----")
    print(f"REQUEST: {data}")
    sendSocket(clientAddress, UNKNOWN_MESSAGE)
    print(f"RESPONSE: {UNKNOWN_MESSAGE}\n")



def handleCommand(serverSocket, request, clientAddress):
    global globalFlag 
    commandParts = request.split()

    if commandParts[0] == "ECHO":
        echoCommand(serverSocket, clientAddress, request)
        mutex.release()
    
    elif request == "TIME":
        timeCommand(serverSocket, clientAddress, request)
        mutex.release()

    elif request == "QUIT":
        quitCommand(serverSocket, clientAddress, request)
        mutex.release()

    elif commandParts[0] == "DOWNLOAD":
        downloadCommand(serverSocket, clientAddress, request)
        mutex.release()

    elif commandParts[0] == "UPLOAD":
        uploadCommand(serverSocket, clientAddress, request)

    else:
        unknownCommand(clientAddress, request)



def isCommand(message):
    message = message.decode('utf-8')
    if message.startswith("ECHO"):
        return True
    elif message == "TIME":
        return True
    elif message == "QUIT":
        return True
    elif message.startswith("DOWNLOAD"):
        return True
    elif message.startswith("UPLOAD"):
        return True
    else:
        return False



def consumerCommand(serverSocket, number):
    global globalIsWork
    global globalToKill

    while not globalToKill[number]:
        request = b''
        time.sleep(0.1)
        mutex.acquire()

        serverSocket.setblocking(False)
        try:
            request, clientAddress = serverSocket.recvfrom(READING_SIZE, socket.MSG_PEEK)
        except socket.error as e:
            pass

        # print(f"pid = {threading.get_ident()}, request = {request}")
        serverSocket.setblocking(True)

        if isCommand(request):
            globalIsWork[number] = True
            request, clientAddress = recvSocket(serverSocket, READING_SIZE)
            handleCommand(serverSocket, request, clientAddress)
            globalIsWork[number] = False
        else:
            mutex.release()



def main():
    global globalFlag
    global globalIsWork
    global globalToKill
    number = 0

    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, READING_SIZE * WINDOW_SIZE)
    # serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, READING_SIZE * WINDOW_SIZE)
    serverSocket.bind(SERVER_ADDRESS)
    print(f"UDP server listening on {SERVER_ADDRESS}")

    threads = []

    for _ in range(MAX_T):
        thread = threading.Thread(target=consumerCommand, args=(serverSocket, number))
        globalIsWork.append(False)
        globalToKill.append(False)
        thread.start()
        threads.append(thread)
        number += 1
    # and sum(1 for value in globalIsWork if value) > MIN_T

    while True:
        print(globalIsWork, [thread.ident % 10000 for thread in threads])

        threads_to_remove = []
        summary = 0
        for i in globalIsWork:
            if i == False:
                summary += 1
        for i in range(len(threads) - MIN_T):
            if summary > MIN_T and not globalIsWork[MIN_T + i]:
                globalToKill[MIN_T + i] = True
                threads[MIN_T + i].join()
                threads_to_remove.append(MIN_T + i)

        time.sleep(3)

        for i in threads_to_remove:
            threads.remove(threads[i])
            globalIsWork.remove(globalIsWork[i])
            globalToKill.remove(globalToKill[i])
            number -= 1

        threads_to_remove.clear()


        # for thread in threads:
        #     if sum(1 for value in globalIsWork if value) > MIN_T:
        #         threads.remove(thread)
        #         number -= 1

        if MAX_T > len(threads) and summary == 0:
            new_thread = threading.Thread(target=consumerCommand, args=(serverSocket, number))
            globalIsWork.append(False)
            globalToKill.append(False)
            new_thread.start()
            threads.append(new_thread)
            number += 1

        time.sleep(1)

    serverSocket.close()

if __name__ == "__main__":
    main()
