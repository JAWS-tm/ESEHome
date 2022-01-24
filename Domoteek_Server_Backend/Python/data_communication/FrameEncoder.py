class FrameEncoder:
    #Attributes:
    def __init__(self, msg):
        self.msg = msg

    def inputMessage(self):
        msg = input("Msg en hexa : ")
        print("Le message envoyé est : " ,msg)
        data_size = hex(len(msg)//2)
        print("data_size : ", data_size)
        nb_bits =  data_size[2:]
        #print ("Nombre bits : ",nb_bits)
        len_bits = len(nb_bits)
        print("Conv en hexa : ", len_bits)
        if len_bits==1 :
            zero = "0"
            new_data_size = zero + nb_bits
            print("conv en hexa : ", new_data_size)
        else :
            print("conv en hexa : ", nb_bits) 


        msg_id_e = input("msg id e : ")
        if len(msg_id_e) > 2 :
            print("error msg") 
        elif msg_id_e == "02" :
            size == "00"
        elif msg_id_e == "03" :
            size == "00"
        elif msg_id_e == "06" :
            size == "00"
        elif msg_id_e == "16" :
            size == "00"
        elif msg_id_e == "30" :
            size == "01"
        elif msg_id_e == "40" :
            size == "05"
        elif msg_id_e == "41" :
            size == "01"
        elif msg_id_e == "42" :
            size == "05"
        elif msg_id_e == "FD" :
            size == "00"
        elif msg_id_e == "FE" :
            size == "00"

        # if len_new_concat==1 :
        #     concat = 0
        #     data_size = concat + data_size
        #     print(data_size)


        # print ("data size : ", data_size)

        #print("le message envoyé est", input_dummy_msg)



    """ def getInfoMessageId(self):
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
        print("message id error") """
