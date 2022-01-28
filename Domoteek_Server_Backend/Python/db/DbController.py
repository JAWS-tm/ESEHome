import queue
from threading import Thread
from db.dbRequest import db_process_main_thread
from data_communication.FrameParser import FrameParser

class DbController :
    '''Constructor'''
    def __init__(self, bdd_config):
        #Threads that handles DB communication
        self.input_queue = queue.Queue()
        self.output_queue = queue.Queue()
        self.db_thread = Thread(target=db_process_main_thread, args=(bdd_config["user"], bdd_config["password"], bdd_config["host"], bdd_config["port"], bdd_config["DB_name"], self.input_queue, self.output_queue), daemon=True).start()

    '''Methods'''
    def get_last_message(self):#Message coming from bdd
        if(self.input_queue.qsize()>0):
            last_msg = self.input_queue.get()
            return last_msg
        else :
            return 0
            
    def put_message_in_bdd_sending_queue(self, msg : FrameParser):
        next_msg = self.output_queue.put(msg)