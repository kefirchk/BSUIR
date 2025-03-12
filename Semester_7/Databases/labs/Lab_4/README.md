# School Management System
___

## Table of Contents

- [Overview](#overview)
- [Technologies](#technologies)
- [Features](#features)
- [Database Schema](#database-schema)
- [Installation](#installation)
- [Usage](#usage)
   - [Main Window](#main-window)
   - [Table Window](#table-window)
   - [Edit Window](#edit-window)
   - [Quick Keyboard Shortcuts](#quick-keyboard-shortcuts)
- [License](#license)

## Overview
___

This is a **School Management System** built using Python, Tkinter, and SQLAlchemy.
The application provides a graphical user interface (GUI) for managing students,
teachers, classes, and subjects within a school. The system supports functionalities
for creating, updating, and deleting records from a database while maintaining data
consistency and integrity.

## Technologies
___

- **Python** (3.11+)
- **Tkinter** for GUI
- **SQLAlchemy** for ORM and database management
- **PostgreSQL** (or any compatible relational database)

## Features
___

- ✅**CRUD Operations**: Create, read, update, and delete records for students, teachers, classes, and subjects.
- ✅**User-friendly GUI**: Developed using Tkinter for easy interaction with the database.
- ✅**Data Validation**: Ensures data integrity through the use of SQLAlchemy models and database constraints.
- ✅**Hotkeys for Navigation**: Quickly navigate through input fields and buttons using keyboard shortcuts.
- ✅**Error Handling**: Graceful error handling with rollback for database transactions in case of integrity violations.
- ✅**Custom Focus Control**: Focus on specific input elements (e.g., text fields, buttons) using customizable hotkeys for streamlined data entry.


## Database Schema
___

![Database Schema](docs/database_design.png)


## Installation
___

```bash
  sudo apt-get install libdb-dev
  sudo apt install libpython3.11-dev
  sudo apt install python3-tk
```

1. Create a virtual environment and activate it:
    ```bash
    python -m venv venv
    source venv/bin/activate  # On Windows: venv\Scripts\activate
    ```

2. Install the required dependencies:
    ```bash
    pip install -r app/requirements.txt
    ```

3. Create a **.env** files in the project directory and fill it with your data:

```.env
# .env

DB_HOST                     - ip address of your database (e.g. localhost)
DB_PORT                     - port of database (e.g. 5432)
DB_USER                     - user name (owner) of database (e.g. postgres)
DB_PASS                     - password for access to database (e.g. 1234)
DB_NAME                     - database name (e.g. cleanbuy)
```

## Usage
___

### Main Window

---

The main window of the application provides access to the core functions for working with the database. Upon opening, it automatically establishes a connection to the database if the environment variables are pre-configured.

#### Main Menus

The application provides access to two main menus: **TableMenu** and **QueryMenu**.

###### *1. TableMenu*
This menu is used for working with database tables:
- **Focus**: To focus on this menu, use the **CTRL+T** keyboard shortcut.
- **Opening a Table**: Navigate through the tables using the arrow keys. To open a table, select it and press **Enter**.

###### *2. QueryMenu*
This menu is designed for executing SQL queries:
- **Focus**: Press **CTRL+Q** to activate this menu.
- **Modes of Operation**:
  - **Interactive Mode**: Allows you to write an SQL query manually in the **Editor** widget.
    - **Focus on Editor**: Use **CTRL+E** to focus on the Editor.
  - **Batch Mode**: Executes an SQL script from a file selected by the user (**Execute from file**).
- **Executing a Query**: Choose the **Execute** option to run the query. The result may be displayed in a separate window.

###### *3. Quick Closing*
- Press **ESC** to close the **MainWindow**. All child windows will automatically close along with it.


### Table Window

---

This window is used to display records from database tables. Fields that are primary keys or foreign keys are hidden for better clarity.

#### Working with Records

###### *1. Focusing on a Record*
- **Focus**: Press **CTRL+T** to set the focus on the first row of the table.
- **Navigating through Rows**: Use the **Up/Down** arrow keys to move between rows.
- **Horizontal Scrolling**: If the table data doesn't fit within the window, use the **Left/Right** arrow keys to scroll horizontally.

###### *2. Viewing Related Records*
- Press **Enter** on the desired record to open additional windows showing related data from other tables.

#### EditMenu

This menu allows you to add, update, or delete records from the table:

- **Focus**: Press **CTRL+E** to switch to this menu.
- **Available Actions**:
  - **Update Record (UPDATE)**: Select the row you want to update.
  - **Add Record (INSERT)**: No need to focus on any specific row for this action.
  - **Delete Record (DELETE)**: Focus on the desired row before deleting. To update the opened table you must close *TableWindow*.

#### Switching Windows

- To switch back to **MainWindow**, press **CTRL+Tab**.
- To return to **TableWindow**, press **CTRL+Tab** again.

#### Closing the Window
- Press **ESC** to close **TableWindow**.


### Edit Window

---

The **EditWindow** is used to add or update records from the selected table.

#### Modes of Operation

###### *1. Insert Mode (INSERT)*
- If **INSERT** was selected in **TableWindow**, the window will open with empty fields for entering data. Some fields may be pre-filled with default values.

###### *2. Update Mode (UPDATE)*
- If **UPDATE** was selected, the fields will be populated with the current values of the selected record.

#### Interacting with Elements

- **Focus on Input Fields**: Use **CTRL+F** to toggle between input fields.
- **Focus on Buttons**: Press **CTRL+B** to focus on add/remove buttons for list elements.
- **Confirm Action**: Press **Enter** to activate the selected button.
- **Save Record**: Use **CTRL+S** to update or add a record.

#### Closing the Window
- Press **ESC** to close **EditWindow**.

#### Switching Between Windows
- Use **CTRL+Tab** to switch between open windows.

### Quick Keyboard Shortcuts

---
| Shortcut          | Action Description                                  |
| ----------------- | -------------------------------------------------- |
| **CTRL+T**        | Focus on **TableMenu** or a table row               |
| **CTRL+Q**        | Focus on **QueryMenu**                              |
| **CTRL+E**        | Focus on **Editor** or **EditMenu**                 |
| **CTRL+F**        | Focus on input fields in **EditWindow**             |
| **CTRL+B**        | Focus on buttons in **EditWindow**                  |
| **CTRL+S**        | Save the record in **EditWindow**                   |
| **CTRL+Tab**      | Switch between open windows                         |
| **ESC**           | Close the current window                            |


## License
___

This project is licensed under the MIT License.\
Designed by __Alexey Klimovich__, 2024
