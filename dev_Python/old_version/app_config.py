import json
from appli_logger import AppliLogger

CONFIG = {}
with open('old_version/config.json', "r") as jsonFile:
    CONFIG = json.load(jsonFile)
    jsonFile.close()

DATA_COMMUNICATION_CONFIG = CONFIG["data_communication"]
DB_CONFIG = CONFIG["DB"]
UART_CONFIG = CONFIG["data_communication"]["UART"]

#AppliLogger("nomdufichier","DEBUG","default")
logger = AppliLogger(CONFIG["logs"]["fileName"],CONFIG["logs"]['filter'],CONFIG["logs"]['format'])