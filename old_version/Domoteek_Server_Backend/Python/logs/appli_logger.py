import logging

#Logging filters :
#DEBUG  Detailed information, typically of interest only when diagnosing problems.
#INFO   Confirmation that things are working as expected.
#WARNING    An indication that something unexpected happened, or indicative of some problem in the near future (e.g. ‘disk space low’). The software is still working as expected.
#ERROR  Due to a more serious problem, the software has not been able to perform some function.
#CRITICAL   A serious error, indicating that the program itself may be unable to continue running.

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
        self.file_handler = logging.FileHandler('logs/'+str(fileName))
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
