from multiprocessing import dummy
import sys
from data_communication.FrameParser import FrameParser
from config.app_config import logger
from db.dbRequest import dbRequest
from dbProcess.dbMessage import dbMessage
import datetime
from config.app_config import UART_CONFIG
from data_communication.UartController import UartController
import traceback

if __name__ == "__main__":
    logger.info("-------------------Starting application-------------------")
    #Init values
    db = dbRequest()
    uart_controller = UartController(UART_CONFIG)
    #Boucle de fond
    while True :
        try :
            incoming_msg = uart_controller.get_last_message()
            if(incoming_msg!=0):
                logger.debug("INCOMING MSG FROM UART : "+incoming_msg)
                parsed_message = FrameParser(incoming_msg)
                parsed_message.msgParsed()
                message2pierre = dbMessage(db, str(parsed_message.receiver), str(parsed_message.emitter) , str(parsed_message.id), str(parsed_message.param_id_e), str(parsed_message.data), datetime.datetime.now() ,True)
                message2pierre.objectTX2DB()
            uart_controller.send_new_message("Message sent from the main\n")
            #Rajouter ici le check des messages arrivant depuis la station de base vers les objets (emetteur)
        except Exception as e :
            logger.error("ERROR : There was an error processing the incoming data. The message has been ignored")
            logger.error(str(e))
            traceback.print_exc()
            #sys.exit(1)





