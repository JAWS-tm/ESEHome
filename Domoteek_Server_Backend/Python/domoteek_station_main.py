from config.app_config import logger
from data_communication.FrameParser import *
from BDD.MariaDB import *

def main():
    logger.debug("-------------------Starting application-------------------")
    connect()
    dummy_message = "BA1000000002EEEEEE00A2420508CAFEDECADA"#String
    #parsed_message = FrameParser()

main()