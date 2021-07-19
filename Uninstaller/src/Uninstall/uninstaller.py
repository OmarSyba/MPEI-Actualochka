import os
import winreg as wr

registry_key = "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
keyName = "Actualochka"

program_data = "C:\\ProgramData\\Actualochka"


class ActRemover:
    def remove_actualochka(self):
        # self.remove_from_registry()
        # self.remove_from_programdata()

        current_path = os.getcwd()

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
