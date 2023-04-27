########################
# MainURC : 
#			Ce main comprend les composantes suivantes : 
#				UART
#				Réponse
#				Chiffrement	
########################

#import
import json
import logging
from multiprocessing import RLock
from Data_base.MariadB_Connect import MariaDBConnect
from Data_comm.mainURC import mainURC
import time
from serial.tools.list_ports import comports
from Data_comm.UartController import UartController
from Data_comm.FrameParser import FrameParser
from Data_base.Receive_write import Receive_write

#main
##  Here, we call class and others                  DO AT THE END
##  
port_serial = ""


## Find serial port who's open
def get_port_serial_open():
    connected = []
    try:
        for element in comports():
            connected.append(element.name)
        global port_serial
        port_serial = str(connected).split("'")[1]
        print("port_serial :",port_serial)
        return port_serial
    except IndexError as e:
        print("Il se peut qu'aucun port serie ne soit connecte")
        time.sleep(5)
        print("get_port_serial_open() error : ", e)
        # exit()
        return 0

## Créer les fichiers de log de l'application
class AppliLogger():
    '''Attributes'''
    logger = None
    file_handler = None
    formatter = None
    '''Constructor'''
    def __init__(self, fileName, filter, format):
        self.logger = logging.getLogger(fileName)
        if(filter == "DEBUG"):
            self.logger.setLevel(logging.DEBUG)
        elif(filter == "INFO"):
            self.logger.setLevel(logging.INFO)
        elif(filter == "WARNING"):
            self.logger.setLevel(logging.WARNING)
        elif(filter == "ERROR"):
            self.logger.setLevel(logging.ERROR)
        elif(filter == "CRITICAL"):
            self.logger.setLevel(logging.CRITICAL)
        else :
            self.logger.setLevel(logging.WARNING) #Default
        if(format == "default"):
            self.formatter = logging.Formatter('%(asctime)s:%(name)s:%(levelname)s:%(message)s')
        else :
            self.formatter = logging.Formatter(format)
        self.file_handler = logging.FileHandler('Logs/'+str(fileName))
        self.file_handler.setFormatter(self.formatter)
        self.logger.addHandler(self.file_handler)
        self.logger.propagate = False #Don't affect the root logger (True -> logs will apear in the console via the root logger)
        
    def debug(self, message):
        self.logger.debug(message)

    def info(self, message):
        self.logger.info(message)
    
    def warning(self, message):
        self.logger.warning(message)

    def error(self, message):
        self.logger.error(message)
    
    def critical(self, message):
        self.logger.critical(message)

# Va récupérer les infos de config dans le fichier config.json
class config (object):
    get_port_serial_open()
    try: 
        CONFIG = {}
        with open('config.json', "r") as jsonFile:
            CONFIG = json.load(jsonFile)
            jsonFile.close()
        DATA_COMMUNICATION_CONFIG = CONFIG["data_communication"]
        DB_CONFIG = CONFIG["DB"]
        UART_CONFIG = CONFIG["data_communication"]["UART"]
        ## global = variable global
        global port_serial
        UART_CONFIG["port"] = port_serial
        
        logger = AppliLogger(CONFIG["logs"]["fileName"],CONFIG["logs"]['filter'],CONFIG["logs"]['format'])
    except Exception as e:
        print("Error config :", str(e))


class mainClass (object):
    def __init__ (self):
        # On lancera ici le Data_base_main.py et le Data_comm_main.py en multiprocessing

        # Receive_write(FrameParser.tram_dico)
        
        uart_controller = UartController(config.UART_CONFIG)


        while True:
            
            last_message = uart_controller.get_last_message()
            if (last_message != 0): # 
                print("reception du message dans le main : ",last_message)   

            last_dico = uart_controller.get_last_dico()
            if (last_message != 0): # 
                print("reception du dico dans le main : ",last_dico)   

                
    
def mainURC(dic = {}, lock = RLock()):
    config.logger.info("-------------------Starting application-------------------")

        # Config : donnéees, mpd, port... pour DATA_COMMUNICATION, DB et UART
    config()
    config.logger.info("-----------------------Config : ok------------------------")

    # MariaDb init : create database and tables, if not exists
    MariaDBConnect(config.DB_CONFIG)
    config.logger.info("-----------------------MariaDB : ok-----------------------")

    if(get_port_serial_open() != 0):
        mainClass()
    
    if(get_port_serial_open() == 0):
        get_port_serial_open



if __name__ == "__main__":
    mainURC()