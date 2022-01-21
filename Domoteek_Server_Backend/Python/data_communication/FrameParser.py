#La classe doit modéliser un objet message qui contient toutes les informations d'un message interpretées et accessibles depuis ses méthodes.
#import this


from email import message


class FrameParser :
    #Attributes
    def __init__(self, message):
        self.message = message
        self.begin = message [:2]
        self.data_size = message [2:4]
        self.receiver = message [4:12]
        self.emmiter = message [12:20]
        self.counter = message [20:22]
        self.id = message [22:24]
        self.msg_size = message [24:26]
        self.param_color = message[26:28]
        self.data = message[28:-2]
        self.end = message[-2:]

    def msgParsed(self):
        # if self.msg_size != 0:
        #     print("Trame :", self.message)
        #     print("begin :", self.begin)
        #     print("datasize :", self.data_size)
        #     print("receiver :", self.receiver)
        #     print("emmiter :", self.emmiter)
        #     print("counter :", self.counter)
        #     print("id :", self.id)
        #     print("msg_size :", self.msg_size)
        #     print("parameter color :", self.param_color)
        #     print("data :", self.data)
        #     print("end :", self.end)
        # else:
        #      print("message vide")
        CONST_BEGIN = "BA"
        CONST_END = "DA"
        self.tram_size = len(self.message)//2

        tab_msg = []
        for x in range(self.tram_size):
            chaine = self.message[x*2]+self.message[(x*2)+1]
            tab_msg.append(chaine)
        #print(tab_msg)

        begin = tab_msg[0]

        data_size = tab_msg[1]
        emitter = "".join(tab_msg[2:6]) 
        reciver = "".join(tab_msg[6:10])
        cnt = tab_msg[10] 
        id = tab_msg[11]
        msg_size = tab_msg[12]
        data = tab_msg[13:-1]
        end = tab_msg[-1]
        data_concat = "".join(data) 
        if begin != CONST_BEGIN:
            print("Frame error")
        elif end != CONST_END:
            print("Frame error")
        # elif len(emitter) != 8:
        #     print("Emitter error")
        # elif len(reciver) != 8:
        #     print("Reciver error")
        else:
            tab_parse = []
            tab_parse.insert(0,begin)
            tab_parse.insert(1,data_size)
            tab_parse.insert(2,emitter)
            tab_parse.insert(3,reciver)
            tab_parse.insert(4,cnt)
            tab_parse.insert(5,id)
            tab_parse.insert(6,msg_size)
            tab_parse.insert(7,data_concat)
            tab_parse.insert(8,end)
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