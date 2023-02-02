import mysql.connector
##
# DO THIS ON DB.py
##
class MariaDBConnect:

    #initialisation of MariadB
    def __init__(self, bdd_config):
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

    #Creation of database
    def create_database(self):
        try:
            self.cursor.execute("CREATE DATABASE IF NOT EXISTS loggg")
            self.cnx.commit()
            self.cursor.execute("USE loggg")
            self.cnx.commit()
        except Exception as e:
            print("Error create database :", str(e))

    #Creation of tables
    def create_tables(self):
        self.cursor.execute("CREATE TABLE IF NOT EXISTS historique (id INT AUTO_INCREMENT PRIMARY KEY, date DATETIME NOT NULL, action VARCHAR(255) NOT NULL)")
        self.cnx.commit()
        self.cursor.execute("CREATE TABLE IF NOT EXISTS chiffrage (id INT AUTO_INCREMENT PRIMARY KEY, cle VARCHAR(255) NOT NULL, valeur VARCHAR(255) NOT NULL)")
        self.cnx.commit()
        self.cursor.execute("CREATE TABLE IF NOT EXISTS local (id INT AUTO_INCREMENT PRIMARY KEY, nom VARCHAR(255) NOT NULL, adresse VARCHAR(255) NOT NULL)")
        self.cnx.commit()

    #Close the connection when it's finish
    def close_connection(self):
        self.cursor.close()
        self.cnx.close()

#Main of the files, we call all the function here
if __name__ == "__main__":
    db = MariaDBConnect()
    db.create_database()
    db.create_tables()
    db.close_connection()