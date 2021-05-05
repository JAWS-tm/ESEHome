package bdd;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import tables.Objet; 
public class Select {
	
	static Connection connexion ;
	
	public static void Objet() {
		byte variable_init_byte = 0 ;
		try {
		    PreparedStatement preparedStatement = connexion.prepareStatement("SELECT * from Objet"); {
		            
		    	ResultSet resultSet = preparedStatement.executeQuery();
	            while (resultSet.next()) {
	                Objet objet = new Objet(variable_init_byte, variable_init_byte, new byte [0], variable_init_byte, variable_init_byte, false);
	                objet.setObjet_id(resultSet.getByte(1));
	                objet.setObjet_type(resultSet.getByte(2));
	                objet.setObjet_numero(resultSet.getBytes(3));
	                objet.setObjet_appartenance(resultSet.getByte(4));
	                objet.setObjet_adresse(resultSet.getByte(5));
	                objet.setObjet_associer(resultSet.getBoolean(6));
	            }
		        System.out.println("");
	            System.out.println(preparedStatement);
	               
		    }
	        
	    }
	
	    catch (SQLException e) {
	    	e.printStackTrace();
	    }
	}

}
