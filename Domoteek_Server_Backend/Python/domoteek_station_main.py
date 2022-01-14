from config.data_communication_config import logger, DATA_COMMUNICATION_CONFIG
from data_communication import FrameParser

def main():
    print("Starting application")
    logger.debug("Starting application")
    dummy_message = "BA1000000002EEEEEE00A2420508CAFEDECADA"#String
    #parsed_message = FrameParser()

main()