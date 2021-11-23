import sqlite3

class DB:

    def __init__(self):
        self.__connection = sqlite3.connect("./database/database.db")
        self.__cursor = self.__connection.cursor()

    def getPriceByID(self, code:str) -> int:
        return ((self.__cursor.execute('SELECT price FROM Products WHERE id=:code', {"code":code})).fetchall()[0])[0]

