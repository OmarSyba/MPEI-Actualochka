rmdir /S /Q __pycache__
rmdir /S /Q dist
rmdir /S /Q build
rmdir /S /Q bin

pip freeze > requirements.txt
python -m venv uninstall

uninstall\Scripts\activate.bat
pip install -r requirements.txt && pyinstaller -w --onefile --hidden-import tkinter --paths uninstall\Lib\site-packages uninstall.py -i resources\favicon.ico && deactivate.bat
xcopy /E /I dist\uninstall bin\

rmdir /S /Q __pycache__
rmdir /S /Q dist
rmdir /S /Q build
erase /A *.spec