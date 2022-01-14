import json
from logs.appli_logger import AppliLogger

DATA_COMMUNICATION_CONFIG = {}
with open('config/config.json') as jsonFile:
    DATA_COMMUNICATION_CONFIG = json.load(jsonFile)
    jsonFile.close()

#AppliLogger("nomdufichier","DEBUG","default")
logger = AppliLogger(DATA_COMMUNICATION_CONFIG["data_communication"]["logs"]["fileName"],DATA_COMMUNICATION_CONFIG["data_communication"]["logs"]['filter'],DATA_COMMUNICATION_CONFIG["data_communication"]["logs"]['format'])