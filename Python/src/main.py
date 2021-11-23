from modules.automata.AutoCode import nfa
from modules.Database.database import DB
import os
import serial.tools.list_ports

db = DB()

def main():
    while True:
        code = input()
        os.system('clear')
        if nfa.accepts_input(code):
            print(db.getPriceByID(code))


def main2():
    for port in serial.tools.list_ports.comports():
        print(port)

if __name__ == "__main__":
    main2()
