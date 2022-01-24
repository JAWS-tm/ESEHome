import serial
from queue import Queue

class UartSerial :
    '''
    Attributes :
    port : string
    baudrate : int
    timeout : float
    previous_message : string
    current_message : string
    end_of_message : bool
    launched_as_thread = bool
    ***if launched_as_thread***
    message_queue : Queue
    '''
    def __init__(self, new_port : str, new_baudrate : int, new_timeout : int, launch_as_thread : bool, msg_queue : Queue) : #launch_as_thread and msg_q should be additional args
        self.baudrate = new_baudrate
        self.timeout = new_timeout
        print(self.timeout)
        self.port = serial.Serial(new_port, baudrate=self.baudrate, timeout=self.timeout)
        self.previous_message = ""
        self.current_message = ""
        self.end_of_message = False
        print("Init completed with port : "+new_port)
        self.print_port_info()
        if(launch_as_thread):
            self.message_queue = msg_queue
            self.launched_as_thread = True
        else :
            self.launched_as_thread = False
    
    def read_uart_frames(self, end_of_frame_character) :
        while True:
            try :
                if not self.end_of_message :
                    rcv = self.port.read(15).decode("utf-8") 
                    if(rcv.find("\n")!=-1):
                        #The message is ending
                        end_msg = rcv.split(end_of_frame_character)
                        #Get the other side of the message ?
                        self.current_message+= end_msg[0]
                        self.end_of_message = True
                    else :
                        #print("Completing message...")
                        self.current_message+=rcv
                else:
                    #print("New message received : ")
                    #print(self.current_message)
                    self.end_of_message = False
                    if(self.launched_as_thread) : self.put_message_in_queue(self.current_message)
                    self.previous_message = self.current_message
                    self.current_message = ""
            except Exception :
                self.port.close()
                print("Error reading port... Connection closed") 
                break

    def print_port_info(self):
        print("Port : "+str(self.port)+"\n"
        +     "Baudrate : "+str(self.baudrate)+"\n"
        +     "Timeout : "+str(self.timeout)+"\n")

    def put_message_in_queue(self, message):
        if(self.launched_as_thread):
            self.message_queue.put(message)
        else :
            print("ERROR : You didn't launch the uart reader as a thread (ref to the constructor)")

def uart_reading_thread(port : str, baudrate : int, timeout : int, msg_q : Queue, end_of_frame_character : str):
    uart_reader = UartSerial(port, baudrate, timeout, True, msg_q)
    uart_reader.read_uart_frames(end_of_frame_character)
        