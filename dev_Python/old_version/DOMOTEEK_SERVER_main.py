import sys
import datetime
import traceback
import time
from multiprocessing import dummy
from FrameParser import FrameParser
from app_config import logger
from app_config import UART_CONFIG
from app_config import DB_CONFIG
from UartController import UartController
from DbController import DbController


if __name__ == "__main__":
    logger.info("-------------------Starting application-------------------")
    db_controller = DbController(DB_CONFIG)
    uart_controller = UartController(UART_CONFIG)
    while True :
        time.sleep(0.5)
        try :
            uart_incoming_msg = uart_controller.get_last_message()
            if(uart_incoming_msg!=0):
                logger.debug("INCOMING MSG FROM UART : "+str(uart_incoming_msg))
                parsed_message = FrameParser(uart_incoming_msg)
                parsed_message.msgParsed()
                logger.debug("Parsed message : "+str(parsed_message))
                #Send message to bdd (needs FrameParser msg type)
                db_controller.put_message_in_bdd_sending_queue(parsed_message)
            bdd_incoming_msg = db_controller.get_last_message()
            if(bdd_incoming_msg!=0):
                logger.debug("INCOMING MSG FROM BDD : "+str(bdd_incoming_msg))
                #Concat dégueu ==> should be FrameEncoder
                #ret=str(bdd_incoming_msg[0])+str(bdd_incoming_msg[1])+str(bdd_incoming_msg[2])+str(bdd_incoming_msg[3])+str(bdd_incoming_msg[4])+str(bdd_incoming_msg[5])
                #Send message to UART (needs str msg type)
                #uart_controller.put_message_in_uart_sending_queue(ret)
        except Exception as e :
            logger.error("ERROR : There was an error processing the incoming data. The message has been ignored")
            logger.error(str(e))
            #traceback.print_exc()
            #sys.exit(1)