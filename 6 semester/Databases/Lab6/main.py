import database as db
import mainwindow as mw
from tkinter import messagebox

try:
    postgresql = db.Database()
    postgresql.mainloop()
    if db.connection == None:
        exit()
    
    app = mw.MainWindow(postgresql)
    app.mainloop()
 
except Exception:
    messagebox.showerror(title="Error", message="Error while working with PostgreSQL")
