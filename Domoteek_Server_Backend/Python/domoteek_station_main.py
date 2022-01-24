import sys
from config.app_config import logger
from data_communication.FrameParser import *
from db.dbRequest import dbRequest
from dbProcess.dbMessage import dbMessage
import datetime

def main():
    logger.debug("-------------------Starting application-------------------")
    db = dbRequest()
    #TEMPORAIRE - Test de message en attendant le code et décode

    #Ajout d'un message dans la table message
    message2pierre = dbMessage(db, 2, "zoubizoubizou", datetime.datetime.now() ,True)
    message2pierre.objectTX2DB()

    #Suppression d'un message de la table message

    # messageremove = 
    sys.exit(1)


    dummy_message = "BA1000000002EEEEEE00A2420508CAFEDECADA"#String
    #parsed_message = FrameParser()

main()





