CREATE DATABASE  Domoteek ;
USE Domoteek ;


#------------------------------------------------------------
# Table: Objet
#------------------------------------------------------------

CREATE TABLE Objet(
        objet_id           Int  Auto_increment  NOT NULL ,
        objet_type         VARBINARY (32) NOT NULL ,
        objet_numero       Int NOT NULL ,
        objet_appartenance VARBINARY (32) NOT NULL ,
        objet_adresse      Int NOT NULL 
	,CONSTRAINT Objet_PK PRIMARY KEY (objet_id)
)ENGINE=InnoDB;

#------------------------------------------------------------
# Table: Regle
#------------------------------------------------------------


CREATE TABLE Regle(
        regle_id               Int  Auto_increment  NOT NULL ,
        regle_operand_1        VARBINARY (32) NOT NULL ,
        regle_operateur        VARBINARY (32) NOT NULL ,
        regle_operand_2        VARBINARY (32) NOT NULL ,
        regle_action_parametre VARBINARY (32) NOT NULL ,
        regle_action_value     VARBINARY (32) NOT NULL
	,CONSTRAINT Regle_PK PRIMARY KEY (regle_id)
)ENGINE=InnoDB;

#------------------------------------------------------------
# Table: Parametre
#------------------------------------------------------------

CREATE TABLE Parametre(
        parametre_id      Int  Auto_increment  NOT NULL ,
        parametre_type    VARBINARY (32) NOT NULL ,
        parametre_contenu VARBINARY (32) NOT NULL ,
        objet_id          Int NOT NULL
	,CONSTRAINT Parametre_PK PRIMARY KEY (parametre_id)
    /*
	 * Clés étrangères
	 */
	,CONSTRAINT Parametre_Objet_FK FOREIGN KEY (objet_id) REFERENCES Objet(objet_id)
)ENGINE=InnoDB;

#------------------------------------------------------------
# Table: Boite_reception
#------------------------------------------------------------

CREATE TABLE Boite_reception(
        boite_reception_id Int  Auto_increment  NOT NULL ,
		objet_id           Int NOT NULL 
	,CONSTRAINT Boite_reception_PK PRIMARY KEY (boite_reception_id)
	/*
	* Clés étrangères
	*/
	,CONSTRAINT Boite_reception_Objet_FK FOREIGN KEY (objet_id) REFERENCES Objet(objet_id)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: Boite_envoi
#------------------------------------------------------------

CREATE TABLE Boite_envoi(
        boite_envoi_id Int  Auto_increment  NOT NULL ,
		objet_id           Int NOT NULL 
	,CONSTRAINT Boite_envoi_PK PRIMARY KEY (boite_envoi_id)
	
	/*
	* Clés étrangères
	*/
	,CONSTRAINT Boite_envoi_Objet_FK FOREIGN KEY (objet_id) REFERENCES Objet(objet_id)
)ENGINE=InnoDB;



#------------------------------------------------------------
# Table: Message
#------------------------------------------------------------

CREATE TABLE Message(
        message_id                          Int  Auto_increment  NOT NULL ,
        message_statut                      VARBINARY (32) NOT NULL ,
        message_contenu                     VARBINARY (32) NOT NULL ,
        message_date_envoi                  Date ,
        message_date_reception_acquittement Date 
	,CONSTRAINT Message_PK PRIMARY KEY (message_id)
)ENGINE=InnoDB;

#------------------------------------------------------------
# Table: Stocker
#------------------------------------------------------------

CREATE TABLE Stocker(
        boite_reception_id Int ,
        boite_envoi_id     Int ,
        message_id         Int ,
        stocker_qte        Int
	,CONSTRAINT Stocker_PK PRIMARY KEY (boite_reception_id,boite_envoi_id,message_id)
	/*
	* Clés étrangères
	*/
	,CONSTRAINT Stocker_Boite_reception_FK FOREIGN KEY (boite_reception_id) REFERENCES Boite_reception(boite_reception_id)
	,CONSTRAINT Stocker_Boite_envoi_FK FOREIGN KEY (boite_envoi_id) REFERENCES Boite_envoi(boite_envoi_id)
	,CONSTRAINT Stocker_Message_FK FOREIGN KEY (message_id) REFERENCES Message(message_id)
)ENGINE=InnoDB;



/*
* test insertion donnée dans la base
*/ 


INSERT INTO Objet (objet_type, objet_numero, objet_appartenance, objet_adresse)Value('16', 15, '1', 156);

INSERT INTO Boite_envoi(objet_id)VALUE(1);

INSERT INTO Boite_reception(objet_id)VALUE(1);

INSERT INTO Message(message_statut, message_contenu)VALUE('test_statut','test_message')

INSERT INTO Stocker(boite_reception_id, boite_envoi_id, message_id) VALUE(1,1,1);