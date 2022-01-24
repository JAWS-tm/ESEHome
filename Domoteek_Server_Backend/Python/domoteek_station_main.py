from multiprocessing import dummy
import sys
from data_communication.FrameParser import FrameParser
from config.app_config import logger
from db.dbRequest import dbRequest
from dbProcess.dbMessage import dbMessage
import datetime

def main():
    logger.debug("-------------------Starting application-------------------")
    db = dbRequest()
    #TEMPORAIRE - Test de message en attendant le code et décode
    dummy_message = "BA1000000002EEEEEE00A2420508CAFEDECADA"#String
    dummy_parse = FrameParser(dummy_message)
    dummy_parse.msgParsed()
    #Ajout d'un message dans la table message
    message2pierre = dbMessage(db, dummy_parse.receiver, dummy_parse.emmiter ,dummy_parse.id, dummy_parse.param_color, dummy_parse.data, datetime.datetime.now() ,True)
    message2pierre.objectTX2DB()

    #Suppression d'un message de la table message
    
    
    # messageremove = 
    sys.exit(1)


    

main()





