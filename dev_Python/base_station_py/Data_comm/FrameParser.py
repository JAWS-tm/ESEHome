#La classe doit modéliser un objet message qui contient toutes les informations d'un message interpretées et accessibles depuis ses méthodes.
#import this



from email import message



class FrameParser :
    #Attributes
    def __init__(self, message):
        self.message = message
        self.msgParsed()
        self.getInfoMessageId()
        self.getSizeUpBit()
     

    #Message attributes (ex dest, emitter, data, etc.)
    

    #Constructor
    #def __init__(self, ) :
    #init attributes (en fonction du protocole de com)
    def msgParsed(self):
        CONST_BEGIN = "BA"
        CONST_END = "DA"
        self.tram_size = len(self.message)//2
        tram_dico = {}
        tab_msg = []
        for x in range(self.tram_size):
            chaine = self.message[x*2]+self.message[(x*2)+1]
            tab_msg.append(chaine)
        print("\n")
        # print("tab_msg :",tab_msg)

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
            print("Frame begin error : ", self.begin)
            return 0
        elif self.end != CONST_END:
            print("Frame end error :", self.end)
            return 0
        elif self.param_id_e == CONST_END: # param_id_e = CONST_END si pas de message dans la tram
            print("pas de message dans la tram")
            tram_dico = {
                "begin": self.begin,
                "data_size": self.data_size,
                "emitter": self.emitter,
                "receiver": self.receiver,
                "cnt": self.cnt,
                "id": self.id,
                "msg_size": self.msg_size,
                "param_id_e": "",   # String vide, sinon param_id_e = DA
                "data_concat": self.data_concat,
                "end": self.end
            }
            # print(tram_dico)
            return tram_dico
            # self.put_dico_in_queue(tram_dico)
        elif self.param_id_e > "24" or self.param_id_e == "16" :
            print("Param id error")
            return 0
        else:
            tram_dico = {
                "begin": self.begin,
                "data_size": self.data_size,
                "emitter": self.emitter,
                "receiver": self.receiver,
                "cnt": self.cnt,
                "id": self.id,
                "msg_size": self.msg_size,
                "param_id_e": self.param_id_e,
                "data_concat": self.data_concat,
                "end": self.end
            }
            # print(tram_dico)
            return tram_dico
            # self.put_dico_in_queue(tram_dico)
            # tab_parse = []
            # tab_parse.insert(0,self.begin)
            # tab_parse.insert(1,self.data_size)
            # tab_parse.insert(2,self.emitter)
            # tab_parse.insert(3,self.receiver)
            # tab_parse.insert(4,self.cnt)
            # tab_parse.insert(5,self.id)
            # tab_parse.insert(6,self.msg_size)
            # tab_parse.insert(7,self.param_id_e)
            # tab_parse.insert(8,self.data_concat)
            # tab_parse.insert(9,self.end)
            # print(tab_parse)

    #Recupération du msg ID et affichage de sa signification
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
        elif self.id == "FF":
            print("LONG_MESSAGE")
        else:
            print("Message id error, id :", self.id)
    
    #Fonction qui regarde si la trame est chiffrée ou non via le bit de poids fort
    def getSizeUpBit(self):

        # print(self.msg_size)

        ini_string = self.msg_size
        scale = 16


        # Convertir le message hexadécimal en un entier
        message_int = int(ini_string, 16)
        # Utiliser l'opérateur bit à bit AND pour vérifier le bit de poids fort
        msb = message_int & 0x80
        # Si le bit de poids fort est 1, l'afficher
        if msb:
            # Printing initial string
            print ("msg_size : ", ini_string, " bit de poid fort : 1")
        else:
            print ("msg_size : ", ini_string, " bit de poid fort : 0")

    #Methods
    #Getters et setters
    def getFrameBegin(self):
        str_begin = "".join(self.begin)
        return str_begin

    def getDataSize(self):
        str_dataSize = "".join(self.data_size)
        return str_dataSize
    
    def getEmitter(self):
        str_emitter = "".join(self.emitter)
        return str_emitter
    
    def getReceiver(self):
        str_receiver = "".join(self.receiver)
        return str_receiver
    
    def getCounter(self):
        str_counter = "".join(self.cnt)
        return str_counter
    
    def getId(self):
        str_id = "".join(self.id)
        return str_id

    def getMessageSize(self):
        str_messageSize = "".join(self.msg_size)
        return str_messageSize

    def getParamID(self):
        str_paramId = "".join(self.param_id_e)
        return str_paramId
    
    def getData(self):
        str_Data = "".join(self.data_concat)
        return str_Data
    
    def getEndFrame(self):
        str_endFrame= "".join(self.end)
        return str_endFrame


    #def getMessageInfo():
        #return "dest :"+self.dest+"emitter :"+self.emitter...etc.