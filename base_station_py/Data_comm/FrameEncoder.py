class FrameEncoder:
    #Attributes:
    def __init__(self, msg):
        self.msg = msg

    def inputMessage(self):
        # msg = input("Msg en hexa : ")
        # print("Le message envoyé est : " ,msg)
        # data_size = hex(len(msg)//2)
        # print("data_size : ", data_size)
        # nb_bits =  data_size[2:]
        # #print ("Nombre bits : ",nb_bits)
        # len_bits = len(nb_bits)
        # print("Conv en hexa : ", len_bits)
        # if len_bits==1 :
        #     zero = "0"
        #     new_data_size = zero + nb_bits
        #     print("conv en hexa : ", new_data_size)
        # else :
        #     print("conv en hexa : ", nb_bits) 

        begin = "BA"
        end = "DA" 
        emmiter = input("emmiter : ")
        receiver = input("receiver : ")
        len_emmiter = len(emmiter)
        len_receiver = len(receiver)
        print(len_emmiter+len_receiver)
        if (len_emmiter+len_receiver)==16 :
            msg_id_e = input("msg id e : ")
            size = 0
            param_id_e = 0
            if len(msg_id_e) > 2 :
                print("error msg") 
            elif msg_id_e == "02" :
                size = "00"
                msg = ""
                
            elif msg_id_e == "03" :
                size = "00"
                msg = ""
                
            elif msg_id_e == "06" :
                size = "00"
                msg = ""
                
            elif msg_id_e == "16" :
                size = "00"
                msg = ""
                
            elif msg_id_e == "30" :
                size = "01"
                event_id_e = input("Event id e : ")
                msg = ""
                
            elif msg_id_e == "40" :
                size = "05"
                msg = input("Msg en hexa : ")
                if len(msg)==8:
                    print("Message de bonne taille : ", msg)
                else :
                    print("Message de mauvaise taille")
                param_id_e = input("Param id e : ")
                if param_id_e > "24" or param_id_e == "16" :
                    print("Mauvais param_id_e")
                else :
                    print("Bon param_id_e")

            elif msg_id_e == "41" :
                size = "01"
                param_id_e = input("Param id e : ")
                msg = ""
                if param_id_e > "24" or param_id_e == "16" :
                    print("Mauvais param_id_e")
                else :
                    print("Bon param_id_e")

            elif msg_id_e == "42" :
                size = "05"
                msg = input("Msg en hexa : ")
                if len(msg)==8:
                    print("Message de bonne taille : ", msg)
                else :
                    print("Message de mauvaise taille")
                param_id_e = input("Param id e : ")
                if param_id_e > "24" or param_id_e == "16" :
                    print("Mauvais param_id_e")
                else :
                    print("Bon param_id_e")

            elif msg_id_e == "FD" :
                size = "00"
                msg = ""
        
            elif msg_id_e == "FE" :
                size = "00"
                msg = ""
        else :
            print ("Emmetteur ou receveur de mauvaise taille")
        frame = emmiter+receiver+msg_id_e+size+param_id_e+msg
        size_frame = len(frame)//2
        full_frame = begin+str(size_frame)+emmiter+receiver+msg_id_e+size+param_id_e+msg+end
        tab_frame = []
        tab_frame.append(full_frame)
        print(tab_frame)


        



        # print("msg_id_e : ", msg_id_e, "size ", size, "msg : ", msg )
        
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