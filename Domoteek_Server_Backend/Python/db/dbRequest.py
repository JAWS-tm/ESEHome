# Module Imports
import sys
import mysql.connector
from config.app_config import DB_CONFIG, logger
# import mariaDB


class dbRequest:
    def __init__(self):
        try:
            self.conn = mysql.connector.connect(user=DB_CONFIG["user"],
                                                password=DB_CONFIG["password"],
                                                host=DB_CONFIG["host"],
                                                port=DB_CONFIG["port"],
                                                database=DB_CONFIG["DB_name"])
            self.cursor = self.conn.cursor()
            logger.debug("MariaDB.py : Connected to database")
        except Exception as e:
            logger.error(f"MariaDB.py : Error connecting to MariaDB Platform: {e}")
            sys.exit(1)

    def sendData(self, request, data):
        self.cursor.execute(request, data)
        self.conn.commit()
        print(self.cursor)
    
    def recieveData(self, query):
        self.cursor.execute(query)

    def getCursor(self):
        return self.cursor
    
    def endConn(self):
        self.cursor.close()
        self.conn.close()
