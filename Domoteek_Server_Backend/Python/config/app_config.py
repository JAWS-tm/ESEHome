import json
from logs.appli_logger import AppliLogger

CONFIG = {}
with open('Domoteek_Server_Backend/Python/config/config.json', "r") as jsonFile:
    CONFIG = json.load(jsonFile)
    jsonFile.close()

DATA_COMMUNICATION_CONFIG = CONFIG["data_communication"]
BDD_CONFIG = CONFIG["BDD"]

#AppliLogger("nomdufichier","DEBUG","default")
logger = AppliLogger(CONFIG["logs"]["fileName"],CONFIG["logs"]['filter'],CONFIG["logs"]['format'])
