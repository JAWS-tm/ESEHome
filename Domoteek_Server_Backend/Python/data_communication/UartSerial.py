import serial

class UartSerial :
    '''
    Attributes :
    port : string
    baudrate : int
    timeout : float
    previous_message : string
    current_message : string
    end_of_message : boolean
    '''
    def __init__(self, new_port, new_baudrate, new_timeout) :
        self.baudrate = new_baudrate
        self.timeout = new_timeout
        print(self.timeout)
        self.port = serial.Serial(new_port, baudrate=self.baudrate, timeout=self.timeout)
        self.previous_message = ""
        self.current_message = ""
        self.end_of_message = False
        print("Init completed with port : "+new_port)
        self.print_port_info()
        
    
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
                    print("New message received : ")
                    print(self.current_message)
                    self.end_of_message = False
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
        