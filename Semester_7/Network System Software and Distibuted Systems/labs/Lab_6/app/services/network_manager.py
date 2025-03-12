import socket
import struct
import netifaces

from app.config import PUBLIC_ROOM_IP, PRIVATE_ROOM_IPS, PORT
from app.entities import Packet


class NetworkManager:

    def __init__(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        mreq = struct.pack('4sL', socket.inet_aton(PUBLIC_ROOM_IP), socket.INADDR_ANY)
        self.socket.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)
        self.socket.bind(('', PORT))
        self.ip = self.get_network_params()

    def send_packet(self, packet: Packet):
        room_ip = self.get_room_ip(packet.source.room_no)
        print(f"[INFO] Send packet to room '{room_ip}': {packet}")
        if room_ip:
            self.socket.sendto(packet.json().encode('utf-8'), (room_ip, PORT))

    def add_membership(self, ip):
        self.socket.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, socket.inet_aton(ip) + socket.inet_aton(self.ip))

    def drop_membership(self, ip):
        self.socket.setsockopt(socket.IPPROTO_IP, socket.IP_DROP_MEMBERSHIP, socket.inet_aton(ip) + socket.inet_aton(self.ip))

    @staticmethod
    def get_room_ip(room_number):
        if room_number == 0:
            return PUBLIC_ROOM_IP
        elif 1 <= room_number <= 4:
            return PRIVATE_ROOM_IPS[room_number - 1]
        return None

    @staticmethod
    def get_network_params():
        iface = netifaces.gateways()['default'][netifaces.AF_INET][1]
        addr_info = netifaces.ifaddresses(iface)[netifaces.AF_INET][0]
        ip = addr_info['addr']
        return ip
