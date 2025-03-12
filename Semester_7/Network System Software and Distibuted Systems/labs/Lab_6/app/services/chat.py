from datetime import datetime
from getpass import getuser

from app.config import PUBLIC_ROOM_IP
from app.entities import Message, User, Packet, PacketType, Room
from .network_manager import NetworkManager


class Chat:
    def __init__(self, network_manager: NetworkManager):
        self.network_manager = network_manager
        self.ip = self.network_manager.get_network_params()
        self.current_user = User(ip=self.ip, username=getuser(), room_no=0)
        self.rooms = [
            Room(room_no=0, room_ip=PUBLIC_ROOM_IP, users=[self.current_user])
        ]

    def send_message(self, message: str):
        packet = Packet(
            packet_type=PacketType.OTHER,
            source=self.current_user,
            payload={
                "message": Message(
                    context=message,
                    timestamp=datetime.now().strftime('%Y-%m-%d %H:%M:%S'),
                ).dict()
            }
        )
        self.network_manager.send_packet(packet)
        return packet
