from modules.automata.AutoCode import nfa
from modules.Database.database import DB
import threading
import serial
import os

dev = serial.Serial("/dev/cu.usbserial-1420", 9600)
aux = ''
money = 0
db = DB()

def getMoney() -> None:
    while True:
        print(dev.readline().decode('ascii'))

def main():
    while True:
        code = input()
        os.system('clear')
        if(nfa.accepts_input(code)):
            print(db.getPriceByID(code))


if __name__ == "__main__":
    thread = threading.Thread(target=getMoney)
    thread.start()
    main()
