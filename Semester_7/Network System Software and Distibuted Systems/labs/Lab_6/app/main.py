import sys, os

project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.append(project_root)

from app.gui.main_window import MainWindow


if __name__ == "__main__":
    app = MainWindow()
    app.mainloop()
