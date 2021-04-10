package bdd;

import java.io.IOException;
import java.io.OutputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Properties;

import serial_dialog.*;


import tables.*;


public class Bdd {
	
	static Connection connexion ;
	
	private static final int message_en_attente = 0;
	
	private static final int I_HAVE_NO_SERVER_ID = 0xFD;
		
	private static final int YOUR_SERVER_ID_IS = 0xFE;
	
	public static void Bdd_process_msg(OutputStream ostream) throws IOException {
		byte size = 0;
		byte [] datas = new byte[0];
		byte variable_init_byte = 0 ;
				// si le message est un message I_HAVE_NO_SERVER_ID 
				if( Data.getMsg() == I_HAVE_NO_SERVER_ID) {
					try {
					    PreparedStatement preparedStatement = connexion.prepareStatement("SELECT * from Objet"); {
					        // on parcourt toute la table d'objet pour savoir si l'objet est connu ou pas 
					    	ResultSet resultSet = preparedStatement.executeQuery();
				            while (resultSet.next()) {
				                Objet objet = new Objet(variable_init_byte , variable_init_byte, new byte[0], variable_init_byte, variable_init_byte, false);
				                objet.setObjet_id(resultSet.getByte(1));
				                objet.setObjet_type(resultSet.getByte(2));
				                objet.setObjet_numero(resultSet.getBytes(3));
				                objet.setObjet_appartenance(resultSet.getByte(4));
				                objet.setObjet_adresse(resultSet.getByte(5));
				                objet.setObjet_associer(resultSet.getBoolean(6));
				                
				                // si l'objet est connu et s'il est associé on le retire de la liste des objet associer (false)
				                if(Data.getEmetteur() == objet.getObjet_numero() && objet.getObjet_associer() == true) {
									
										PreparedStatement preparedStatement2 = connexion.prepareStatement(
												  "UPDATE Objet"
												+ "SET objet_associer = 'false'"
												+ "WHERE objet_numero = ?;");{
												
													preparedStatement.setBytes(1, objet.getObjet_numero());
													preparedStatement2.executeUpdate();
												}
									
								// sinon cela veux dire qu'il s'agit d'un nouvel objet que l'on doit inserer dans la table Objet	
								}else {
									//TODO : insertion du nouvel objet dans la table
			
									//Insert_into.Objet(objet_type,Data.getEmetteur(), objet_appartenance, objet_adresse, true);

									//size = 0x0B;
									//datas = {0x00, 0x00, 0x00, 0x02, 0xEE, 0xEE,0xEE, 0x00, 0xA2, 0x42, 0x05, 0x08, 0xCA, 0xFE, 0xDE, 0xCA}; // message YOUR_SERVER-ID_IS...
									//envoi du message YOUR_SERVER_ID_IS...
									Serial_dialog.SERIAL_DIALOG_send_msg(size, datas, ostream);
								}
				                
				                
				                
				            }
				               
					    }
				        
				    }
				
				    catch (SQLException e) {
				    	e.printStackTrace();
				    }
					
					
				// sinon le message reçu est un message qui concerne un paramètre 	
				}else {
					
				byte parametre_id = 0;
					Insert_into.Parametre( Data.getType_donnees(), Data.getDonnees(),  Data.getEmetteur());
					try {
					    PreparedStatement preparedStatement = connexion.prepareStatement("SELECT * from Regle"); {
					        // on parcourt toute la table d'objet pour savoir si l'objet est connu ou pas 
					    	ResultSet resultSet = preparedStatement.executeQuery();
					    	while (resultSet.next()) {
				                Regle regle = new Regle(variable_init_byte,variable_init_byte,variable_init_byte,
				                		variable_init_byte,variable_init_byte,variable_init_byte,variable_init_byte);
				                regle.setRegel_id(resultSet.getByte(1));
				                regle.setRegle_operand_1(resultSet.getByte(2));
				                regle.setRegle_operateur(resultSet.getByte(3));
				                regle.setRegle_operand_2(resultSet.getByte(4));
				                regle.setRegle_action_parametre(resultSet.getByte(5));
				                regle.setRegle_action_value(resultSet.getByte(6));
				                regle.setParametre_id(resultSet.getByte(7));
				                
				                //TODO : récupérer parametre_id
				                
				                if (regle.getParametre_id() == parametre_id) {
				                	
				                	// TODO :  effectuer la règle liée au parametre
				                 
				                }
					    	}
					    }
					
					}catch (SQLException e) {
						e.printStackTrace();
			    	}

				}
				
	}


}

