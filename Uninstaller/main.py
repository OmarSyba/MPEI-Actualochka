from src.GUI.mainwindow import MainWindow
from src.Uninstall.uninstaller import ActRemover


def main():
    #window = MainWindow()
    act = ActRemover()
    act.remove_actualochka()


if __name__ == '__main__':
    main()