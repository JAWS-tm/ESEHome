package tables;

public class Boite_reception {
	
	private byte boite_reception_id ;
    private byte objet_id ;
    
    public Boite_reception(byte boite_reception_id, byte objet_id) {
    	this.boite_reception_id = boite_reception_id;
    	this.objet_id = objet_id ;
    }
    
    public byte getBoite_reception_id() {
		return boite_reception_id ;
	}
	public void setBoite_reception_id(byte boite_reception_id ) {
		this.boite_reception_id = boite_reception_id ;
	}
    
    public byte getObjet_id() {
		return objet_id ;
	}
	public void setObjet_id(byte objet_id ) {
		this.objet_id = objet_id ;
	}
}