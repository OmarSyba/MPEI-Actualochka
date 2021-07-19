from tkinter import *
from tkinter import ttk
from tkinter import messagebox as ms


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
        self._upperLabel = Label(self._upFrame, text="\nUninstall Actualochka", bg="white", font=("Times New Roman", 11, "bold"))
        self._upperLabel.pack()
        self._upperLabelText = Label(self._upFrame, text="Remove Actualochka from your computer.\n\n", bg="white", font=("Times New Roman", 11))
        self._upperLabelText.pack()
        ############################################

        self._canvas = Canvas(self._upFrame, width=500, height=500, bg="white")
        self._canvas.pack()
        self._image = PhotoImage(file="resources/favicon.png")
        self._canvas.create_image(0, 0, anchor=CENTER, image=self._image)


        self._window.mainloop()

    def ask_to_uninstall(self):
        return ms.askyesno("Uninstall?", "Are you sure to remove all components?") == 'yes'
