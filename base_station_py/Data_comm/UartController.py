<<<<<<< HEAD
from app_config import logger
from UartSerial import uart_process_main_thread
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
        self.input_queue = queue.Queue()
        self.output_queue = queue.Queue()
        self.uart_thread = Thread(target=uart_process_main_thread, args=(uart_config["port"],uart_config["baudrate"],uart_config["timeout"], self.input_queue, self.output_queue, uart_config["end_of_frame_character"]), daemon=True).start()
    '''Methods'''
    def get_last_message(self):#message received from the uart
        if(self.input_queue.qsize()>0):
            last_msg = self.input_queue.get()
            return last_msg
        else :
            return 0
    def put_message_in_uart_sending_queue(self, msg : str):#message to send from the uart
        next_msg = self.output_queue.put(msg)


=======
from app_config import logger
from UartSerial import uart_process_main_thread
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
        self.input_queue = queue.Queue()
        self.output_queue = queue.Queue()
        self.uart_thread = Thread(target=uart_process_main_thread, args=(uart_config["port"],uart_config["baudrate"],uart_config["timeout"], self.input_queue, self.output_queue, uart_config["end_of_frame_character"]), daemon=True).start()
    '''Methods'''
    def get_last_message(self):#message received from the uart
        if(self.input_queue.qsize()>0):
            last_msg = self.input_queue.get()
            return last_msg
        else :
            return 0
    def put_message_in_uart_sending_queue(self, msg : str):#message to send from the uart
        next_msg = self.output_queue.put(msg)


>>>>>>> 9c9f1f97cbf1019a68a5fc30533f120b399640be
