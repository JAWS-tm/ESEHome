package bdd;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import serial_dialog.Data;

public class Inert_into {

static Connection connexion ;
	
	
	public static void Objet(int objet_type,int objet_numero, int objet_appartenance, int objet_adresse) {
		
	    
		for(int i = 0; i < Data.getSize_donnees(); i++) {
			try {
			    PreparedStatement preparedStatement = connexion.prepareStatement("INSERT INTO Objet (objet_type, objet_numero, objet_appartenance, objet_adresse)Value(?, ?, ?, ?);"); {
			            preparedStatement.setInt(1, objet_type );
			            preparedStatement.setInt(2, objet_numero);
			            preparedStatement.setInt(3, objet_appartenance);
			            preparedStatement.setInt(4, objet_adresse);
			            
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
	
	
	public static void Regle(int regle_operand_1, int regle_operateur, int regle_operand_2, int regle_action_parametre, int regle_action_value) {
		

		for(int i = 0; i < Data.getSize_donnees(); i++) {
			try {
			    PreparedStatement preparedStatement = connexion.prepareStatement("INSERT INTO Regle (regle_operand_1, regle_operateur, regle_operand_2, regle_action_parametre, regle_action_value)Value(?, ?, ?, ?, ?);"); {
			            preparedStatement.setInt(1, regle_operand_1 );
			            preparedStatement.setInt(2, regle_operateur);
			            preparedStatement.setInt(3, regle_operand_2);
			            preparedStatement.setInt(4, regle_action_parametre);
			            preparedStatement.setInt(5, regle_action_value);
			            
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
	
	public static void Parametre(int parametre_type, int parametre_contenu, int objet_id) {
		
		
		
	    
		for(int i = 0; i < Data.getSize_donnees(); i++) {
			try {
			    PreparedStatement preparedStatement = connexion.prepareStatement("INSERT INTO Parametre (parametre_type, parametre_contenu, objet_id)Value(?, ?, ?);"); {
			            preparedStatement.setInt(1, parametre_type );
			            preparedStatement.setInt(2, parametre_contenu);
			            preparedStatement.setInt(3, objet_id);
			            
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
	
	public static void Boite_reception(int objet_id) {
		
		

	    
		for(int i = 0; i < Data.getSize_donnees(); i++) {
			try {
			    PreparedStatement preparedStatement = connexion.prepareStatement("INSERT INTO Boite_reception (objet_id)Value(?);"); {
			            preparedStatement.setInt(1, objet_id );
			            
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
	
public static void Boite_envoi(int objet_id) {
		
		

	    
		for(int i = 0; i < Data.getSize_donnees(); i++) {
			try {
			    PreparedStatement preparedStatement = connexion.prepareStatement("INSERT INTO Boite_envoi (objet_id)Value(?);"); {
			            preparedStatement.setInt(1, objet_id );
			            
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
	
	public static void Message(int message_statut, int message_contenu, int message_date_envoi, int objet_adresse) {
		
		
		
	    
		for(int i = 0; i < Data.getSize_donnees(); i++) {
			try {
			    PreparedStatement preparedStatement = connexion.prepareStatement("INSERT INTO Objet (message_statut, message_contenu, message_date_envoi, message_date_reception_acquittement)Value(?, ?, ?, ?);"); {
			            preparedStatement.setInt(1, message_statut );
			            preparedStatement.setInt(2, message_contenu);
			            preparedStatement.setInt(3, message_date_envoi);
			            preparedStatement.setInt(4, objet_adresse);
			            
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
	
public static void Stocker(int boite_reception_id, int boite_envoi_id, int message_id, int stocker_qte) {
		
		
		
	    
		for(int i = 0; i < Data.getSize_donnees(); i++) {
			try {
			    PreparedStatement preparedStatement = connexion.prepareStatement("INSERT INTO Stocker (boite_reception_id, boite_envoi_id, message_id, stocker_qte)Value(?, ?, ?, ?);"); {
			            preparedStatement.setInt(1, boite_reception_id );
			            preparedStatement.setInt(2, boite_envoi_id);
			            preparedStatement.setInt(3, message_id);
			            preparedStatement.setInt(4, stocker_qte);
			            
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
}
