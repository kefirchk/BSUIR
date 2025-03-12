from pydantic import BaseModel

from .user import User
from .packet_type import PacketType


class Packet(BaseModel):
    packet_type: PacketType
    source: User = None
    payload: dict
