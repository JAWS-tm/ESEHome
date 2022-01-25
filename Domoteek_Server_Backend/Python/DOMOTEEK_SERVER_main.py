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
    logger.debug("-------------------Starting application-------------------")
    # #TEMPORAIRE - Test de message en attendant le code et décode
    # dummy_message = "BA1000000002EEEEEE00A2420508CAFEDECADA"#String
    # dummy_parse = FrameParser(dummy_message)
    # dummy_parse.msgParsed()
    # #Ajout d'un message dans la table message
    # message2pierre = dbMessage(db, dummy_parse.receiver, dummy_parse.emmiter ,dummy_parse.id, dummy_parse.param_color, dummy_parse.data, datetime.datetime.now() ,True)
    # message2pierre.objectTX2DB()
    '''MAIN'''
    #Init values
    db = dbRequest()
    uart_controller = UartController(UART_CONFIG)
    #Boucle de fond
    while True :
        try :
            incoming_msg = uart_controller.get_last_message()
            if(incoming_msg!=0):
                print("INCOMING MSG FROM UART : "+incoming_msg)
                parsed_message = FrameParser(incoming_msg)
                parsed_message.msgParsed()
                message2pierre = dbMessage(db, parsed_message.getReceiver(), parsed_message.getEmitter() , parsed_message.getId(), parsed_message.getParamID(), parsed_message.getData(), datetime.datetime.now() ,True)
                message2pierre.objectTX2DB()
        except Exception as e :
            print("ERROR : There was an error processing incoming messages")
            print(str(e))
            traceback.print_exc()
            sys.exit(1)






