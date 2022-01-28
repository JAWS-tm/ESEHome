from db import dbRequest
from db.SQLRequest import addMessageSQLQuery, getMessageSQLQuery, removeMessageSQLQuery
from config.app_config import logger

class dbMessage:
    def __init__(self, db, reciever, emitter, typeID, paramID, msg, date, perm):
        self.db = db
        self.receiver = reciever
        self.emitter = emitter
        self.msgTypeID = typeID # frame.getId
        self.paramID = paramID
        self.msgCONTENT = msg # frame.getMessage
        self.msgDATE = date # frame.getDate
        self.msgPerm = perm

    def objectTX2DB(self):
        # Extraire toutes les infos de la frame
        self.db.sendData(addMessageSQLQuery, (self.receiver, self.emitter,self.msgTypeID, self.paramID, self.msgCONTENT, self.msgDATE, self.msgPerm))
        logger.debug("Request successfully sent to DataBase")

    def objectRX2DB(self):
        self.db.receiveData(getMessageSQLQuery)
        for c in self.db.getCursor():
           print(c)

    def objectRM2DB(self):
        self.db.sendData(removeMessageSQLQuery)
        


    