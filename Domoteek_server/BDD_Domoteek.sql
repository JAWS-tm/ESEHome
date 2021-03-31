CREATE DATABASE  Domoteek ;
USE Domoteek ;

/*
 * Table
 */

CREATE TABLE Object(
        id_object       Int  Auto_increment  NOT NULL ,
        nom_object      Varchar(50) NOT NULL , 
	CONSTRAINT Object_PK PRIMARY KEY (id_object)
)ENGINE=innoDB;


CREATE TABLE Data(
        id_data          Int  Auto_increment  NOT NULL ,
        valeur_data      Varchar (50) NOT NULL ,
        id_object        Int ,
	CONSTRAINT Data_PK PRIMARY KEY (id_data)
)ENGINE=innoDB;

/*
 * Clé étrangère
 */

ALTER TABLE Data
ADD CONSTRAINT fk_id_object_id_data FOREIGN KEY (id_object) REFERENCES Object(id_object);


INSERT INTO Object(nom_object)VALUES("tracker_GPS");