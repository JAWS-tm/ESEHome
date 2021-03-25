package serv_comm;

import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.IOException;


import dk.thibaut.serial.SerialConfig;
import dk.thibaut.serial.SerialPort;
import dk.thibaut.serial.enums.BaudRate;
import dk.thibaut.serial.enums.DataBits;
import dk.thibaut.serial.enums.Parity;
import dk.thibaut.serial.enums.StopBits;

import serial_dialog.Serial_dialog;

 

 public class main {

	 
	
	public static void main(String[] args) throws IOException, InterruptedException{
		
		
		
		// liste des port disponible
		List<String> portsNames = SerialPort.getAvailablePortsNames();
		System.out.println(portsNames);
		
		// ouverture du port COM8
		SerialPort port = SerialPort.open("COM8");
		System.out.println("le port est ouvet");
		
		
		// Configuration de la connexion
		port.setTimeout(100);
		port.setConfig(BaudRate.B115200, Parity.NONE, StopBits.ONE, DataBits.D8);

		
		InputStream istream = port.getInputStream();
		
		OutputStream ostream = port.getOutputStream();
		

		
		while(true) {
			Serial_dialog.SERIAL_DIALOG_read(istream);
		}
		
			
		
		
		
	}

	

}
