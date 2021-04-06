package bdd;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import tables.Objet; 
public class Select {
	
	static Connection connexion ;
	
	public static void Objet() {
		try {
		    PreparedStatement preparedStatement = connexion.prepareStatement("SELECT * from Objet"); {
		            
		    	ResultSet resultSet = preparedStatement.executeQuery();
	            while (resultSet.next()) {
	                Objet objet = new Objet(0, 0, 0, 0, 0);
	                objet.setObjet_id(resultSet.getInt(1));
	                objet.setObjet_type(resultSet.getInt(2));
	                objet.setObjet_numero(resultSet.getInt(3));
	                objet.setObjet_appartenance(resultSet.getInt(4));
	                objet.setObjet_adresse(resultSet.getInt(5));
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
