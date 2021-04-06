package tables;

public class Message {

	private int message_id ;
	private int message_statut ;
	private int message_contenu ;
	private int message_date_envoi ;
	private int message_date_reception_acquittement ;
	
	public Message(int message_id, int message_statut, int message_contenu, int message_date_envoi, int message_date_reception_acquittement) {
		this.message_id = message_id;
		this.message_statut = message_statut;
		this.message_contenu = message_contenu ;
		this.message_date_envoi = message_date_envoi;
		this.message_date_reception_acquittement = message_date_reception_acquittement;
		
	}
	
	public int getMessage_id() {
		return message_id ;
	}
	public void setMessage_id(int message_id ) {
		this.message_id = message_id ;
	}
	
	public int getMessage_statut() {
		return message_statut;
	}
	public void setMessage_Statut() {
		this.message_statut = message_statut;
	}
	
	public int getMessage_contenu() {
		return message_contenu;
	}
	public void setMessage_contenu(int message_contenu) {
		this.message_contenu = message_contenu;
	}
	
	public int getMessage_date_envoi() {
		return message_date_envoi;
	}
	public void setMessage_date_envoi(int message_date_envoi) {
		this.message_date_envoi = message_date_envoi;
	}
	
	public int getMessage_date_reception_acquittement() {
		return message_date_reception_acquittement;
	}
	public void setMessage_date_reception_acquittement() {
		this.message_date_reception_acquittement =message_date_reception_acquittement;
	}
	
}
