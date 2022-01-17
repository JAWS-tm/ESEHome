# Module Imports
import sys
import mysql.connector
from config.app_config import BDD_CONFIG, logger
# import mariadb


class BDDRequest:
    def __init__(self):
        try:
            self.conn = mysql.connector.connect(user=BDD_CONFIG["user"],
                                                password=BDD_CONFIG["password"],
                                                host=BDD_CONFIG["host"],
                                                port=BDD_CONFIG["port"],
                                                database=BDD_CONFIG["BDD_name"])
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
        

# def connect():
#     # Connect to MariaDB Platform
#     try:
#         #      mariadb.connect
#         conn = mysql.connector.connect(
#             user=BDD_CONFIG["user"],
#             password=BDD_CONFIG["password"],
#             host=BDD_CONFIG["host"],
#             port=BDD_CONFIG["port"],
#             database=BDD_CONFIG["BDD_name"]

#         )
#         logger.debug("MariaDB.py : Connected to database")
#         return conn
#     # except mariadb.Error as e:
#     except Exception as e:
#         logger.error(f"MariaDB.py : Error connecting to MariaDB Platform: {e}")
#         sys.exit(1)

# def selectData(curs): #, nom_bdd, nom_table
#     select = "SELECT data, id FROM pipo;"
#     #select = ("SELECT nom_table FROM nom_bdd")
#     curs.execute(select)
    
# def updateData(curs):
#     update = "UPDATE pipo SET data='Température : 30° | Humidité : 60%' WHERE id=2;"
#     curs.execute(update)

# def addData(curs):
#     add = "INSERT INTO pipo (data) VALUES 'Température : 24°C | Humidité : 45%';"
#     curs.execute(add)

# def removeData(curs):
#     remove = "DELETE FROM pipo WHERE id = 4;"
#     curs.execute(remove)

# def testBDD():
#     conn = connect()
#     curs = conn.cursor()
#     addData(curs)
#     updateData(curs)
#     removeData(curs)










# https://dev.mysql.com/doc/connector-python/en/connector-python-example-cursor-transaction.html