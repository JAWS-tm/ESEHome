from Data_comm.UartSerial import uart_process_main_thread
# import Queue             # Python 2.x
from queue import Queue # Python 3.x
from threading import Thread
from serial.tools.list_ports import comports


'''
This class enables the usage of the UartSerial class in a thread. The thread is controlled and initialised by this class.
The uart_config parameter should match the json config file architecture
'''

def get_serial_ports_open():
        open_port = ""
        for port in comports():
            open_port = port.name
            
        if(open_port != ""):
            return open_port

class UartController :
    '''Constructor'''
    def __init__(self, uart_config):
        try: 
            #Thread that handles UART communication
            self.input_queue = Queue()
            self.dico_input_queue = Queue()
            self.output_queue = Queue()
            self.uart_thread = Thread(target=uart_process_main_thread, args=(uart_config["port"],uart_config["baudrate"],uart_config["timeout"], self.input_queue, self.output_queue, self.dico_input_queue, uart_config["end_of_frame_character"]), daemon=False).start()
        except Exception as e:        
            print("Error init UartController : ", e)
    '''Methods'''
    def get_last_message(self):#message received from the uart
        if(self.input_queue.qsize()>0):
            last_msg = self.input_queue.get()
            return last_msg
        else :
            return 0
    def get_last_dico(self):#message received from the uart
        if(self.dico_input_queue.qsize()>0):
            last_msg = self.dico_input_queue.get()
            return last_msg
        else :
            return 0
    def put_message_in_uart_sending_queue(self, msg : str):#message to send from the uart
        next_msg = self.output_queue.put(msg)

