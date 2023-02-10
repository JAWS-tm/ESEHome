                        ---- DbProcess directory ----

dbMessage : Gestion des message en base de donnée
-------------------------------------------------
def init(self, db, reciever, emitter, typeID...) : initialisation de l'émetteur et récepteur ainsi que de l'ID du message, paramètres, contenu, date...
def objectTX2DB(self) : TX objet : envoi du message
def objectRX2DB(self) : RX object : réception de message
def objectRM2DB(self) : envoi de suppression de message