from config.app_config import logger
from data_communication.UartSerial import uart_reading_thread
import queue
from threading import Thread


'''
This class enables to use the UartSerial class in a thread. The thread is controlled and initialised by this class.
The uart_config parameter should match the json config file architecture
'''

class UartController :
    '''Constructor'''
    def __init__(self, uart_config):
        self.msg_q = queue.Queue()
        self.reading_thread = Thread(target=uart_reading_thread, args=(uart_config["port"],uart_config["baudrate"],uart_config["timeout"], self.msg_q, uart_config["end_of_frame_character"]), daemon=True).start()
        #logger.info("New thread started for uart reading")
        print("New thread started for uart reading")
    '''Methods'''
    def get_last_message(self):
        if(self.msg_q.qsize()>0):
            last_msg = self.msg_q.get()
            #print("Last message from uart thread : "+last_msg)
            return last_msg
        else :
            return 0

