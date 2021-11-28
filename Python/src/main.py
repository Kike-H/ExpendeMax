from modules.Alfa.alfa import Alfa
import threading
import sys

alfa = Alfa()

if __name__ == "__main__":
    try:
        thread = threading.Thread(target=alfa.reciveData)
        thread.daemon = True
        thread.start()
        alfa.sendData()
    except KeyboardInterrupt:
        alfa.stop()
        sys.exit(0)
