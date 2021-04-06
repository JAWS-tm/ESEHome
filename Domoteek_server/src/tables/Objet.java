package tables;

public class Objet {

	private int objet_id ; 
	private int objet_type ;
	private int objet_numero ;
	private int objet_appartenance ;
	private int objet_adresse ;
	
	
	public Objet(int objet_id, int objet_type,int objet_numero, int objet_appartenance, int objet_adresse) {
		this.objet_id = objet_id;
		this.objet_type = objet_type ;
		this.objet_numero = objet_numero ;
		this.objet_appartenance = objet_appartenance ;
		this.objet_adresse = objet_adresse ;
		
	}
	
	public int getObjet_id() {
		return objet_id ;
	}
	public void setObjet_id(int objet_id ) {
		this.objet_id = objet_id ;
	}
	
	public int getObjet_type() {
		return objet_type;
	}
	public void setObjet_type(int objet_type) {
		this.objet_type = objet_type;
	}
	
	public int getObjet_numero() {
		return objet_numero;
	}
	public void setObjet_numero(int objet_numero) {
		this.objet_numero = objet_numero ;
	}
	
	public int getObjet_appartenance() {
		return objet_appartenance;
	}
	public void setObjet_appartenance(int objet_appartenance) {
		this.objet_appartenance = objet_appartenance ;
	}
	
	public int getObjet_adresse() {
		return objet_adresse;
	}
	public void setObjet_adresse(int objet_adresse ) {
		this.objet_adresse = objet_adresse;
	}
	

}
