import json
from logs.appli_logger import AppliLogger

CONFIG = {}
with open('config/config.json', "r") as jsonFile:
    CONFIG = json.load(jsonFile)
    jsonFile.close()

DATA_COMMUNICATION_CONFIG = CONFIG["data_communication"]
DB_CONFIG = CONFIG["DB"]

#AppliLogger("nomdufichier","DEBUG","default")
logger = AppliLogger(CONFIG["logs"]["fileName"],CONFIG["logs"]['filter'],CONFIG["logs"]['format'])
