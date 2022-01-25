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
    incoming_message_queue : Queue
    '''
    def __init__(self, new_port : str, new_baudrate : int, new_timeout : int, launch_as_thread : bool, incoming_msg_queue : Queue, outgoing_msg_queue : Queue) : #launch_as_thread and msg_q should be additional args
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
            self.incoming_message_queue = incoming_msg_queue
            self.outgoing_message_queue = outgoing_msg_queue
            self.launched_as_thread = True
        else :
            self.launched_as_thread = False
    
    def read_uart_frame(self, end_of_frame_character) :
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

    def send_uart_frame(self, frame : str):
        try :
            self.port.write(bytes(frame, 'utf-8'))
            return 1
        except :
            return 0

    def put_message_in_queue(self, message):
        if(self.launched_as_thread):
            self.incoming_message_queue.put(message)
        else :
            print("ERROR : You didn't launch the uart reader as a thread (ref to the constructor)")
    
    def get_next_message(self):
        if(self.outgoing_message_queue.qsize()>0):
            return self.outgoing_message_queue.get()
        else :
            return None

    def print_port_info(self):
        print("Port : "+str(self.port)+"\n"
        +     "Baudrate : "+str(self.baudrate)+"\n"
        +     "Timeout : "+str(self.timeout)+"\n")


#THREADING MAIN FUNCTION
def uart_process_main_thread(port : str, baudrate : int, timeout : int, incoming_message_queue : Queue, outgoing_message_queue : Queue, end_of_frame_character : str):
    uart = UartSerial(port, baudrate, timeout, True, incoming_message_queue, outgoing_message_queue)
    while True :
        uart.read_uart_frame(end_of_frame_character) #Updates queue when a complete message is received
        next_msg = uart.get_next_message() #Checks if there is a message to send
        if(next_msg): 
            if(uart.send_uart_frame(next_msg)==1):
                print("Message successfully sent to UART : "+next_msg)
            else :
                print("ERROR : Failed to send msg to UART --> "+next_msg)
            
        