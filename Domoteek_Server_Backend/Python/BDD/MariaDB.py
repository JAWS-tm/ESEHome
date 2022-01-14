# Module Imports
from asyncio import wait_for
from multiprocessing.connection import wait
import sys
import mysql.connector
from config.app_config import BDD_CONFIG, logger
# import mariadb

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
    # except mariadb.Error as e:
    except Exception as e:
        logger.error(f"MariaDB.py : Error connecting to MariaDB Platform: {e}")
        sys.exit(1)

def selectData():
    wait_for("Dev")

def updateData():
    wait_for("Dev")

def addData():
    wait_for("Dev")

def removeData():
    wait_for("Dev")

#Pour tester les fonctions en cours de dev 
if __name__ == "__main__":
    connect()