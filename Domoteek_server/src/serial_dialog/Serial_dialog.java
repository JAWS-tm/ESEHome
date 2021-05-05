package serial_dialog;


import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import java.sql.Connection;

import bdd.Bdd;
import bdd.Insert_into;
import bdd.Select;

public class Serial_dialog {
	
	private static final byte SOH = (byte) 0xBA;
	private static final byte EOT = (byte) 0xDA;
	
	private static int BUFFER_SIZE = 128;
	
	private static byte [] datas = new byte[255];
	private static boolean flag_FA = false;
	private static int index = 0;
	private static byte size = 0;
	

	 private Connection connection;
	
	public static void SERIAL_DIALOG_parse_rx(byte c)
	{

		switch(index)
		{
			case 0:
				if(c == SOH)
					index++;
				break;
			case 1:
				size = c;
				index++;
				break;
			default:
				if(index-2 == size)
				{
					if(c == EOT)
						//ok, fin du message !
						
						Data.data_parse(datas, size);
						System.out.println("");
					index = 0;
				}
				else if(flag_FA)
				{
					datas[index-2] = (byte) (c&0xFA);
					flag_FA = false;
					index++;
				}
				else if(c == 0xFA)
					flag_FA = true;		//on ne touche pas à l'index, le prochain caractère sera compté et pris en compte avec le masque &0xFA
				else if(c == SOH)
					index = 1;
				else if(c == EOT)
					index = 0;
				else if(index-2 < size)
				{
					datas[index-2] = c;
					index++;
				}
				else
					index = 0;
				break;
		}
	}
	
				
	
	public static void SERIAL_DIALOG_send_msg(byte size, byte [] datas, OutputStream ostream) throws IOException
	{
		byte i;
		byte c;
		if(size > 0 && datas == null)
			return;
		ostream.write(SOH);
		ostream.write(size);

		for(i=0; i<size; i++)
		{
			c = datas[i];
			if(c == 0xBA || c == 0xDA || c == 0xFA)		//si l'octet à transmettre est 0xBA, 0xDA, 0xFA
			{
				ostream.write(0xFA);	//on transmet 0xFA...
				ostream.write(c|0x0F);	//suivi de 0xBF, 0xDF ou 0xFF
								
			}
			else
				ostream.write(c);				//sinon, on transmets c directement
		}
		ostream.write(EOT);	//EOT
	}
	

	private static Thread th = new Thread();
	
	public static void SERIAL_DIALOG_read(InputStream istream)throws  IOException, InterruptedException{
		//Déclaration d'un buffer de 128 caractères
		
				byte[] byteBuffer = new byte[BUFFER_SIZE];
				
				//déclaration d'un index initialisé à 0
				int index_buffer = 0;
				int i = 0;


					//Lecture des octets reçus sur le port série depuis notre dernier passage ici
					index_buffer = istream.read(byteBuffer, 0, BUFFER_SIZE);
					

					for(i=0; i < index_buffer; i++)
					{
					 	
					 	//on viens traiter chaque octet que l'on reçoit sur le port serie
					 	SERIAL_DIALOG_parse_rx(byteBuffer[i]);
					 	
					}
					th.sleep(10);
	
	}
	
	public static void SERIAL_DIALOG_write(OutputStream ostream)throws  IOException
	{
		/*
		 * quand la bdd sera faite il faudra que datas soit remplis avec les donné qui en sorte. 
		 * pour size la meme chose.
		 */
		//byte size = 16;
		//byte [] datas = {0x00, 0x00, 0x00, 0x02, 0xEE, 0xEE,0xEE, 0x00, 0xA2, 0x42, 0x05, 0x08, 0xCA, 0xFE, 0xDE, 0xCA};
		// à remplacer par la donnée qui sera recup dans la bdd
		
		SERIAL_DIALOG_send_msg(size, datas, ostream);
	}
	
	public static enum statut_message{

		KEEP_ALWAYS_NOT_SENT,
		KEEP_ALWAYS_ALREADY_SENT,
		KEEP_ALWAYS_ACKNOWLEDGED,
		ONLY_ONCE_NOT_SENT,
		ONLY_ONCE_SENT,
		TRANSMITTED 

	}
	
	
	
}
