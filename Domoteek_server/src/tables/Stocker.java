 package tables;

public class Stocker {

	private byte boite_reception_id ;
	private byte boite_envoi_id ;
	private byte message_id ;
	private byte stocker_qte ;
	
	public Stocker(byte boite_reception_id, byte boite_envoi_id, byte message_id, byte stocker_qte) {
		
		this.boite_envoi_id = boite_envoi_id;
		this.boite_reception_id = boite_reception_id;
		this.message_id = message_id ;
		this.stocker_qte = stocker_qte;		
			
	}
	
	public byte getBoite_reception_id() {
		return boite_reception_id;
	}
	public void setBoite_reception_id(byte boite_reception_id) {
		this.boite_reception_id = boite_reception_id;
	}
	
	public byte getBoite_envoi_id() {
		return boite_envoi_id;
	}
	public void setBoite_envoi_id() {
		this.boite_envoi_id = boite_envoi_id;
	}
	
	public byte getMessage_id() {
		return message_id;
	}
	public void setMessage_id(byte message_id) {
		this.message_id = message_id;
	}
	
	public byte getStocker_qte() {
		return stocker_qte;
	}
	public void setStocker_qte() {
		this.stocker_qte = stocker_qte;
	}
}
