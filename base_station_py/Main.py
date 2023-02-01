<<<<<<< HEAD
#import
import json
import logging
from Data_base.MariadB_Connect import MariaDBConnect
import multiprocessing
from multiprocessing import Queue

#main
##  Here, we call class and others                  DO AT THE END
##  

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
    try: 
        CONFIG = {}
        with open('config.json', "r") as jsonFile:
            CONFIG = json.load(jsonFile)
            jsonFile.close()

        DATA_COMMUNICATION_CONFIG = CONFIG["data_communication"]
        DB_CONFIG = CONFIG["DB"]
        UART_CONFIG = CONFIG["data_communication"]["UART"]
        logger = AppliLogger(CONFIG["logs"]["fileName"],CONFIG["logs"]['filter'],CONFIG["logs"]['format'])
    except Exception as e:
        print("Error config :", str(e))


class mainClass (object):
    def __init__ (self):
        print("Main class ")
        # On lancera ici le Data_base_main.py et le Data_comm.py en multiprocessing

if __name__ == "__main__":

    # Config : donnéees, mpd, port... pour DATA_COMMUNICATION, DB et UART
    config()
    print("Config : OK")

    # MariaDb init : create database and tables, if not exists
    MariaDBConnect(config.DB_CONFIG)
    print("MariaDB : OK")

    mainClass()
=======
#import
import json
import logging
from Data_base.MariadB_Connect import MariaDBConnect

#main
##  Here, we call class and others                  DO AT THE END
##  

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
    try: 
        CONFIG = {}
        with open('config.json', "r") as jsonFile:
            CONFIG = json.load(jsonFile)
            jsonFile.close()

        DATA_COMMUNICATION_CONFIG = CONFIG["data_communication"]
        DB_CONFIG = CONFIG["DB"]
        UART_CONFIG = CONFIG["data_communication"]["UART"]
        logger = AppliLogger(CONFIG["logs"]["fileName"],CONFIG["logs"]['filter'],CONFIG["logs"]['format'])
    except Exception as e:
        print("Error config :", str(e))


class mainClass (object):
    def __init__ (self):
        print("Main class ")
        # On lancera ici le Data_base_main.py et le Data_comm.py en multiprocessing
        
        launch = True
        while launch:
            try:
                print("launch true")
            except Exception as e:
                print("Error main :", str(e))
            
            launch = False



if __name__ == "__main__":

    config.logger.info("-------------------Starting application-------------------")
    
    # Config : donnéees, mpd, port... pour DATA_COMMUNICATION, DB et UART
    config()
    config.logger.info("-----------------------Config : ok------------------------")

    # MariaDb init : create database and tables, if not exists
    MariaDBConnect(config.DB_CONFIG)
    config.logger.info("-----------------------MariaDB : ok-----------------------")


    mainClass()
>>>>>>> 9c9f1f97cbf1019a68a5fc30533f120b399640be
    