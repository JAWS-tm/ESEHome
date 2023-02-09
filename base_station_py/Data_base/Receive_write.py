import mysql.connector
#This class is used to receivre a dictionary (containing the frame) from "Response" to write it inside the DataBase.
class Receive_write:
    #                       ------- INIT -------
    def __init__(self, bdd_config, db, reciever, emitter, typeID, paramID, msg, date, perm, history):
        self.dico = {}
        self.db = db
        self.receiver = reciever
        self.emitter = emitter
        self.paramID = paramID
        self.msgTypeID = typeID # frame.getId
        self.msgCONTENT = msg # frame.getMessage
        self.msgDATE = date # frame.getDate
        self.msgPerm = perm
        self.history = history
        self.nom = "----- Receive_write class -----"

        #connection to db
        try:
            self.cnx = mysql.connector.connect(
                ## Caution: it is your personnal host user and password
                host = bdd_config["host"],
                port = bdd_config["port"],
                user = bdd_config["user"],
                passwd = bdd_config["password"] 
            )
            self.cursor = self.cnx.cursor()
        except Exception as e:
            print("Error init database :", str(e))

        
    #                       ---------- Functions ----------

    def set_new_dico(self, new_dico):
        if(new_dico != 0):
            self.dico = new_dico
            print("set_new_dico ::", self.dico)
            self.receiver = self.dico.receiver
            self.emitter = self.dico.emitter
            self.msgTypeID = self.dico.id
            self.paramID = self.dico.param_id_e
            self.msgCONTENT = self.dico.data_concat
            self.msgDATE = "09/02/2023"
            self.msgPerm = "perm ?"

            self.objectTX2DB()


    def objectTX2DB(self):
        self.cursor.execute("INSERT INTO message (destinataire, emetteur, type_message_id, parametre_id, message, date, permanent) VALUES (%s,%s,%s,%s,%s,%s,%s)", (self.receiver, self.emitter,self.msgTypeID, self.paramID, self.msgCONTENT, self.msgDATE, self.msgPerm)) # execute sql control
        self.cnx.commit()        


if __name__ == "__main__":
    Receive_write()



