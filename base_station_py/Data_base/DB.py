#Class DB

class dBclass (object):
        
    def __init__(self):
        self.nom = "----- dB class -----"


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

"""