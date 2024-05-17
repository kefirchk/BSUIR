from config import TABLE_NAMES
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import filedialog
import tablewindow as tw
import database as db
import os

EXAMPLES_PATH = "./sql_scripts/examples/"

class MainWindow(Tk):
    def __init__(self, database):
        super().__init__()
        self.my_db = database
        self.title("Database Manager")
        self.geometry("440x350+540+220")
        self.resizable(False, False)
        self.option_add("*tearOff", FALSE)

        editor = Text(wrap = "none", height=20, width=50)
        editor.grid(column = 0, row = 0, sticky = NSEW)
        ys = ttk.Scrollbar(orient = "vertical", command = editor.yview)
        ys.grid(column = 1, row = 0, sticky = NS)
        xs = ttk.Scrollbar(orient = "horizontal", command = editor.xview)
        xs.grid(column = 0, row = 1, sticky = EW)
        editor["yscrollcommand"] = ys.set
        editor["xscrollcommand"] = xs.set
        editor.insert("1.0", "Enter your query...")

        main_menu = Menu()
        table_menu = Menu()
        query_menu = Menu()

        for table_name in TABLE_NAMES:
            table_menu.add_command(label=table_name, command=lambda name=table_name: self.show_table(name))
        main_menu.add_cascade(label="Tables", menu=table_menu)
        
        query_menu.add_command(label="Execute", command=lambda: self.execute_query(editor.get('1.0', 'end')))
        query_menu.add_command(label="Execute from file", command=self.execute_query_from_file)
        query_menu.add_command(label="Clean", command=lambda: editor.delete('1.0', 'end'))
        query_menu.add_command(label="Examples", command=self.show_query_examples)
        main_menu.add_cascade(label="Query", menu=query_menu)

        self.config(menu=main_menu)

        
    def show_table(self, table_name):
        table_window = tw.TableWindow(database=self.my_db, table_name=table_name)
        table_window.mainloop()

    
    def execute_query(self, query):
        try:
            cursor = db.connection.cursor()
            cursor.execute(query)

            if "SELECT".lower() not in query.lower():
                messagebox.showinfo(title="Information", message="Query executed successfully!")
                return 
            
            rows = cursor.fetchall()
            column_names = [desc[0] for desc in cursor.description]
            
            result_window = Tk()
            result_window.option_add("*tearOff", FALSE)
            result_window.title("Query Result")
            result_window.geometry("600x400")
            result_window.resizable(False, False)

            result_table = ttk.Treeview(result_window, columns=column_names, show="headings", height=20)

            table_yscrollbar = ttk.Scrollbar(result_window, orient="vertical", command=result_table.yview)
            table_xscrollbar = ttk.Scrollbar(result_window, orient="horizontal", command=result_table.xview)
            table_yscrollbar.pack(side=RIGHT, fill=Y)
            table_xscrollbar.pack(side=BOTTOM, fill=X)
            result_table["yscrollcommand"]=table_yscrollbar.set
            result_table["xscrollcommand"]=table_xscrollbar.set

            if not rows:
                label = Label(result_window, text="No data in the table")
                label.pack()
            else:
                for col in column_names:
                    result_table.heading(col, text=col)
                    result_table.column(col, stretch=True)
        
                for row in rows:
                    result_table.insert('', 'end', values=row)

            result_table.pack(fill="both")
            messagebox.showinfo(title="Information", message="Query executed successfully!")
            result_window.mainloop()

        except Exception as _ex:
           messagebox.showerror(title="Error", message=f"Wrong query: {_ex}")
        
        finally:
           cursor.close()


    def execute_query_from_file(self):
        filepath = filedialog.askopenfile(title="Execute SQL-script")
        if filepath.name != "":
            with open(filepath.name, "r", encoding="utf-8") as file:
                text = file.read()
                self.execute_query(text)


    def show_query_examples(self):
        examples_window = Tk()
        examples_window.option_add("*tearOff", FALSE)
        examples_window.title("Query List")
        examples_window.geometry("600x400")
        examples_window.resizable(False, False)

        query_list = Listbox(examples_window, selectmode=SINGLE, height=22)

        info_button = ttk.Button(examples_window, text="Info", width=30, command=lambda: self.show_script_info(query_list))
        exec_button = ttk.Button(examples_window, text="Execute", width=30, command=lambda: self.execute_example(query_list))
        info_button.place(x=70, y=10)
        exec_button.place(x=320, y=10)

        list_yscrollbar = ttk.Scrollbar(examples_window, orient="vertical", command=query_list.yview)
        list_yscrollbar.pack(side='right', fill='y')
        query_list["yscrollcommand"]=list_yscrollbar.set

        file_names = []
        with os.scandir(EXAMPLES_PATH) as entries:
            for entry in entries:
                if entry.is_file():
                    file_names.append(entry.name)

        for name in file_names:
            query_list.insert("end", name)

        query_list.pack(fill='both', side="bottom")
        examples_window.mainloop()
    

    def show_script_info(self, query_list):
        selected_query_index = query_list.curselection()
        if len(selected_query_index) != 0:
            selected_query_name = query_list.get(selected_query_index[0])  

            info_window = Tk()
            info_window.option_add("*tearOff", FALSE)
            info_window.title(f"Info about {selected_query_name}")
            info_window.geometry("440x350")
            info_window.resizable(False, False)

            info = Text(info_window, wrap = "none", height=20, width=50)
            info.grid(column = 0, row = 0, sticky = NSEW)
            ys = ttk.Scrollbar(info_window, orient = "vertical", command = info.yview)
            xs = ttk.Scrollbar(info_window, orient = "horizontal", command = info.xview)
            ys.grid(column = 1, row = 0, sticky = NS)
            xs.grid(column = 0, row = 1, sticky = EW)
            info["yscrollcommand"] = ys.set
            info["xscrollcommand"] = xs.set

            with open(EXAMPLES_PATH + selected_query_name, "r", encoding="utf-8") as file:
                text = file.read()
                info.insert('1.0', text)
                info['state']='disabled'


    def execute_example(self, query_list):
        selected_query_index = query_list.curselection()
        if len(selected_query_index) != 0:
            selected_query_name = query_list.get(selected_query_index[0])  
            with open(EXAMPLES_PATH + selected_query_name, "r", encoding="utf-8") as file:
                text = file.read()
                self.execute_query(text)