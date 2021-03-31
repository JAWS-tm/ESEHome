package serial_dialog;

public class Data {
	
	private static String [] destinataire = new String [4];
	private static String [] emetteur = new String [4]; 
	private static String cnt = null; 
	private static String msg = null; 
	private static int size_donnees = 0 ; 
	private static String [] donnees = new String [16]; 
	
	public static void data_parse(int [] datas, int size) {
		
		/*
		 * destinataire
		 */
		
		System.out.print("destinataire : ");
		for(int i = 0; i < 4 ; i++){
			destinataire[i] = Integer.toHexString(datas[i]);
			System.out.print("0x" + destinataire[i] + " , ");
		}
		System.out.println("");
		
		/*
		 * émetteur
		 */
		int index_emetteur = 0;
		System.out.print("émetteur : ");
		for(int i = 4; i < 8; i++){
			emetteur[index_emetteur] = Integer.toHexString(datas[i]);
			System.out.print("0x" +emetteur[index_emetteur]+ " , ");
			index_emetteur++;
		}
		System.out.println("");
		
		/*
		 * cnt
		 */
		
		cnt = Integer.toHexString(datas[8]);
		System.out.println("cnt : " + "0x" +cnt);
	
		/*
		 * msg
		 */
		msg = Integer.toHexString(datas[9]);
		System.out.println("msg : " + "0x" +msg);
		
		/*
		 * size
		 */
		size_donnees = datas[10];
		System.out.println("size : "  + size_donnees);
		
		/*
		 * Données
		 */
		int index_donnees = 0;
		System.out.print("données : ");
		for(int i = 11; i < size; i++) {
			donnees[index_donnees] = Integer.toHexString(datas[i]);
			System.out.print("0x" +donnees[index_donnees]+ " , ");
			index_donnees++;
		}
		System.out.println("");
		      

		
	}	
		
	
	
	public static String[] getDestinataire() {
        return destinataire;
    }
	public static String[] getEmetteur() {
        return emetteur;
    }
	public static String getCnt() {
        return cnt;
    }
	public static String getMsg() {
        return msg;
    }
	public static int getSize_donnees() {
        return size_donnees ;
    }
	public static String[] getDonnees() {
        return donnees ;
    }
	
	
    

}
