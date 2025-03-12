from pydantic import BaseModel


class Message(BaseModel):
    context: str
    timestamp: str
