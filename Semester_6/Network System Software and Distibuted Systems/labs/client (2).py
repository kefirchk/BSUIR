import socket
import time
import os
import sys
import select

mainCycleFlag = True
RECONNECT_PERIOD = 10
RECONNECT_ATTEMPTS = 6
BUFFER_SIZE = 1024
RCV_BUFFER_SIZE = 1024
SIZE_FOR_WRITE = 32768
SIZE_FOR_READ = 65536
address = "0.0.0.0"
port = 0
currentId = -1


def sendInfo(info, sock): #+
    sock.sendto(str(info).encode('utf-8'), (address, port))


def receiveInfo(sock): #+
    ready_to_read, _, _ = select.select([sock], [], [], 1)
    if ready_to_read:
        data, _ = sock.recvfrom(BUFFER_SIZE)
        return data.decode('utf-8')
    return "ABRACADABRA"


def wait(sock):
    ready_to_read, _, _ = select.select([sock], [], [], 1)
    return ready_to_read

def showUploadPercents(offset, fileSize): #+
    percent = float(offset / fileSize * 100)
    hashes = '#' * (int(percent) // 5)
    spaces = '.' * (20 - len(hashes))
    sys.stdout.flush()
    sys.stdout.write("\rUploading... [{}{}] {}%".format(hashes, spaces, "{:.1f}".format(percent)))


def uploadCommand(filePath, sock):
    if not os.path.exists(filePath):
        print("No such file")
        return
    fileName = os.path.basename(filePath)
    fileSize = os.path.getsize(filePath)        #размер исходного файла
    uploadString = f"UPLOAD {fileName} {fileSize}"
    sendInfo(uploadString, sock)
    offset = int(receiveInfo(sock))             #скачанная часть файла
    if offset == fileSize:
        print(f"File {fileName} has already been uploaded to the server")
        return
    if offset > fileSize:
        offset = 0
    if offset > 0:
        downloadedPart = float(offset / fileSize * 100)
        print(f"Part of this file has already been downloaded, downloading will continue from {downloadedPart}%")
    sendTime = 0
    try:
        with open(filePath, "rb") as file:
            file.seek(offset)
            currentPosition = offset          
            file.seek(offset, 0)
            while True:
                data = file.read(BUFFER_SIZE - 2)
                if not data:
                    break
                startUploadTime = time.time()
                #sock.sendto(data, (address, port))		#это я только что изменил
                sendInfo(f"{data}", sock)
                endUploadTime = time.time()
                sendTime += (endUploadTime - startUploadTime)

                currentPosition += len(data)
                showUploadPercents(currentPosition, fileSize)
    finally:
        file.close()
    #confirmation = receiveInfo(sock)
    endUploadTime = time.time()
    #if confirmation != "File uploaded successfully":
     #   print("\nError sending file")
    sendSize = fileSize - offset
    uploadSpeed = "{:.2f}".format(sendSize/sendTime/1024)
    #sendInfo(uploadSpeed, sock)
    print(f"\nUpload speed: {uploadSpeed} Kb/s")


#def showDownloadPercents(offset, fileSize): #+
#    percent = float(offset / fileSize * 100)
#    hashes = '#' * int(percent // 5)
#    spaces = '.' * (20 - len(hashes))
#    sys.stdout.flush()
#    sys.stdout.write("\rDownloading... [{}{}] {}%".format(hashes, spaces, "{:.1f}".format(percent)))


def downloadCommand(filePath, sock):
    print(f"filePath: {filePath}")
    downloadString = f"DOWNLOAD {filePath}"
    sendInfo(downloadString, sock)
    fileSize = int(receiveInfo(sock))
    if fileSize == 0:           #размер исходного файла на сервере
        print("No such file")
        return

    pathParts = filePath.split("/")
    fileName = pathParts[-1]
    downloadsPath = "./download_files"
    fullFilePath = os.path.join(downloadsPath, fileName)
    if os.path.exists(fullFilePath):
        offset = os.path.getsize(fullFilePath)      #скачанная часть файла (после установки соединения)
        downloadedPart = offset / fileSize * 100
        if offset < fileSize:
            print(f"Part of this file has already been downloaded, downloading will continue from {downloadedPart}%")
        mode = "ab"
    else:
        offset = 0
        mode = "wb+"
    sendInfo(offset, sock)
    try:
        with open(fullFilePath, mode) as file:
            file.seek(0, os.SEEK_END)
            while wait(sock):
                data = sock.recv(RCV_BUFFER_SIZE)
                offset = offset + len(data)
                #print(offset)
                file.write(data)
                #showDownloadPercents(offset, fileSize)
    finally:
        file.close()
    #sendInfo("File downloaded successfully", sock)
    #downloadSpeed = receiveInfo(sock)  
    #print(f"\nDownload speed: {downloadSpeed} Kb/s")

    
def timeCommand(sock): #+
    timeString = "TIME"
    sendInfo(timeString, sock)
    serverTime = receiveInfo(sock)
    print(f"Server time: {serverTime}")


def echoCommand(info, sock): #+
    if info != "":
        sendInfo(f"ECHO {info}", sock)
        echoString = receiveInfo(sock)
        print(f"Echo from server: {echoString}")
    else:
        print("You should enter command \"ECHO (parameters)\". Try again")
        

def quitCommand(sock): #+
    global mainCycleFlag
    mainCycleFlag = False
    sendInfo("QUIT", sock)
    print("Successful exit")


def mainCycle(sock): #+
    global mainCycleFlag
    
    while mainCycleFlag:

        print("=================================")
        keyCommand = input("client> ")

        keyCommandArr = keyCommand.split(maxsplit=1)
        if len(keyCommandArr) == 0:
            continue
        first_word = keyCommandArr[0].strip().upper()
        arguments = "" if len(keyCommandArr) == 1 else keyCommandArr[1].strip()

        if first_word == "UPLOAD":
            uploadCommand(arguments, sock)
        elif first_word == "DOWNLOAD":
            downloadCommand(arguments, sock)
        elif first_word == "TIME":
            timeCommand(sock)
        elif first_word == "ECHO":
            echoCommand(arguments, sock)
        elif first_word == "QUIT" or first_word == "EXIT":
            quitCommand(sock)
        else:
            print("Unknown command, try again")
        
    sock.close()


def initializeSock(): #+
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, 8192)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, 425984)
    sock.bind(("192.168.123.198", port))
    print(f"Initialize completed (address: {address}, port: {port})")
    return sock


def main(): #+
    global address, port
    try:
        #address = input("Input address: ")
        #port = int(input("Input port: "))
        address = "192.168.123.213"
        port = 12345
        sock = initializeSock()
    except socket.error:
        print("Connection error")
        exit()
    except (TypeError, ValueError, OverflowError):
        print("Invalid parameters")
        exit()
    mainCycle(sock)


if __name__ == "__main__":
    main()
