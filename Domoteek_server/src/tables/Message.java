package tables;

public class Message {

	private byte message_id ;
	private byte message_statut ;
	private byte message_contenu ;
	private byte message_date_envoi ;
	private byte message_date_reception_acquittement ;
	
	public Message(byte message_id, byte message_statut, byte message_contenu, byte message_date_envoi, byte message_date_reception_acquittement) {
		this.message_id = message_id;
		this.message_statut = message_statut;
		this.message_contenu = message_contenu ;
		this.message_date_envoi = message_date_envoi;
		this.message_date_reception_acquittement = message_date_reception_acquittement;
		
	}
	
	public byte getMessage_id() {
		return message_id ;
	}
	public void setMessage_id(byte message_id ) {
		this.message_id = message_id ;
	}
	
	public byte getMessage_statut() {
		return message_statut;
	}
	public void setMessage_Statut() {
		this.message_statut = message_statut;
	}
	
	public byte getMessage_contenu() {
		return message_contenu;
	}
	public void setMessage_contenu(byte message_contenu) {
		this.message_contenu = message_contenu;
	}
	
	public byte getMessage_date_envoi() {
		return message_date_envoi;
	}
	public void setMessage_date_envoi(byte message_date_envoi) {
		this.message_date_envoi = message_date_envoi;
	}
	
	public byte getMessage_date_reception_acquittement() {
		return message_date_reception_acquittement;
	}
	public void setMessage_date_reception_acquittement() {
		this.message_date_reception_acquittement =message_date_reception_acquittement;
	}
	
}
