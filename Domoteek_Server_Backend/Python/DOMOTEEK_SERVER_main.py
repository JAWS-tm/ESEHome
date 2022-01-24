from multiprocessing import dummy
import sys
from data_communication.FrameParser import FrameParser
from config.app_config import logger
from db.dbRequest import dbRequest
from dbProcess.dbMessage import dbMessage
import datetime
from config.app_config import UART_CONFIG
from data_communication.UartController import UartController

if __name__ == "__main__":
    logger.debug("-------------------Starting application-------------------")
    db = dbRequest()
    #TEMPORAIRE - Test de message en attendant le code et décode
    dummy_message = "BA1000000002EEEEEE00A2420508CAFEDECADA"#String
    dummy_parse = FrameParser(dummy_message)
    dummy_parse.msgParsed()
    #Ajout d'un message dans la table message
    message2pierre = dbMessage(db, dummy_parse.id, dummy_parse.param_color+dummy_parse.data, datetime.datetime.now() ,True)
    message2pierre.objectTX2DB()
    #Suppression d'un message de la table message
    # messageremove = 
    sys.exit(1)
    # '''Sous main pour l'uart'''
    # print("Starting UART Test")
    # uart_controller = UartController(UART_CONFIG)
    # while True :
    #     incoming_msg = uart_controller.get_last_message()
    #     if(incoming_msg!=0):
    #         print("INCOMING MSG FROM UART : "+incoming_msg)

main()





