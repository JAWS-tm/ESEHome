# Module Imports
import mysql.connector
# import mariadb
from config.app_config import BDD_CONFIG, logger

import sys

def connect():
    # Connect to MariaDB Platform
    try:
        #      mariadb.connect
        conn = mysql.connector.connect(
            user=BDD_CONFIG["user"],
            password=BDD_CONFIG["password"],
            host=BDD_CONFIG["host"],
            port=BDD_CONFIG["port"],
            database=BDD_CONFIG["BDD_name"]

        )
        logger.debug("MariaDB.py : Connected to database")
    except Exception as e:
        logger.error(f"MariaDB.py : Error connecting to MariaDB Platform: {e}")
        sys.exit(1)

# def connect():
#     # Connect to MariaDB Platform
#     try:
#         conn = mariadb.connect(
#             user=BDD_CONFIG["user"],
#             password=BDD_CONFIG["password"],
#             host=BDD_CONFIG["host"],
#             port=BDD_CONFIG["port"],
#             database=BDD_CONFIG["BDD_name"]

#         )
#         logger.debug("MariaDB.py : Connected to database")
#     except mariadb.Error as e:
#         logger.error(f"MariaDB.py : Error connecting to MariaDB Platform: {e}")
#         sys.exit(1)