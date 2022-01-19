from config.app_config import logger
from data_communication.FrameParser import *
from db.dbRequest import dbRequest

def main():
    logger.debug("-------------------Starting application-------------------")
    db = dbRequest()


    dummy_message = "BA1000000002EEEEEE00A2420508CAFEDECADA"#String
    #parsed_message = FrameParser()

main()





