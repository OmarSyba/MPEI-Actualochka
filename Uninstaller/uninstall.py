import os
import pathlib
import winreg as wr
import time

from tkinter import *
from tkinter import ttk
from tkinter import messagebox as ms

registry_key = "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
keyName = "Actualochka"

program_data = "C:\\ProgramData\\Actualochka"


class MainWindow:
    _window = Tk()

    def __init__(self):
        self._window.title("Uninstaller Actualochka")
        self._window.geometry('640x480')
        self._window.resizable(False, False)

        self._upFrame = Frame(self._window, height=100, width=640, bg="white")
        self._upFrame.pack(fill=BOTH, expand=False)

        ############################################
        # TODO                                     #
        # Need to fix separator between two Frames #
        self._sep = ttk.Separator(self._window, orient="horizontal")
        self._sep.pack(fill='x')
        # self.sep.grid(row=1, column=0)
        ############################################

        self._downFrame = Frame(self._window, height=600, width=640, bg="#c9c2c4")
        self._downFrame.pack(fill=BOTH, expand=False)
        # self.downFrame.grid(row=2, column=0)

        ############################################
        # TODO                                     #
        # Need to fix padding from upper frame     #
        self._upperLabel = Label(self._upFrame, text="\nUninstall Actualochka", bg="white",
                                 font=("Times New Roman", 11, "bold"))
        self._upperLabel.pack()
        self._upperLabelText = Label(self._upFrame, text="Remove Actualochka from your computer.\n\n", bg="white",
                                     font=("Times New Roman", 11))
        self._upperLabelText.pack()
        ############################################

        self._canvas = Canvas(self._upFrame, width=500, height=500, bg="white")
        self._canvas.pack()
        #self._image = PhotoImage(file="resources/favicon.png")
        #self._canvas.create_image(0, 0, anchor=CENTER, image=self._image)

        self._window.mainloop()

    def ask_to_uninstall(self):
        return ms.askyesno("Uninstall?", "Are you sure to remove all components?") == 'yes'


class ActRemover:
    def remove_actualochka(self):
        # self.remove_from_registry()
        # self.remove_from_programdata()

        current_path = os.path.basename(os.getcwd())
        fp = open("temporary_remover.bat", 'w')
        fp.write("for %%i in (*.*) do if not \"%%i\"==\"temporary_remover.bat\" del /q \"%%i\"")
        fp.write("\ndel /a /q *")
        fp.close()
        time.sleep(1)
        os.startfile("temporary_remover.bat")

    def remove_from_programdata(self):
        try:
            files = os.listdir(program_data)
            for x in files:
                os.remove(program_data + "\\" + x)
            os.rmdir(program_data)
        except OSError as e:
            print("Error: %s : %s" % (program_data, e.strerror))

    def remove_from_registry(self):
        try:
            key = wr.OpenKey(wr.HKEY_CURRENT_USER, registry_key, 0, wr.KEY_ALL_ACCESS)
            wr.DeleteValue(key, keyName)
            key.Close()
        except FileNotFoundError:
            print("--- Regedit doesn't contains Actualochka key")

def main():
    window = MainWindow()
    act = ActRemover()
    act.remove_actualochka()


if __name__ == '__main__':
    main()
