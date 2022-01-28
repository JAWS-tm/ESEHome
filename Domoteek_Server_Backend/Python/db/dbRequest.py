# Module Imports
import sys
import time
import datetime
from queue import Queue
import schedule
import mysql.connector
from config.app_config import logger
from db.SQLRequest import getMessageSQLQuery
from dbProcess.dbMessage import dbMessage
# import mariaDB


class dbRequest:
    def __init__(self, new_user : str, new_password : str, new_host : str, new_port : int, new_DB_name : str, launch_as_thread : bool, incoming_msg_queue : Queue, outgoing_msg_queue : Queue):
        try:
            self.conn = mysql.connector.connect(user=new_user,
                                                password=new_password,
                                                host=new_host,
                                                port=new_port,
                                                database=new_DB_name)
            self.cursor = self.conn.cursor(buffered=True)
            logger.debug("MariaDB.py : Connected to database")
            if(launch_as_thread):
                self.incoming_message_queue = incoming_msg_queue
                self.outgoing_message_queue = outgoing_msg_queue
                self.launched_as_thread = True
        except Exception as e:
            logger.error(f"MariaDB.py : Error connecting to MariaDB Platform: {e}")
            sys.exit(1)

    def sendData(self, request, data):
        self.cursor.execute(request, data)
        self.conn.commit()
        print(self.cursor)
    
    def receiveData(self, query):
        self.cursor.execute(query)
        return self.cursor.fetchall()

    def getCursor(self):
        return self.cursor
    
    def endConn(self):
        self.cursor.close()
        self.conn.close()

    def checkForNewMessage(self):
        potential_data = self.receiveData(getMessageSQLQuery)
        if(potential_data):
            for data in potential_data :
                self.put_message_in_queue(data)

    def put_message_in_queue(self, message):
        if(self.launched_as_thread):
            self.incoming_message_queue.put(message)
        else :
            print("ERROR : You didn't launch the uart reader as a thread (ref to the constructor)")
    
    def get_next_message(self):
        if(self.launched_as_thread):
            if(self.outgoing_message_queue.qsize()>0):
                return self.outgoing_message_queue.get()
            else :
                return None
        else :
            print("ERROR : You didn't launch the uart reader as a thread (ref to the constructor)")

#THREADING MAIN FUNCTION
def db_process_main_thread(user, password, host, port, DB_name, input_queue : Queue, output_queue : Queue):
    db = dbRequest(user, password, host, port, DB_name, True, input_queue, output_queue)
    #Set a timer to periodically check new messages
    schedule.every(0.25).minutes.do(db.checkForNewMessage)
    while True :
        try :
            schedule.run_pending() #ie check for new messages from DB
            msg_to_send = db.get_next_message()#Checks if there is a message to send
            if(msg_to_send):#Msg to send should be a FrameParser object
                #Send request to BDD
                new_msg = dbMessage(db, msg_to_send.getReceiver(), msg_to_send.getEmitter() , msg_to_send.getId(), msg_to_send.getParamID(), msg_to_send.getData(), datetime.datetime.now() ,True)
                new_msg.objectTX2DB()
        except Exception as e:
            logger.error("DATABASE THREAD ERROR : "+str(e))


        



  


