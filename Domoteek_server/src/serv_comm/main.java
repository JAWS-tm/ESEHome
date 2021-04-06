package serv_comm;

import java.io.InputStream;
import java.io.OutputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.List;

import java.io.IOException;

import dk.thibaut.serial.SerialPort;
import dk.thibaut.serial.enums.BaudRate;
import dk.thibaut.serial.enums.DataBits;
import dk.thibaut.serial.enums.Parity;
import dk.thibaut.serial.enums.StopBits;

import serial_dialog.Serial_dialog;



 public class main {
	 
		// JDBC Driver Name & Database URL
	    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
	    static final String JDBC_DB_URL = "jdbc:mysql://localhost:3306/Domoteek";
	 
	    // JDBC Database Credentials
	    static final String JDBC_USER = "root";
	    static final String JDBC_PASS = "";

	
	public static void main(String[] args) throws IOException, InterruptedException, ClassNotFoundException{
		
		
		
		// liste des port disponible
		List<String> portsNames = SerialPort.getAvailablePortsNames();
		System.out.println(portsNames);
		
		// ouverture du port COM8
		SerialPort port = SerialPort.open("COM8");
		//SerialPort portWrite = null;
		
		System.out.println("le port est ouvet");
		
		
		// Configuration de la connexion
		port.setTimeout(100);
		port.setConfig(BaudRate.B115200, Parity.NONE, StopBits.ONE, DataBits.D8);

		
		InputStream istream = port.getInputStream();
		
		OutputStream ostream = port.getOutputStream();
		
		/*
		 * connexion a la base de donnée
		 */
		try {
	    	Class.forName(JDBC_DRIVER);  
	        Connection connObj = DriverManager.getConnection(JDBC_DB_URL, JDBC_USER, JDBC_PASS);
	    
	    }catch(SQLException e) {
	    	
	    }
		
		
		while(true) {
			
			Serial_dialog.SERIAL_DIALOG_read(istream);
			
			
			 
			
		}
		
		
		
		/*
		 * gestion changement BDD
		 */
		
	}	

	

}
