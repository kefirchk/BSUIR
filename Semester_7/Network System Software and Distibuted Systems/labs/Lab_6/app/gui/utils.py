import tkinter as tk

from app.services import Chat


def update_users_list(users_listbox: tk.Listbox, chat: Chat):
    users_listbox.delete(0, tk.END)
    room = chat.rooms[chat.current_user.room_no]
    for user in room.users:
        users_listbox.insert(tk.END, f"{user.username} | {user.ip}")