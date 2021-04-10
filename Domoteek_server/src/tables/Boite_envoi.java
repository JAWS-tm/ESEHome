package tables;

public class Boite_envoi {
	
	private byte boite_envoi_id ;
    private byte objet_id ;
    
    public Boite_envoi(byte boite_envoi_id, byte objet_id) {
    	this.boite_envoi_id = boite_envoi_id;
    	this.objet_id = objet_id ;
    }
    
    public byte getBoite_envoi_id() {
		return boite_envoi_id ;
	}
	public void setBoite_envoi_id(byte boite_envoi_id ) {
		this.boite_envoi_id = boite_envoi_id ;
	}
    
    public byte getObjet_id() {
		return objet_id ;
	}
	public void setObjet_id(byte objet_id ) {
		this.objet_id = objet_id ;
	}
}
