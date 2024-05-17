from tkinter import *
from tkinter import ttk
from tkinter import messagebox
import database as db
import query_generator as qgen


class TableWindow(Tk):
    def __init__(self, database, table_name):
        super().__init__()
        self.option_add("*tearOff", FALSE)
        self.table_name = table_name
        self.database = database

        data, column_names = database.get_table(table_name)
        self.table_data = data
        self.column_names = column_names

        self.title(table_name)
        self.geometry("600x400")
        self.resizable(False, False)

        table_menu = Menu(self)
        edit_menu = Menu(self)
        edit_menu.add_command(label="Insert", command=lambda name=table_name: self.edit_table("INSERT"))
        edit_menu.add_command(label="Delete", command=lambda name=table_name: self.edit_table("DELETE"))
        edit_menu.add_command(label="Update", command=lambda name=table_name: self.edit_table("UPDATE"))
        edit_menu.add_command(label="Truncate", command=lambda name=table_name: self.edit_table("TRUNCATE"))
        table_menu.add_cascade(label="Edit", menu=edit_menu)
        self.config(menu=table_menu)

        table = ttk.Treeview(self, columns=column_names, show="headings", height=20)

        table_yscrollbar = ttk.Scrollbar(self, orient="vertical", command=table.yview)
        table_xscrollbar = ttk.Scrollbar(self, orient="horizontal", command=table.xview)
        table_yscrollbar.pack(side=RIGHT, fill=Y)
        table_xscrollbar.pack(side=BOTTOM, fill=X)
        table["yscrollcommand"]=table_yscrollbar.set
        table["xscrollcommand"]=table_xscrollbar.set

        if not data:
            label = Label(self, text="No data in the table")
            label.pack()
        else:
            for col in column_names:
                table.heading(col, text=col)
                table.column(col, stretch=True)
        
            for row in data:
                table.insert('', 'end', values=row)

        table.pack(fill="both")


    def edit_table(self, command):
        if command == "TRUNCATE":
            with db.connection.cursor() as cursor:
                query = f"TRUNCATE TABLE main_scheme.{self.table_name} CASCADE;"
                cursor.execute(query)
                messagebox.showinfo(title="Information", message="Query executed successfully!")
                return

        edit_window = Tk()
        edit_window.title(command + " " + self.table_name)
        edit_window.geometry("350x350")

        i = 0
        entries = []
        labels = []
        for column_name in self.column_names:
            if column_name == 'id' and command == "INSERT":
                continue
            label = Label(edit_window, text=column_name)
            entry = Entry(edit_window, width=30)
            entries.append(entry)
            labels.append(label['text'])
            label.grid(row = i, column=0, sticky="e", padx=10, pady=10)
            entry.grid(row = i, column=1, pady=10)
            i += 1
        button = ttk.Button(edit_window, text=command, width=30, command=lambda: self.edit(command, labels, entries))
        button.grid(row = i, column=1, pady=10)

        edit_window.mainloop()


    def edit(self, command, labels, entries):
        values = []
        for field in entries:
            values.append(field.get())

        print(f"Values: {values}")
            
        query_generator = qgen.QueryGenerator()

        try:    
            if command == "INSERT":
                query = query_generator.generate_insert_query(table_name=self.table_name, column_names=labels, entries=values)
                print(query)
                with db.connection.cursor() as cursor:
                    cursor.execute(query)
                
            elif command == "DELETE":
                query = query_generator.generate_delete_query(self.table_name, column_names=labels, entries=values)
                print(query)
                with db.connection.cursor() as cursor:
                    cursor.execute(query)

            elif command == "UPDATE":
                query = query_generator.generate_update_query(self.table_name, column_names=labels, entries=values)
                print(query)
                with db.connection.cursor() as cursor:
                    cursor.execute(query)
            
            messagebox.showinfo(title="Information", message="Query completed successfully!")

        except Exception as _ex:
            messagebox.showerror("Error", f"Wrong {command} query: {_ex}")
        