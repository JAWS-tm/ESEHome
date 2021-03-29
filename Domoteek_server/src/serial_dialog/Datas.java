package serial_dialog;

public class Datas {
	
	private static int [] destinataire = new int [4];
	private static int [] emetteur = new int [4]; 
	private static int cnt = 0 ; 
	private static int msg = 0 ; 
	private static int size_donnees = 0 ; 
	private static int [] donnees = new int [16]; 
	
	public static void datas_parse(int [] datas, int size) {
		
		/*
		 * destinataire
		 */
		System.out.print("destinataire : ");
		for(int i = 0; i < 4 ; i++){
			destinataire[i] = datas[i];
			System.out.print(destinataire[i]);
		}
		System.out.println("");
		
		/*
		 * émetteur
		 */
		int index_emetteur = 0;
		System.out.print("émetteur : ");
		for(int i = 4; i < 8; i++){
			emetteur[index_emetteur] = datas[i];
			System.out.print(emetteur[index_emetteur]);
			index_emetteur++;
		}
		System.out.println("");
		
		/*
		 * cnt
		 */
		cnt = datas[8];
		System.out.println("cnt : " + cnt);
		
		/*
		 * msg
		 */
		msg = datas[9];
		System.out.println("msg : " + msg);
		
		/*
		 * size
		 */
		size_donnees = datas[10];
		System.out.println("size : " + size_donnees);
		
		/*
		 * Données
		 */
		int index_donnees = 0;
		System.out.print("données : ");
		for(int i = 11; i < size; i++) {
			donnees[index_donnees] = datas[i];
			System.out.print(donnees[index_donnees]);
			index_donnees++;
		}
		System.out.println("");
		
/*
        int convertedValue = Integer.decode(arg0)
        System.out.print(convertedValue)
        
*/
		
	}	
		
	
	
	public int[] getDestinataire() {
        return this.destinataire;
    }
	public int[] getEmetteur() {
        return this.emetteur;
    }
	public int getCnt() {
        return this.cnt;
    }
	public int getMsg() {
        return this.msg;
    }
	public int getSize_donnees() {
        return this.size_donnees ;
    }
	public int[] getDonnees() {
        return this.donnees ;
    }
	
	
    

}
