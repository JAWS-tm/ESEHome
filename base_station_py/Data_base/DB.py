import mysql.connector

class dBclass:
    
    #                       ------- INIT -------
    def __init__(self,bdd_config):
        self.nom = "----- DB class -----"
        
    #connection to db
        print("--- Connection DB ---")
        try:
            self.cnx = mysql.connector.connect(
                ## Caution: it is your personnal host user and password
                host = bdd_config["host"],
                port = bdd_config["port"],
                user = bdd_config["user"],
                passwd = bdd_config["password"]
            )
            self.cursor = self.cnx.cursor()
        except Exception as e:
            print("Error init database :", str(e))

    #Creation of tables
    def create_tables(self):
        self.cursor.execute("CREATE TABLE IF NOT EXISTS historique (id INT AUTO_INCREMENT PRIMARY KEY, date DATETIME NOT NULL, action VARCHAR(255) NOT NULL)")
        self.cnx.commit()
        self.cursor.execute("CREATE TABLE IF NOT EXISTS chiffrage (id INT AUTO_INCREMENT PRIMARY KEY, cle VARCHAR(255) NOT NULL, valeur VARCHAR(255) NOT NULL)")
        self.cnx.commit()
        self.cursor.execute("CREATE TABLE IF NOT EXISTS local (id INT AUTO_INCREMENT PRIMARY KEY, nom VARCHAR(255) NOT NULL, adresse VARCHAR(255) NOT NULL)")
        self.cnx.commit()
    
    #Creation of database
    def create_database(self):
        try:
            self.cursor.execute("CREATE DATABASE IF NOT EXISTS loggg") # execute sql control
            self.cnx.commit()
            self.cursor.execute("USE loggg")
            self.cnx.commit()
        except Exception as e:
            print("Error create database :", str(e))
    
    #Close the connection when it's finish
    def close_connection(self):
        self.cursor.close()
        self.cnx.close()



#                       ---------- MAIN DB ----------
if __name__ == "__main__":
    db = dBclass()
    db.create_database() #if database is not yet create
    db.create_tables()  #same for tables

    #go to Receive_send send by Reponse

    db.close_connection() #close db when all is finished

"""

//source : DB controller 

def put_message_in_bdd_sending_queue(self, msg : FrameParser):
next_msg = self.output_queue.put(msg)
logger.debug("Message has been put into database sending queue")


//source : DB request 

def sendData(self, request, data):
        self.cursor.execute(request, data)
        self.conn.commit()
        print(self.cursor)
    
    def receiveData(self, query):
        self.cursor.execute(query)
        return self.cursor.fetchall()

    def getCursor(self):
        return self.cursor

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
        time.sleep(0.5)
        try :
            schedule.run_pending() #ie check for new messages from DB
            msg_to_send = db.get_next_message()#Checks if there is a message to send
            if(msg_to_send):#Msg to send should be a FrameParser object
                #Send request to BDD
                new_msg = dbMessage(db, msg_to_send.getReceiver(), msg_to_send.getEmitter() , msg_to_send.getId(), msg_to_send.getParamID(), msg_to_send.getData(), datetime.datetime.now() ,True)
                new_msg.objectTX2DB()
        except Exception as e:
            logger.error("DATABASE THREAD ERROR : "+str(e))

=======
#Class DB

class dBclass (object):
        
    def __init__(self):
        self.nom = "----- dB class -----"


"""

#source : DB controller 

def put_message_in_bdd_sending_queue(self, msg : FrameParser):
    next_msg = self.output_queue.put(msg)
    logger.debug("Message has been put into database sending queue")


#source : DB request 

def sendData(self, request, data):
        self.cursor.execute(request, data)
        self.conn.commit()
        print(self.cursor)
    
def receiveData(self, query):
    self.cursor.execute(query)
    return self.cursor.fetchall()

def getCursor(self):
    return self.cursor

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
        time.sleep(0.5)
        try :
            schedule.run_pending() #ie check for new messages from DB
            msg_to_send = db.get_next_message()#Checks if there is a message to send
            if(msg_to_send):#Msg to send should be a FrameParser object
                #Send request to BDD
                new_msg = dbMessage(db, msg_to_send.getReceiver(), msg_to_send.getEmitter() , msg_to_send.getId(), msg_to_send.getParamID(), msg_to_send.getData(), datetime.datetime.now() ,True)
                new_msg.objectTX2DB()
        except Exception as e:
            logger.error("DATABASE THREAD ERROR : "+str(e))
