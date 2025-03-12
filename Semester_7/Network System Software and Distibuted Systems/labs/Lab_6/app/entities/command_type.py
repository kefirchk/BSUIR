from enum import Enum


class CommandType(str, Enum):
    PING = "PING"
    PONG = "PONG"
