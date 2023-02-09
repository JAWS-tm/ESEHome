import Main
#This class is used to receivre a dictionary (containing the frame) from "Response" to write it inside the DataBase.
class Receive_write:
    #                       ------- INIT -------
    def __init__(self, db, reciever, emitter, typeID, paramID, msg, date, perm, history):
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
        
    #                       ---------- Functions ----------

    def recieve_uart_tram():
        precedentDico = {}
        print(Main.tram_dico)

        while True:


            if(Main.tram_dico == precedentDico):
                # Le dictionnaire n'a pas été mis à jour, donc on ne fait rien
                print("dico pas changé")
            else:
                # le dico est différent, il a été mis à jour, on peut donc les envoyer dans la BDD
                print("dico changé")


    #def write_uart_tram():

    def objectTX2DB(self):
        # Extraire toutes les infos de la frame
        self.db.sendData(addMessageSQLQuery, (self.receiver, self.emitter,self.msgTypeID, self.paramID, self.msgCONTENT, self.msgDATE, self.msgPerm))
        logger.debug("Request successfully sent to DataBase")
    
    def objectRM2DB(self):
        self.db.sendData(removeMessageSQLQuery)

if __name__ == "__main__":
    write = Receive_write()
    write.recieve_uart_tram()



