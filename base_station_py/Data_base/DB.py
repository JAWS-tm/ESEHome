#Class DB connection here not on MariadB_Connect.py, passerelle, structure of trame

import mysql.connector
from multiprocessing import Process, Manager
from Data_base.Receive_write import Receive_write

class dBclass:
    
    #                       ------- INIT -------
    def __init__(self,bdd_config):
        self.nom = "----- DB class -----"
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
        
        self.create_database() #if database is not yet create
        self.create_tables()  #same for tables
        self.close_connection() #close db when all is finished



    #Creation of tables not for the web
    def create_tables(self):

        ## object_type
        self.cursor.execute('''CREATE TABLE IF NOT EXISTS object_type (
            id int(11) NOT NULL AUTO_INCREMENT,
            name varchar(100) NOT NULL, 
                PRIMARY KEY (id))
        ''')
        self.cnx.commit()
        ## Check si il y a déjà des données
        self.cursor.execute('''SELECT * FROM object_type''')
        # Transforme les données reçu en tableau, et s'il est vide, alors on ajoute les données
        data = self.cursor.fetchall() 
        if(data == []):
            self.cursor.execute('''INSERT INTO object_type (name) VALUES 
                ('OBJECT_BASE_STATION'),
                ('OBJECT_SMART_LIGHT'),
                ('OBJECT_NIGHT_LIGHT'),
                ('OBJECT_SMART_SOCKET'),
                ('OBJECT_BRIGHTNESS_SENSOR'),
                ('OBJECT_STATION_METEO_INT'),
                ('OBJECT_OUT_WEATHER_STATION'),
                ('OBJECT_ROLLER_SHUTTER'),
                ('OBJECT_ALARM'),
                ('OBJECT_FIRE_DETECTOR'),
                ('OBJECT_WINE_DEGUSTATION'),
                ('OBJECT_VENTILATOR'),
                ('OBJECT_GSM'),
                ('OBJECT_FALL_SENSOR'),
                ('OBJECT_WATER_LEVEL_DETECTOR'),
                ('OBJECT_AIR_SENSOR'),
                ('OBJECT_TRACKER_GPS'),
                ('OBJECT_RFID'),
                ('OBJECT_LCD_SLIDER'),
                ('OBJECT_VOICE_CONTROL'),
                ('OBJECT_TOUCH_SCREEN'),
                ('OBJECT_E_PAPER'),
                ('OBJECT_MATRIX_LEDS')
            ''')
            self.cnx.commit()  

        #object
        self.cursor.execute('''CREATE TABLE IF NOT EXISTS object (
            id int(11) NOT NULL AUTO_INCREMENT,
            physical_id varchar(8) NOT NULL UNIQUE,
            type_id int(11) NOT NULL,
            name varchar(30) NOT NULL,
            creation_date timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
            state bit NOT NULL,
                PRIMARY KEY (id),
                FOREIGN KEY (type_id) REFERENCES object_type(id))
        ''')
        
        self.cnx.commit()
        ## Check si il y a déjà des données
        self.cursor.execute('''SELECT * FROM object''')
        # Transforme les données reçu en tableau, et s'il est vide, alors on ajoute les données
        data = self.cursor.fetchall() 
        if(data == []):
            self.cursor.execute('''INSERT INTO object (physical_id, type_id, name, state) VALUES 
                ('00000000', 1, 'Station de base', 1),
                ('00000001', 2, 'Lumière', 0),
                ('00000002', 3, 'Lumière de nuit', 0),
                ('00000003', 4, 'Prise', 0),
                ('00000004', 5, 'Capteur de lumière', 0),
                ('00000005', 6, 'Station météo', 0),
                ('00000006', 7, 'Station météo exterieur', 1),
                ('00000007', 8, 'Volet roulant', 0),
                ('00000008', 9, 'Alarme', 0),
                ('00000009', 10, 'Détecteur incendie', 1),
                ('00000011', 12, 'Ventilateur', 0),
                ('00000012', 13, 'GSM', 0),
                ('00000013', 14, 'Détecteur de chute', 0),
                ('00000014', 15, 'Détecteur de niveau d''eau', 0),
                ('00000015', 16, 'Capteur d''air', 0),
                ('00000016', 17, 'Tracker GPS', 0)
            ''')
        self.cnx.commit()
        
        #message_type
        self.cursor.execute('''CREATE TABLE IF NOT EXISTS message_type (
            id int(11) NOT NULL AUTO_INCREMENT,
            name varchar(100) NOT NULL,
            hex_value varchar(2),
                PRIMARY KEY (id))
        ''')
        self.cnx.commit()
        ## Check si il y a déjà des données
        self.cursor.execute('''SELECT * FROM message_type''')
        # Transforme les données reçu en tableau, et s'il est vide, alors on ajoute les données
        data = self.cursor.fetchall() 
        if(data == []):
            self.cursor.execute('''INSERT INTO message_type (name, hex_value) VALUES
                ('RECENT_RESET', '02'),
                ('ASK_FOR_SOFTWARE_RESET', '03'),
                ('PING', '16'),
                ('PONG', '06'),
                ('EVENT_OCCURED', '30'),
                ('PARAMETER_IS', '40'),
                ('PARAMETER_ASK', '41'),
                ('PARAMETER_WRITE', '42'),
                ('I_HAVE_NO_SERVER_ID', 'FD'),
                ('YOUR_SERVER_ID_IS', 'FE')
            ''')
        self.cnx.commit()

        #message
        self.cursor.execute('''CREATE TABLE IF NOT EXISTS message (
            id int(11) NOT NULL AUTO_INCREMENT,
            recipient int(11) NOT NULL,
            transmitter int(11) NOT NULL,
            type_message int(11) NOT NULL,
            parameter_id int(11),
            data varchar(20) NOT NULL,
            date timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
            permanent bit NOT NULL DEFAULT 0,
            history bit NOT NULL DEFAULT 0,
                PRIMARY KEY (id),
                FOREIGN KEY (recipient) REFERENCES object(id),
                FOREIGN KEY (transmitter) REFERENCES object(id))
            ''')
        self.cnx.commit()
        ## Check si il y a déjà des données
        self.cursor.execute('''SELECT * FROM message''')
        # Transforme les données reçu en tableau, et s'il est vide, alors on ajoute les données
        data = self.cursor.fetchall() 
        if(data == []):
            self.cursor.execute('''INSERT INTO message (recipient, transmitter, type_message, parameter_id, data) VALUES 
                (9, 1, 8, 2, '01')
            ''')
        self.cnx.commit()

        # interface_type
        self.cursor.execute('''CREATE TABLE IF NOT EXISTS interface_type (
            id int(11) NOT NULL AUTO_INCREMENT,
            name varchar(30) NOT NULL,
                PRIMARY KEY (id))
        ''')
        self.cnx.commit()
        ## Check si il y a déjà des données
        self.cursor.execute('''SELECT * FROM interface_type''')
        # Transforme les données reçu en tableau, et s'il est vide, alors on ajoute les données
        data = self.cursor.fetchall() 
        if(data == []):
            self.cursor.execute('''INSERT INTO interface_type (name) VALUES  
                ('Seuil'),
                ('Affichage'),
                ('Switch'),
                ('Luminosité'),
                ('Selecteur'),
                ('Couleur')
            ''')
        self.cnx.commit()

        #param_types
        self.cursor.execute('''CREATE TABLE IF NOT EXISTS param_types (
            id int(11) NOT NULL AUTO_INCREMENT,
            name varchar(100) NOT NULL,
            hex_value varchar(2) NOT NULL,
            interface_type_id int(11),
                PRIMARY KEY (id),
                FOREIGN KEY (interface_type_id) REFERENCES interface_type(id))
        ''')
        self.cnx.commit()
        ## Check si il y a déjà des données
        self.cursor.execute('''SELECT * FROM param_types''')
        # Transforme les données reçu en tableau, et s'il est vide, alors on ajoute les données
        data = self.cursor.fetchall() 
        if(data == []):
            self.cursor.execute('''INSERT INTO param_types (name, hex_value, interface_type_id) VALUES 
                ('PARAM_UNKNOW', '00', NULL),
                ('PARAM_MY_BASE_STATION_ID', '01', 2),
                ('PARAM_ACTUATOR_STATE', '02', 3),
                ('PARAM_SENSOR_VALUE', '03', 1),
                ('PARAM_ALARM_TRESHOLD', '04', 1),
                ('PARAM_ALARM_WAY', '05', 5),
                ('PARAM_TEMPERATURE', '06', 2),
                ('PARAM_HYGROMETRY', '07', 2),
                ('PARAM_REFRESH_PERIOD', '08', 1),
                ('PARAM_PRESSURE', '09', 2),
                ('PARAM_BRIGHTNESS', '10', 4),
                ('PARAM_WINDSPEED', '11', 2),
                ('PARAM_PLUVIOMETRY', '12', 2),
                ('PARAM_SCREEN_COLOR', '13', 6),
                ('PARAM_MODE', '14', 5),
                ('PARAM_DURATION', '19', 1),
                ('PARAM_START_TIME', '16', 1),
                ('PARAM_STOP_TIME', '17', 1),
                ('PARAM_CURRENT_TIME', '18', 2),
                ('PARAM_TRESHOLD', '19', 1),
                ('PARAM_PM1_0', '20', NULL),
                ('PARAM_PM2_5', '21', NULL),
                ('PARAM_PM10', '22', NULL),
                ('PARAM_TEXT_PART0', '64', NULL),
                ('PARAM_TEXT_PART1', '65', NULL),
                ('PARAM_TEXT_PART2', '66', NULL),
                ('PARAM_TEXT_PART3', '67', NULL),
                ('PARAM_TEXT_PART4', '68', NULL),
                ('PARAM_TEXT_PART5', '69', NULL),
                ('PARAM_TEXT_PART6', '70', NULL),
                ('PARAM_TEXT_PART7', '71', NULL)
            ''')
        self.cnx.commit()

        #parameters
        self.cursor.execute('''CREATE TABLE IF NOT EXISTS parameters (
            id int(11) NOT NULL AUTO_INCREMENT,
            param_type_id int(11) NOT NULL,
            object_id int(11) NOT NULL,
            name varchar(30) NOT NULL,
            value varchar(30) NOT NULL,
            unit varchar(30),
                PRIMARY KEY (id),
                FOREIGN KEY (param_type_id) REFERENCES param_types(id),
                FOREIGN KEY (object_id) REFERENCES object(id))
            ''')
        self.cnx.commit()
        ## Check si il y a déjà des données
        self.cursor.execute('''SELECT * FROM parameters''')
        # Transforme les données reçu en tableau, et s'il est vide, alors on ajoute les données
        data = self.cursor.fetchall() 
        if(data == []):
            self.cursor.execute('''INSERT INTO parameters (name, param_type_id, object_id, value, unit) VALUES 
                ('Température', 7, 6, '15', '°C'),
                ('Mode', 15, 9, '15', NULL)
            ''')
        self.cnx.commit()
        
    #Creation of database
    def create_database(self):
        try:
            self.cursor.execute('''CREATE DATABASE IF NOT EXISTS esehome 
                DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci
            ''') # execute sql control
            self.cnx.commit()
            self.cursor.execute('''USE esehome''')
            self.cnx.commit()
        except Exception as e:
            print("Error create database :", str(e))
    
    #Close the connection when it's finish
    def close_connection(self):
        self.cursor.close()
        self.cnx.close()



# ---------- MAIN DB ----------   
## if name = main commenté, car l'appelle de la classe passe par l'init au début de la classe.
## C'est donc à ce moment qu'on lance les différentes fonctions.
 
# if __name__ == "__main__":
#     with Manager() as manager:
#         db = dBclass()
#         db.create_database() #if database is not yet create
#         db.create_tables()  #same for tables
#         #go to Receive_send send by Reponse
#         # Receive_write()
#         db.close_connection() #close db when all is finished

"""

//source : DB controller 

def put_message_in_bdd_sending_queue(self, msg : FrameParser):
next_msg = self.output_queue.put(msg)
logger.debug("Message has been put into database sending queue")


//source : DB request 

def sendData(self, request, data):
        self.cursor.execute(request, data)
        self.conn.commit()
        print(self.cursor)
    
    def receiveData(self, query):
        self.cursor.execute(query)
        return self.cursor.fetchall()

    def getCursor(self):
        return self.cursor

    def checkForNewMessage(self):
        potential_data = self.receiveData(getMessageSQLQuery)
        if(potential_data):
            for data in potential_data :
                self.put_message_in_queue(data)

    def put_message_in_queue(self, message):
        if(self.launched_as_thread):
            self.incoming_message_queue.put(message)
        else :
            print("ERROR : You didn't launch the uart reader as a thread (ref to the constructor)")
    
    def get_next_message(self):
        if(self.launched_as_thread):
            if(self.outgoing_message_queue.qsize()>0):
                return self.outgoing_message_queue.get()
            else :
                return None
        else :
            print("ERROR : You didn't launch the uart reader as a thread (ref to the constructor)")

#THREADING MAIN FUNCTION
def db_process_main_thread(user, password, host, port, DB_name, input_queue : Queue, output_queue : Queue):
    db = dbRequest(user, password, host, port, DB_name, True, input_queue, output_queue)
    #Set a timer to periodically check new messages
    schedule.every(0.25).minutes.do(db.checkForNewMessage)
    while True :
        time.sleep(0.5)
        try :
            schedule.run_pending() #ie check for new messages from DB
            msg_to_send = db.get_next_message()#Checks if there is a message to send
            if(msg_to_send):#Msg to send should be a FrameParser object
                #Send request to BDD
                new_msg = dbMessage(db, msg_to_send.getReceiver(), msg_to_send.getEmitter() , msg_to_send.getId(), msg_to_send.getParamID(), msg_to_send.getData(), datetime.datetime.now() ,True)
                new_msg.objectTX2DB()
        except Exception as e:
            logger.error("DATABASE THREAD ERROR : "+str(e))

"""
