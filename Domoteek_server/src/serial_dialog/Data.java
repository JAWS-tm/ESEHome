package serial_dialog;

public class Data {
	
	private static byte [] destinataire = new byte[4];
	private static byte [] emetteur = new byte [4]; 
	private static byte cnt = 0; 
	private static byte msg = 0; 
	private static byte size_donnees = 0 ; 
	private static byte type_donnees = 0 ;
	private static byte [] donnees = new byte [16]; 
	
	public static void data_parse(byte [] datas, byte size) {
		
		/*
		 * destinataire
		 */
		//String str_destinataire = null ;
		System.out.print("destinataire : ");
		for(int i=0; i<4; i++) {
			destinataire[i] = datas[i];
			//str_destinataire = Integer.toHexString(destinataire[i]);
			
			System.out.print(destinataire[i]+", ");
		}
		
		System.out.println("");

			
		/*
		 * émetteur
		 */
		//String str_emetteur = null;
		System.out.print("émetteur : ");
		for(int i = 0; i<4; i++)
		{
			emetteur[i] = datas[i+4];
			//str_emetteur = Integer.toHexString(emetteur[i]);
			System.out.print(emetteur[i] + ", ");
			
		}
		
		System.out.println("");
		
		
		/*
		 * cnt
		 */
		//String str_cnt = null;
		cnt = datas[8];
		//str_cnt = Integer.toHexString(cnt);
		System.out.println("cnt : "  +cnt);
	
		/*
		 * msg
		 */
		msg = datas[9];
		System.out.println("msg : " +msg);
		
		/*
		 * size
		 */
		size_donnees = datas[10];
		System.out.println("size : "  + size_donnees);
		
		/*
		 * Type de données
		 */
		type_donnees = datas[11];
		System.out.println("type de données : "  + type_donnees);
		/*
		 * Données
		 */
		
		int index_donnees = 0;
		String str_donnees = null;
		System.out.print("données : ");
		for(int i = 12; i < size; i++) {
			donnees[index_donnees] = datas[i];
			str_donnees = Integer.toHexString(donnees[index_donnees]);
			System.out.print(donnees[index_donnees]+ " , ");
			index_donnees++;
		}
		System.out.println("");
		      

		
	}	
		
	
	
	public static byte [] getDestinataire() {
        return destinataire;
    }
	public static byte [] getEmetteur() {	
        return emetteur;
    }
	public static byte getCnt() {
        return cnt;
    }
	public static byte getMsg() {
        return msg;
    }
	public static byte getSize_donnees() {
        return size_donnees ;
    }
	public static byte getType_donnees() {
		return type_donnees ;
	}
	public static byte[] getDonnees() {
        return donnees ;
    }
	
	
    

}
