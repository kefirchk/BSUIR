from enum import Enum


class PacketType(str, Enum):
    COMMAND = "COMMAND"
    OTHER = "OTHER"
