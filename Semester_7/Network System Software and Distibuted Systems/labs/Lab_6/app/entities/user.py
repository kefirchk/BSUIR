from pydantic import BaseModel


class User(BaseModel):
    ip: str
    username: str
    room_no: int
