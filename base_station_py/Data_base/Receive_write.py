import mysql.connector
from datetime import datetime

#This class is used to receivre a dictionary (containing the frame) from "Response" to write it inside the DataBase.
class Receive_write:
    #                       ------- INIT -------
    def __init__(self, bdd_config): #  (db, reciever, emitter, typeID, paramID, msg, date, perm, history)
        self.dico = {}
        self.db = ""
        self.receiver = ""
        self.emitter = ""
        self.paramID = ""
        self.msgTypeID = "" # frame.getId
        self.msgCONTENT = "" # frame.getMessage
        self.msgDATE = "" # frame.getDate
        self.msgPerm = ""
        self.history = ""
        self.nom = "----- Receive_write class -----"
        self.cnx = ""
        self.cursor = ""
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
  
        # if(self.dico != 0):
        #     self.set_new_dico()
        #     self.objectTX2DB()
    #                       ---------- Functions ----------

    def set_date():
        # datetime object containing current date and time
        
        # dd/mm/YY H:M:S
        dt_string = now.strftime("%Y-%m-%d %H:%M:%S")
        print("now =", dt_string)
        return dt_string


    def set_new_dico(self, dico):
        if (dico != 0):
            self.dico = dico         
            print("\nset_new_dico ::", self.dico, type(self.dico))
            self.receiver = self.dico.get("receiver")
            self.emitter = self.dico.get("emitter")
            self.msgTypeID = self.dico.get("id")
            self.paramID = self.dico.get("param_id_e")
            self.msgCONTENT = self.dico.get("data_concat")
            self.msgDATE = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            self.msgPerm = 1
            self.emitter = "000000"+self.emitter[6:8]
            self.receiver = "000000"+self.receiver[6:8]

            ## Ajout à la BDD ok, mais encore qqlq bugs, c'est pour çz que c'est commenté 
            self.cursor.execute('''INSERT INTO message 
                (recipient, transmitter, type_message, parameter_id, data, date, permanent) 
            VALUES 
                ((SELECT type_id from object WHERE physical_id = %s),(SELECT type_id from object WHERE physical_id = %s),%s,%s,%s,%s,%s)
            ''', 
                (self.receiver, self.emitter,self.msgTypeID, self.paramID, self.msgCONTENT, self.msgDATE, self.msgPerm))
            # execute sql control
            self.cnx.commit()   
        
        # self.objectTX2DB()

    # def objectTX2DB(self):
    #     print("objectTX2DB")
     


# if __name__ == "__main__":
#     Receive_write()



