package tables;

public class Boite_envoi {
	
	private int boite_envoi_id ;
    private int objet_id ;
    
    public Boite_envoi(int boite_envoi_id, int objet_id) {
    	this.boite_envoi_id = boite_envoi_id;
    	this.objet_id = objet_id ;
    }
    
    public int getBoite_envoi_id() {
		return boite_envoi_id ;
	}
	public void setBoite_envoi_id(int boite_envoi_id ) {
		this.boite_envoi_id = boite_envoi_id ;
	}
    
    public int getObjet_id() {
		return objet_id ;
	}
	public void setObjet_id(int objet_id ) {
		this.objet_id = objet_id ;
	}
}
