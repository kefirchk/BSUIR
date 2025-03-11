import socket
import datetime
import time
import sys
import os
import select
import threading

HOST = "192.168.196.198"
PORT = 12345

UPLOAD_PATH = "./upload_files"
SERVER_FILES_PATH = "./server_files/"

READ_BUFFER_SIZE = 16384 # размер буфера чтения 8192
WRITE_BUFFER_SIZE = 1024 # размер буфера записи 2048
BUFFER_SIZE = 1024       # 1024
MAX_BUFFER = 2048
SIZE_FOR_READ = 2048    
SIZE_FOR_WRITE = 2048
N_MIN = 2
N_MAX = 5
TIMEOUT = 30

current_threads_number = 0
threads_info = []
delete_threads = []

#######################################################################################
class File:
    def __init__(self, file_name, mode, socket, address):
        self.file_name = file_name
        self.mode = mode
        self.socket = socket
        self.address = address

    def wait(self, socket):
        readyToRead, _, _ = select.select([socket], [], [], 1)
        return readyToRead

    def send_file(self, offset):
        sended_data_size = 0
        send_time = 0
        with open(self.file_name, self.mode) as file:
            file.seek(int(offset), 0)
            file_size = os.path.getsize(self.file_name)
            while True:
                data = file.read(WRITE_BUFFER_SIZE)
                if not data:
                    break
                start_time = time.time()
                self.socket.sendto(data, self.address)
                end_time = time.time()
                send_time += end_time - start_time
                sended_data_size += len(data)
            print("\n")
            return (send_time)
        
    def recv_file(self, file_size, offset):
        recv_data_size = 0
        with open(self.file_name, self.mode) as file:
            file.seek(0, os.SEEK_END)
            offset = os.path.getsize(self.file_name)
            while self.wait(self.socket):
                data, address = self.socket.recvfrom(READ_BUFFER_SIZE)
                recv_data_size += len(data)
                if not data:
                    break
                file.write(data)
            print("\n")

#######################################################################################
class ServerCommander:
    def __init__(self, server_socket):
        self.server_socket = server_socket
        self.client_is_active = True

    
    def send_msg(self, data):
        self.server_socket.sendto(str(data).encode("utf-8"), self.client_address)


    def recv_msg(self):
        recv_data, recv_address = self.server_socket.recvfrom(BUFFER_SIZE)
        return (recv_data.decode("utf-8"), recv_address)


    def exec_quit(self):
        self.client_is_active = False


    def exec_time(self):
        current_time_formatted = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        print(f"Now time: {current_time_formatted}")
        self.send_msg(current_time_formatted)


    def exec_echo(self, args):
        self.send_msg(args)


    def exec_download(self, file_name):
        if not os.path.exists(SERVER_FILES_PATH + file_name):
            print(f"File name: {file_name}")
            print("File status: NOT FOUND")
            print("File size: 0")
            self.send_msg("0")
        else:
            print(f"File name: {file_name}")
            print("File status: IS FOUND")

            file_size = os.path.getsize(SERVER_FILES_PATH + file_name)
            self.send_msg(file_size)
            print(f"File size: {file_size}")
            
            file_offset, _ = self.recv_msg()
            file_offset = int(file_offset)
            print(f"File offset: {file_offset}")

            file = File(SERVER_FILES_PATH + file_name, "rb", self.server_socket, self.client_address)
            send_time = file.send_file(file_offset)
            speed = "{:.2f}".format((file_size - file_offset) / send_time / 1024)
            print("Download Speed: {} KB/s".format(speed))


    def exec_upload(self, args):
        path_parts = ' '.join(args.split()[:-1]).split("/")
        full_file_name = os.path.join(UPLOAD_PATH, path_parts[-1])

        if os.path.exists(full_file_name):
            print(f"File name: {full_file_name}")
            print("File status: IS FOUND")
            mode = 'ab'
            file_offset = os.path.getsize(full_file_name)
            print(f"Old file size: {file_offset}")
        else:
            print(f"File name: {full_file_name}")
            print("File status: NOT FOUND")
            mode = 'wb+'
            file_offset = 0 
            print("Old file size: 0")
            
        file_size = int(args.split()[-1])
        print(f"New file size: {file_size}")

        self.send_msg(file_offset)

        file = File(full_file_name, mode, self.server_socket, self.client_address)
        file.recv_file(file_size, file_offset)


    def handle_command(self, msg):
        if len(msg) == 0:
            return
        print('---------------REQUEST---------------')
        print(f"Get Request: {msg}")
        
        full_cmd = msg.split(maxsplit=1)
        command = full_cmd[0].strip().upper()
        arguments = "" if len(full_cmd) == 1 else full_cmd[1].strip()

        if command == "QUIT":  
            self.exec_quit()
        elif command == "TIME":
            self.exec_time()
        elif msg.startswith("ECHO"):
            self.exec_echo(msg[5:])
        elif command == "DOWNLOAD":
            self.exec_download(arguments)
        elif command == "UPLOAD":
            self.exec_upload(arguments)
        else:
            print("Error: unknown command")
        print('-------------------------------------')

    def set_client_address(self, client_address):
        self.client_address = client_address

#######################################################################################
        
class Server:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_running = True
    

    def find_threads_to_delete(self):
        global delete_threads
        if current_threads_number > N_MAX:
            for th in threads_info:
                if th[1] == False:
                    delete_threads.append([th[0], time.time()])
                    

    def delete_threads_func(self):
        global threads_info
        global delete_threads
        global current_threads_number

        delete_id = []
        for th in delete_threads:
            if time.time() - th[1] >= TIMEOUT:
                delete_id.append(th[0])

        for i in delete_id:
            delete_threads = [el for el in delete_threads if el[0] != i]
            threads_info = [el for el in threads_info if el[0] != i]
            current_threads_number -= 1



    def start(self):
        global current_threads_number
        global threads_info
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, WRITE_BUFFER_SIZE * SIZE_FOR_WRITE)
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, MAX_BUFFER)  #pochemy-to zakommencheno
        
        self.server_socket.bind((self.host, self.port))
        print(f"UDP Server is listening on {self.host}:{self.port}")

        for _ in range(N_MIN):
            thread = threading.Thread(target=self.client_handler)
            threads_info.append([thread, False])
            current_threads_number += 1
            thread.start()
        print(f"Current threads amount: {current_threads_number}")
        while True:    
            self.find_threads_to_delete()
            self.delete_threads_func()


    def stop(self):
        self.server_running = False
        self.server_socket.close()
        print("Server is off. Goodbye!")


    
    def client_handler(self):
        global threads_info
        current_thread_id = threading.get_ident()
        for el in threads_info:
            if el[0] == current_thread_id:
                el[1] = True
        print(f"threads_info = {threads_info}")
        print(f"delete_threads = {delete_threads}")
        print(f"threads_number = {current_threads_number}")
        commander = ServerCommander(self.server_socket)
        
        while commander.client_is_active:
            msg, client_address = self.server_socket.recvfrom(BUFFER_SIZE)
            self.client_address = client_address
            commander.set_client_address(client_address)
            commander.handle_command(msg.decode("utf-8"))
        
        for el in threads_info:
            if el[0] == current_thread_id:
                el[1] = False
        self.server_socket.close()
        print(f"threads_info = {threads_info}")
        print(f"delete_threads = {delete_threads}")
        print(f"threads_number = {current_threads_number}")

#######################################################################################

if __name__ == "__main__":
    try:
        # HOST = socket.gethostbyname(socket.gethostname())
        PORT = int(input("Enter a port number: "))
        server = Server(HOST, PORT)
        server.start()
    except KeyboardInterrupt:
        server.stop()
        sys.exit()
   
