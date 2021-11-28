from modules.Alfa.alfa import Alfa
import threading

alfa = Alfa()

if __name__ == "__main__":
    thread = threading.Thread(target=alfa.reciveData)
    thread.start()
    alfa.sendData()
