#La classe doit modéliser un objet message qui contient toutes les informations d'un message interpretées et accessibles depuis ses méthodes.
#import this


from email import message


class FrameParser :
    #Attributes
    def __init__(self, message):
        self.message = message

    def msgParsed(self):
        CONST_BEGIN = "BA"
        CONST_END = "DA"
        self.tram_size = len(self.message)//2

        tab_msg = []
        for x in range(self.tram_size):
            chaine = self.message[x*2]+self.message[(x*2)+1]
            tab_msg.append(chaine)
        #print(tab_msg)

        self.begin = tab_msg[0]
        self.data_size = tab_msg[1]
        self.emitter = "".join(tab_msg[2:6]) 
        self.receiver = "".join(tab_msg[6:10])
        self.cnt = tab_msg[10] 
        self.id = tab_msg[11]
        self.msg_size = tab_msg[12]
        self.param_id_e = tab_msg[13]
        self.data = tab_msg[14:-1]
        self.end = tab_msg[-1]
        self.data_concat = "".join(self.data) 

        if self.begin != CONST_BEGIN:
            print("Frame error")
        elif self.end != CONST_END:
            print("Frame error")
        elif self.param_id_e > "24" :
            print("Param id error")
        # elif len(reciver) != 8:
        #     print("Reciver error")
        else:
            tab_parse = []
            tab_parse.insert(0,self.begin)
            tab_parse.insert(1,self.data_size)
            tab_parse.insert(2,self.emitter)
            tab_parse.insert(3,self.receiver)
            tab_parse.insert(4,self.cnt)
            tab_parse.insert(5,self.id)
            tab_parse.insert(6,self.msg_size)
            tab_parse.insert(7,self.param_id_e)
            tab_parse.insert(8,self.data_concat)
            tab_parse.insert(9,self.end)
            print(tab_parse)

    def getInfoMessageId(self):
        if self.id == "02":
            print("RECENT_RESET")
        elif self.id == "03":
            print("ASK_FOR_SOFTWARE_RESET")
        elif self.id == "16":
            print("PING")
        elif self.id == "06":
            print("PONG")
        elif self.id == "30":
            print("EVENT_OCCURED")
        elif self.id == "40":
            print("PARAMETER_IS")
        elif self.id == "41":
            print("PARAMETER_ASK")
        elif self.id == "42":  
            print("PARAMETER_WRITE")
        elif self.id == "FD":  
            print("I_HAVE_NO_SERVER_ID")
        elif self.id == "FE":  
            print("YOUR_SERVER_ID_IS")
        else:
            print("message id error")
    #Message attributes (ex dest, emitter, data, etc.)

    #Constructor
    #def __init__(self, ) :
    #init attributes (en fonction du protocole de com)

    #Methods
    #Getters et setters


    #def getMessageInfo():
        #return "dest :"+self.dest+"emitter :"+self.emitter...etc.