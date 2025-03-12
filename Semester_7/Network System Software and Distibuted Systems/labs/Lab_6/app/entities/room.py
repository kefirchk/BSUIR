from pydantic import BaseModel
from typing import List

from app.entities import User


class Room(BaseModel):
    room_no: int
    room_ip: str
    users: List[User]
