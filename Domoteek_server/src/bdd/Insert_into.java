package bdd;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import serial_dialog.Data;

public class Insert_into {

static Connection connexion ;
	
	
	public static void Objet(byte objet_type,byte []objet_numero, byte objet_appartenance, byte objet_adresse, boolean objet_associer) {
		
	    
			try {
			    PreparedStatement preparedStatement = connexion.prepareStatement("INSERT INTO Objet (objet_type, objet_numero, objet_appartenance, objet_adresse, objet_associer)Value(?, ?, ?, ?, ?);"); {
			            preparedStatement.setByte(1, objet_type );
			            preparedStatement.setBytes(2, objet_numero);
			            preparedStatement.setByte(3, objet_appartenance);
			            preparedStatement.setByte(4, objet_adresse);
			            preparedStatement.setBoolean(5,objet_associer);
			            
			            System.out.println("");
			            System.out.println(preparedStatement);
			            preparedStatement.executeUpdate();   
			    }
		        
		    }
		
		    catch (SQLException e) {
		    	e.printStackTrace();
		    }
			
		
	}
	
	
	public static void Regle(byte regle_operand_1, byte regle_operateur, byte regle_operand_2, byte regle_action_parametre, byte regle_action_value) {
		
		
			try {
			    PreparedStatement preparedStatement = connexion.prepareStatement("INSERT INTO Regle (regle_operand_1, regle_operateur, regle_operand_2, regle_action_parametre, regle_action_value)Value(?, ?, ?, ?, ?);"); {
			            preparedStatement.setByte(1, regle_operand_1 );
			            preparedStatement.setByte(2, regle_operateur);
			            preparedStatement.setByte(3, regle_operand_2);
			            preparedStatement.setByte(4, regle_action_parametre);
			            preparedStatement.setByte(5, regle_action_value);
			            
			            System.out.println("");
			            System.out.println(preparedStatement);
			            preparedStatement.executeUpdate();   
			    }
		        
		    }
		
		    catch (SQLException e) {
		    	e.printStackTrace();
		    }
			
		
	}
	
	public static void Parametre(byte parametre_type, byte [] parametre_contenu, byte []objet_id) {

		
			try {
			    PreparedStatement preparedStatement = connexion.prepareStatement("INSERT INTO Parametre (parametre_type, parametre_contenu, objet_id)Value(?, ?, ?);"); {
			            preparedStatement.setByte(1, parametre_type );
			            preparedStatement.setBytes(2, parametre_contenu);
			            preparedStatement.setBytes(3, objet_id);
			            
			            System.out.println("");
			            System.out.println(preparedStatement);
			            preparedStatement.executeUpdate();   
			    }
		        
		    }
		
		    catch (SQLException e) {
		    	e.printStackTrace();
		    }
			
		
	}
	
	public static void Boite_reception(byte objet_id) {
		

			try {
			    PreparedStatement preparedStatement = connexion.prepareStatement("INSERT INTO Boite_reception (objet_id)Value(?);"); {
			            preparedStatement.setByte(1, objet_id );
			            
			            System.out.println("");
			            System.out.println(preparedStatement);
			            preparedStatement.executeUpdate();   
			    }
		        
		    }
		
		    catch (SQLException e) {
		    	e.printStackTrace();
		    }
			
	}
	
	public static void Boite_envoi(byte objet_id) {
		

			try {
			    PreparedStatement preparedStatement = connexion.prepareStatement("INSERT INTO Boite_envoi (objet_id)Value(?);"); {
			            preparedStatement.setByte(1, objet_id );
			            
			            System.out.println("");
			            System.out.println(preparedStatement);
			            preparedStatement.executeUpdate();   
			    }
		        
		    }
		
		    catch (SQLException e) {
		    	e.printStackTrace();
		    }
			
	}
	
	public static void Message(byte message_statut, byte message_contenu, byte message_date_envoi, byte objet_adresse) {
		

			try {
			    PreparedStatement preparedStatement = connexion.prepareStatement("INSERT INTO Objet (message_statut, message_contenu, message_date_envoi, message_date_reception_acquittement)Value(?, ?, ?, ?);"); {
			            preparedStatement.setByte(1, message_statut );
			            preparedStatement.setByte(2, message_contenu);
			            preparedStatement.setByte(3, message_date_envoi);
			            preparedStatement.setByte(4, objet_adresse);
			            
			            System.out.println("");
			            System.out.println(preparedStatement);
			            preparedStatement.executeUpdate();   
			    }
		        
		    }
		
		    catch (SQLException e) {
		    	e.printStackTrace();
		    }
			
	}
	
	public static void Stocker(byte boite_reception_id, byte boite_envoi_id, byte message_id, byte stocker_qte) {
		

			try {
			    PreparedStatement preparedStatement = connexion.prepareStatement("INSERT INTO Stocker (boite_reception_id, boite_envoi_id, message_id, stocker_qte)Value(?, ?, ?, ?);"); {
			            preparedStatement.setByte(1, boite_reception_id );
			            preparedStatement.setByte(2, boite_envoi_id);
			            preparedStatement.setByte(3, message_id);
			            preparedStatement.setByte(4, stocker_qte);
			            
			            System.out.println("");
			            System.out.println(preparedStatement);
			            preparedStatement.executeUpdate();   
			    }
		        
		    }
		
		    catch (SQLException e) {
		    	e.printStackTrace();
		    }
			
	}
}
