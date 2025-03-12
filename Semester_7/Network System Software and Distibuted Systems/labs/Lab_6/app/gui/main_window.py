import threading
import tkinter as tk
from tkinter import ttk, messagebox
from tkinter.scrolledtext import ScrolledText

from app.services import Chat
from .packet_handler import PacketHandler
from .utils import update_users_list
from ..entities import CommandType, Packet, PacketType
from ..services.network_manager import NetworkManager



class MainWindow(tk.Tk):
    def __init__(self):
        super().__init__()

        self.network_manager = NetworkManager()
        self.chat = Chat(self.network_manager)

        self.title("UDP Chat")
        self.geometry("1100x620")
        self.resizable(False, False)

        self.main_frame = ttk.Frame(self)
        self.main_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

        self.__create_chat_form()
        self.__create_user_list()
        self.__create_buttons_block()

        self.packet_handler = PacketHandler(
            self.chat,
            self.text_area,
            self.chat_label,
            self.users_listbox,
        )

        threading.Thread(
            target=self.packet_handler.receive_packets,
            daemon=True
        ).start()

    def __create_chat_form(self):
        # Создаем контейнер для чата
        self.chat_frame = ttk.Frame(self.main_frame)
        self.chat_frame.pack(side=tk.LEFT, anchor='nw')

        self.chat_label = ttk.Label(self.chat_frame, text="Chat Room №0", font=("Arial", 12, "bold"))
        self.chat_label.pack(pady=5)

        self.text_area = ScrolledText(self.chat_frame, height=30, width=80, state=tk.DISABLED)
        self.text_area.pack(fill=tk.BOTH, expand=True)

        # Создаем контейнер для поля ввода и кнопки отправки
        self.entry_frame = ttk.Frame(self.chat_frame)
        self.entry_frame.pack(fill=tk.X, expand=True)

        self.msg_entry = ttk.Entry(self.entry_frame, width=80)
        self.msg_entry.grid(row=0, column=0, pady=5)

        self.send_btn = ttk.Button(self.entry_frame, text="Send", command=self.send_message_via_chat, width=20)
        self.send_btn.grid(row=0, column=1, padx=10, pady=5)

    def __create_user_list(self):
        # Создаем контейнер для списка пользователей
        self.users_frame = ttk.Frame(self.main_frame)
        self.users_frame.pack(side=tk.LEFT, anchor='nw', padx=10)

        self.users_label = ttk.Label(self.users_frame, text="Users Online", font=("Arial", 12, "bold"))
        self.users_label.pack(pady=5)

        self.users_listbox = tk.Listbox(self.users_frame, height=20, width=30)
        self.users_listbox.pack(expand=True, fill=tk.Y)

        update_users_list(self.users_listbox, self.chat)

    def __create_buttons_block(self):
        # Контейнер для кнопок
        self.buttons_frame = ttk.Frame(self.users_frame)
        self.buttons_frame.pack(side=tk.LEFT, anchor='nw', pady=10)

        buttons = [
            ttk.Button(self.buttons_frame, text="Refresh Users", command=self.refresh_users, width=25),
            ttk.Button(self.buttons_frame, text="Join Room", command=self.join_room, width=25),
            ttk.Button(self.buttons_frame, text="Ignore User", command=self.ignore_user, width=25),
            ttk.Button(self.buttons_frame, text="Show Network Info", command=self.show_network_info, width=25)
        ]
        for button in buttons:
            button.pack(pady=5)

        # Создаем контейнер для метки и поля ввода аргумента
        self.arg_frame = ttk.Frame(self.buttons_frame)
        self.arg_frame.pack(fill=tk.X, expand=True)
        self.arg_label = ttk.Label(self.arg_frame, text="Arg:", font=("Arial", 10, "bold"))
        self.arg_label.grid(row=0, column=0, pady=5)
        self.arg_entry = ttk.Entry(self.arg_frame, width=25)
        self.arg_entry.grid(row=0, column=1, padx=10, pady=5)

    def show_network_info(self):
        packet = Packet(
            packet_type=PacketType.OTHER,
            source=self.chat.current_user,
            payload={
                "ip": self.chat.ip,
            }
        )
        messagebox.showinfo(
            title="Network Parameters",
            message=packet.dict()
        )

    def join_room(self):
        room_number = int(self.arg_entry.get())
        if room_number == self.chat.current_user.room_no:
            print("[INFO] User is already a member of this room")
            return
        else:
            room_ip = self.network_manager.get_room_ip(room_number)
            if room_ip:
                self.network_manager.add_membership(room_ip)
                self.chat_label.config(text=f"Chat Room №{room_number}")
                self.chat.current_user.room_no = room_number
                if room_number == 0:
                    print("[INFO] User joined public room")
                else:
                    print(f"[INFO] User joined room №{room_number}")

    def refresh_users(self):
        packet = Packet(
            packet_type=PacketType.COMMAND,
            source=self.chat.current_user,
            payload={"command": CommandType.PING}
        )
        self.network_manager.send_packet(packet)
        self.chat.rooms[self.chat.current_user.room_no].users = [self.chat.current_user]  # Очищаем текущий список перед обновлением
        update_users_list(self.users_listbox, self.chat)

    def ignore_user(self):
        selected_user = self.users_listbox.get(tk.ACTIVE)
        if selected_user:
            username, ip = selected_user.split(" | ")
            self.packet_handler.black_list.append((username, ip))
            messagebox.showinfo("Information", f"Ignored user: {username}")
        else:
            messagebox.showwarning(
                title="Warning",
                message="User is not selected"
            )

    def send_message_via_chat(self):
        message = self.msg_entry.get()
        if not message:
            return
        self.chat.send_message(message)
        self.msg_entry.delete(0, tk.END)
