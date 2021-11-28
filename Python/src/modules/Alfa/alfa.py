from modules.Automata.auto_code import nfa
from modules.Database.database import DB
import serial
import os

class Alfa(object):

    """This class implements the methods for used to the expden machine work well."""

    def __init__(self):
        self.__nfa = nfa
        self.__db = DB()
        self.__dev = serial.Serial("/dev/cu.usbserial-14210", 9600)
        self.__balance = 0
        self.__actual_price = 0

    def reciveData(self) -> None:
        while True:
            self.__balance = int(self.__dev.readline().decode('ascii'))
            print(self.__balance)

    def __checkPrice(self,code:str) -> bool:
        self.__actual_price = self.__db.getPriceByID(code)
        return True if self.__balance >= self.__actual_price else False

    def __checkCode(self, code:str) -> bool:
        return self.__nfa.accepts_input(code)

    def __clearConsole(self) -> None:
        commad = 'cls' if os.name in ('nts', 'dos') else 'clear'
        os.system(commad)
    
    def sendData(self):
        while True:
            message = "change is "
            key = "rejected"
            code = input()
            self.__clearConsole()
            if(self.__checkCode(code)):
                if(self.__checkPrice(code)):
                    money = self.__balance - self.__actual_price
                    message += str(money)
                    self.__balance = 0
                    self.__actual_price = 0
                    key = "accepted"
                else:
                    message = "not enf money"
            else:
                message = "code rejected"
            data = "{key}:{message}".format(key=key, message=message)
            self.__dev.write(data.encode('ascii'))
