from db.dbRequest import dbRequest
from db.SQLRequest import addMessageSQLQuery, getMessageSQLQuery, removeMessageSQLQuery
from config.app_config import logger

class dbMessage:
    def __init__(self, db, frame):
        self.db = db
        self.objID = None # frame.getId
        self.objMSG = None # frame.getMessage
        self.objPerm = 1

    def objectTX2DB(self):
        # Extraire toutes les infos de la frame
        self.db.sendData(addMessageSQLQuery, (self.objID, self.objMSG, self.objPerm))

    def objectRX2DB(self):
        self.db.sendData(getMessageSQLQuery)
        for (objID, objMSG, objPerm) in self.db.getCursor():
            print("ObjectID : {}, Message : {}, Permanent : {}".format(objID, objMSG, objPerm))

    def objectRM2DB(self):
        self.db.sendData(removeMessageSQLQuery)
        


    