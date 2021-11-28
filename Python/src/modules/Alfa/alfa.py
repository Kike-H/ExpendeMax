from modules.Automata.auto_code import nfa
from modules.MachineT.machine_t import dtm
from modules.Database.database import DB
from typing import Iterable
import serial
import os

class Alfa(object):

    """This class implements the methods for used to the expden machine work well."""

    def __init__(self):
        self.__nfa = nfa
        self.__dtm = dtm
        self.__db = DB()
        self.__dev = serial.Serial("/dev/cu.usbserial-14210", 9600)
        self.__balance = 0
        self.__actual_price = 0

    def reciveData(self) -> None:
        while True:
            self.__balance = int(self.__dev.readline().decode('ascii'))

    def __isBalanceHigh(self,code:str) -> bool:
        self.__actual_price = self.__db.getPriceByID(code)
        return True if self.__balance > self.__actual_price else False
    
    def __isBalanceEqual(self, code:str) -> bool:
        self.__actual_price = self.__db.getPriceByID(code)
        return True if self.__balance == self.__actual_price else False

    def __checkCode(self, code:str) -> bool:
        return self.__nfa.accepts_input(code)

    def __clearConsole(self) -> None:
        commad = 'cls' if os.name in ('nts', 'dos') else 'clear'
        os.system(commad)
    
    def __encode(self, num:int) -> str:
        value = ""
        index = 0
        while index < num:
            index += 1
            value += '1'
        return value

    def __decode(self, arr:Iterable) -> int:
        num = 0
        for c in arr:
            num += 1 if c == "1" else 0
        return num

    def __giveChange(self) -> str:
        balance = self.__encode(self.__balance)
        price = self.__encode(self.__actual_price)
        stri = "{0}M{1}".format(price, balance)

        arr = ((self.__dtm.read_input(stri)).tape).tape

        return str(self.__decode(arr))


    def sendData(self):
        while True:
            print("Quit: Ctrl+C")
            message = "change is "
            key = "rejected"
            code = input()
            self.__clearConsole()
            if(self.__checkCode(code)):
                if(self.__isBalanceHigh(code)):
                    message += self.__giveChange()
                    self.__balance = 0
                    self.__actual_price = 0
                    key = "accepted"
                elif(self.__isBalanceEqual(code)):
                    self.__balance = 0
                    self.__actual_price = 0
                    key = "accepted"
                    message = "Thanks"
                else:
                    message = "not enf money"
            else:
                message = "code rejected"
            data = "{key}:{message}".format(key=key, message=message)
            self.__dev.write(data.encode('ascii'))
