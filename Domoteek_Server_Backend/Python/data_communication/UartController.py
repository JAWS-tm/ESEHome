from config.app_config import logger
from data_communication.UartSerial import uart_process_main_thread
import queue
from threading import Thread


'''
This class enables the usage of the UartSerial class in a thread. The thread is controlled and initialised by this class.
The uart_config parameter should match the json config file architecture
'''

class UartController :
    '''Constructor'''
    def __init__(self, uart_config):
        #Thread that handles UART communication
        self.uart_to_bdd_msg_q = queue.Queue()
        self.bdd_to_uart_msg_q = queue.Queue()
        self.uart_thread = Thread(target=uart_process_main_thread, args=(uart_config["port"],uart_config["baudrate"],uart_config["timeout"], self.uart_to_bdd_msg_q, self.bdd_to_uart_msg_q, uart_config["end_of_frame_character"]), daemon=True).start()
    '''Methods'''
    def get_last_message(self):
        if(self.uart_to_bdd_msg_q.qsize()>0):
            last_msg = self.uart_to_bdd_msg_q.get()
            return last_msg
        else :
            return 0
    def send_new_message(self, msg : str):
        next_msg = self.bdd_to_uart_msg_q.put(msg)


