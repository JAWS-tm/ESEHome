import mysql.connector

class MariaDBConnect:
    def __init__(self):
        self.cnx = mysql.connector.connect(
            host="localhost",
            user="root",
            passwd="password"
        )
        self.cursor = self.cnx.cursor()

    def create_database(self):
        self.cursor.execute("CREATE DATABASE IF NOT EXISTS loggg")
        self.cursor.execute("USE loggg")

    def create_tables(self):
        self.cursor.execute("CREATE TABLE IF NOT EXISTS historique (id INT AUTO_INCREMENT PRIMARY KEY, date DATETIME NOT NULL, action VARCHAR(255) NOT NULL)")
        self.cursor.execute("CREATE TABLE IF NOT EXISTS chiffrage (id INT AUTO_INCREMENT PRIMARY KEY, cle VARCHAR(255) NOT NULL, valeur VARCHAR(255) NOT NULL)")
        self.cursor.execute("CREATE TABLE IF NOT EXISTS local (id INT AUTO_INCREMENT PRIMARY KEY, nom VARCHAR(255) NOT NULL, adresse VARCHAR(255) NOT NULL)")
        self.cnx.commit()

    def close_connection(self):
        self.cursor.close()
        self.cnx.close()

if __name__ == "__main__":
    db = MariaDBConnect()
    db.create_database()
    db.create_tables()
    db.close_connection()