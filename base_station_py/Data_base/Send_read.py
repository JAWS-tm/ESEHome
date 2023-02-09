
# This class is used to read the message in the data base to send it to DB.py trhoug a dictionary.
class Send_read:




#def objectRX2DB(self):
        #self.db.receiveData(getMessageSQLQuery)
        #for c in self.db.getCursor():
           #print(c)

    """def __init__(self,bdd_config):
        self.nom = "----- DBwrite functions -----"
        #connection to db
        print("--- Connection DB ---")
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

    ## Function add data to table in DB
    def addDataToTable(self, data, table):
        self.cursor.execute("INSERT INTO "+table+" VALUES "+data+";") # execute sql control
        self.cnx.commit()"""
