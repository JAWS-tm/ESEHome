from db.dbRequest import dbRequest
from db.SQLRequest import addMessageSQLQuery, getMessageSQLQuery, removeMessageSQLQuery
from config.app_config import logger

class dbMessage:
    def __init__(self, db, typeID, msg, date, perm):
        self.db = db
        self.msgTypeID = typeID # frame.getId
        self.msgCONTENT = msg # frame.getMessage
        self.msgDATE = date # frame.getDate
        self.msgPerm = perm

    def objectTX2DB(self):
        # Extraire toutes les infos de la frame
        self.db.sendData(addMessageSQLQuery, (self.msgTypeID, self.msgCONTENT, self.msgDATE, self.msgPerm))

    def objectRX2DB(self):
        self.db.recieveData(getMessageSQLQuery)
        for (msgTypeID, msgCONTENT, msgDATE, msgPerm) in self.db.getCursor():
            print("Type ID : {}, Message : {}, Date : {}, Permanent : {}".format(msgTypeID, msgCONTENT, msgDATE, msgPerm))

    def objectRM2DB(self):
        self.db.sendData(removeMessageSQLQuery)
        


    