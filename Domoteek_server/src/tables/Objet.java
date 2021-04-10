package tables;

public class Objet {

	private byte objet_id ; 
	private byte objet_type ;
	private byte [] objet_numero ;
	private byte objet_appartenance ;
	private byte objet_adresse ;
	private boolean objet_associer;
	

	public Objet(byte objet_id, byte objet_type, byte[] objet_numero, byte objet_appartenance, byte objet_adresse,
			boolean objet_associer) {
		this.objet_id = objet_id;
		this.objet_type = objet_type ;
		this.objet_numero = objet_numero ;
		this.objet_appartenance = objet_appartenance ;
		this.objet_adresse = objet_adresse ;
		this.objet_associer = objet_associer ;
	}


	public byte getObjet_id() {
		return objet_id ;
	}
	public void setObjet_id(byte objet_id ) {
		this.objet_id = objet_id ;
	}
	
	public byte getObjet_type() {
		return objet_type;
	}
	public void setObjet_type(byte objet_type) {
		this.objet_type = objet_type;
	}
	
	public byte [] getObjet_numero() {
		return objet_numero;
	}
	public void setObjet_numero(byte[] objet_numero) {
		this.objet_numero = objet_numero ;
	}
	
	public byte getObjet_appartenance() {
		return objet_appartenance;
	}
	public void setObjet_appartenance(byte objet_appartenance) {
		this.objet_appartenance = objet_appartenance ;
	}
	
	public byte getObjet_adresse() {
		return objet_adresse;
	}
	public void setObjet_adresse(byte objet_adresse ) {
		this.objet_adresse = objet_adresse;
	}
	
	public boolean getObjet_associer() {
		return objet_associer;
	}
	public void setObjet_associer(boolean objet_associer) {
		this.objet_associer = objet_associer;
	}
	

}
