package bdd;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import serial_dialog.Data;

public class Bdd {

	
	static Connection connexion ;
	public static void insert_into(String [] data, String [] object_id) 
	{
		
		String int_object_id = object_id[3];
		
		
		loadDatabase();
	    
		for(int i = 0; i < Data.getSize_donnees(); i++) {
			try {
			    PreparedStatement preparedStatement = connexion.prepareStatement("INSERT INTO DATA(valeur_data, id_object)VALUES(?,?);"); {
			            preparedStatement.setString(1, data[i]);
			            preparedStatement.setString(2, int_object_id);
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
	
    private static void loadDatabase() {
        // Chargement du driver
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
        	 e.printStackTrace();
        }

        try {
        	 connexion = DriverManager.getConnection("jdbc:mysql://localhost:3306/Domoteek", "root", "");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

	

}
