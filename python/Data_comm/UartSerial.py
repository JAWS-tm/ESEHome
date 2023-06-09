import serial
import time
from queue import Queue
from Data_comm.FrameParser import FrameParser

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
    def __init__(self, new_port : str, new_baudrate : int, new_timeout : int, launch_as_thread : bool, incoming_msg_queue : Queue, outgoing_msg_queue : Queue, incoming_dico_queue : Queue) : #launch_as_thread and msg_q should be additional args
        self.baudrate = new_baudrate
        self.timeout = new_timeout
        self.port = serial.Serial(port=new_port, baudrate=self.baudrate, timeout=self.timeout)
        self.previous_message = ""
        self.current_message = ""
        self.end_of_message = False
        self.print_port_info()
        if(launch_as_thread):
            self.incoming_message_queue = incoming_msg_queue
            self.incoming_dico_queue = incoming_dico_queue
            self.outgoing_message_queue = outgoing_msg_queue
            self.launched_as_thread = True
        else :
            self.launched_as_thread = False
    
    def read_uart_frame(self, end_of_frame_character) :
        try :
            # copie d’une ligne entiere jusqu’a \n dans rcv
            rcv = self.port.readline().decode("utf-8") 
            if(rcv == ''):
                return 0
            else:
                # print("rcv ::",rcv)
                self.current_message = rcv
                self.put_message_in_queue(rcv)
                return rcv

            ## Pas besoin de la suite car "readline" permet de récupérer chaque tram 1 par 1 en entière

            # if not self.end_of_message : 
            #     copie de 15 caracteres lu dans rcv
            #     rcv = self.port.read(15).decode("utf-8") 
            #     if(rcv.find("\n")!=-1):
            #         #The message is ending
            #         end_msg = rcv.split(end_of_frame_character)
            #         #Get the other side of the message ?
            #         self.current_message+= end_msg[0]
            #         self.end_of_message = True
            #     else :
            #         #print("Completing message...")
            #         self.current_message+=rcv
            # else:
            #     print("New message received : ")
            #     print(self.current_message)
            #     self.end_of_message = False
            #     if(self.launched_as_thread) : self.put_message_in_queue(self.current_message)
            #     self.previous_message = self.current_message
            #     self.current_message = ""
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

    def put_dico_in_queue(self, dico):
        if(self.launched_as_thread):
            self.incoming_dico_queue.put(dico)
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

    def print_port_info(self):
        print("\n----Uart read config : \n"
        +     "--Port : "+str(self.port.name)+"\n"
        +     "--Baudrate : "+str(self.baudrate)+"\n"
        +     "--Timeout : "+str(self.timeout)+"\n")


#THREADING MAIN FUNCTION
def uart_process_main_thread(port : str, baudrate : int, timeout : int, incoming_message_queue : Queue, outgoing_message_queue : Queue, incoming_dico_queue : Queue, end_of_frame_character : str):
    uart = UartSerial(port, baudrate, timeout, True, incoming_message_queue, outgoing_message_queue, incoming_dico_queue)
    while True :
        message = uart.read_uart_frame(end_of_frame_character) #Automatically updates queue when a complete message is received
        if (message == 0):
            print("\nPas de tram reçu. En attente...")
        else : 
            FrameParser(message)
            dico_tram = FrameParser(message).msgParsed()
            uart.put_dico_in_queue(dico_tram)
            
            ## Envoie reponse pour cryptage


############## Commentaire car pas utilisé pour l'instant

        # next_msg = uart.get_next_message() #Checks if there is a message to send
        # if(next_msg): 
        #     if(uart.send_uart_frame(next_msg)==1):
        #         # logger.debug("Message successfully sent to UART : "+next_msg)
        #         print("Message successfully sent to UART : "+next_msg)
        #     else :
        #         # logger.debug("ERROR : Failed to send msg to UART --> "+next_msg)
        #         print("ERROR : Failed to send msg to UART --> "+next_msg)
            
        