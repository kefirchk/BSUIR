import psycopg2
from config import HOST, USER, DB_NAME
from tkinter import *
from tkinter import ttk
from tkinter import messagebox

connection = None

class Database(Tk):
    def __init__(self):
        super().__init__()
        
        self.title("Connect to Server")
        self.geometry("400x150+540+320")
        self.resizable(False, False)
        self.option_add("*tearOff", FALSE)

        password_label = Label(text="Please enter the password for the user 'postgres' to connect the server - PostgreSQL 16",
                           font=("Arial", 12),
                           wraplength=300)
        password_label.pack()

        password_entry = ttk.Entry(show='•')
        password_entry.pack()

        password_button = ttk.Button(text="OK", command=lambda: self.on_password_button_click(password_entry))
        password_button.pack()


    def __del__(self):
        if connection != None:
            connection.close()
            print("[" + "\033[32m{}".format("INFO") + "\033[37m{}".format("] PostgreSQL connection closed"))


    def on_password_button_click(self, password_entry):
        global connection
        try:
            # connect to database
            connection = psycopg2.connect(
                host=HOST,
                user=USER,
                password=password_entry.get(),
                database=DB_NAME
            )
            connection.autocommit = True

            # the cursor for perfoming database operations
            with connection.cursor() as cursor:
                cursor.execute("SELECT version();")
                messagebox.showinfo(title="Information", message="Successful connection to:\n" + "".join(cursor.fetchone()))
            
            self.destroy()
            
        except Exception:
            messagebox.showerror(title="Error", message="Wrong password!")
    

    def get_table(self, table_name):
        rows = []
        column_names = []
        with connection.cursor() as cursor:
            query = f"SELECT * FROM main_scheme.{table_name};"
            cursor.execute(query)
            rows = cursor.fetchall()
            column_names = [desc[0] for desc in cursor.description]
        return rows, column_names