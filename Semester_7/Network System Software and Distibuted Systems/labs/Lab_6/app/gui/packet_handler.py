import json
import tkinter as tk

import select

from app.config import PACKET_SIZE, PORT
from app.entities import CommandType, Packet, PacketType
from app.services import Chat
from .utils import update_users_list


class PacketHandler:
    def __init__(self, chat: Chat, text_area, chat_label, users_listbox):
        self.chat = chat
        self.text_area = text_area
        self.chat_label = chat_label
        self.users_listbox = users_listbox
        self.black_list = []

    def process_command(self, packet: Packet):
        if packet.payload['command'] == CommandType.PING:
            # Отправляем ответ "PONG"
            response = Packet(
                packet_type=PacketType.COMMAND,
                source=self.chat.current_user,
                payload={"command": CommandType.PONG}
            )
            self.chat.network_manager.send_packet(response)
        elif packet.payload['command'] == CommandType.PONG:
            # Обрабатываем ответ "PONG" и обновляем список пользователей
            user = packet.source
            room = self.chat.rooms[self.chat.current_user.room_no]
            if user not in room.users:
                room.users.append(user)
            update_users_list(self.users_listbox, self.chat)

    def process_packet(self, packet: Packet):
        print("[INFO] Receive packet:", packet)
        try:
            # Обработка команд
            if packet.packet_type == PacketType.COMMAND:
                self.process_command(packet)
            # Обработка сообщений из чата
            else:
                self.display_message(self.text_area, packet)
        except ValueError as e:
            print("[ERROR] Invalid message format:", e)

    def display_message(self, text_area, packet: Packet):
        if (((packet.source.username, packet.source.ip) not in self.black_list) and
            (packet.source.room_no == self.chat.current_user.room_no)):
            message = packet.payload['message']
            text_area.config(state=tk.NORMAL)
            text_area.insert(tk.END, f"{packet.source.username}: {message['timestamp']}\n")
            text_area.insert(tk.END, f"{message['context']}\n\n")
            text_area.config(state=tk.DISABLED)
            text_area.see(tk.END)
        else:
            print(f"[INFO] User '{packet.source.username}' in blacklist")

    def receive_packets(self):
        while True:
            try:
                r, _, _ = select.select([self.chat.network_manager.socket], [], [], 0.5)
                if r:
                    data, addr = self.chat.network_manager.socket.recvfrom(PACKET_SIZE)
                    if (addr[0] == self.chat.ip) and (addr[1] == PORT):
                        print("[INFO] MY PACKET\n")
                    packet_data = json.loads(data.decode('utf-8'))
                    packet = Packet(**packet_data)
                    self.process_packet(packet=packet)
            except Exception as e:
                print(f"[ERROR] Failed to receive message: {e}")
