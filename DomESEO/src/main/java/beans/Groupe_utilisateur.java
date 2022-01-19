package beans;
/*
 * Classe permettant de faire le lien entre les utilisateurs et les groupes qui leur ont été attribués
 * 
 */
public class Groupe_utilisateur {
	private int id;
	private int id_utilisateur;
	private int id_groupe;
	private boolean edition;
	
	public Groupe_utilisateur(int id,int id_user, int id_group, boolean edit) {
		this.id = id;
		this.id_utilisateur = id_user;
		this.id_groupe = id_group;
		this.edition = edit;
	}
	
	public void setId(int id) {
		this.id = id;
	}
	
	public void setId_utilisateur(int id) {
		this.id_utilisateur = id;
	}
	
	public void setId_groupe(int id) {
		this.id_groupe = id;
	}
	
	public void setEdition(boolean edit) {
		this.edition = edit;
	}
	
	public int getId() {
		return this.id;
	}
	
	public int getId_utilisateur() {
		return this.id_utilisateur;
	}
	
	public int getId_groupe() {
		return this.id_groupe;
	}
	
	public boolean getEdition() {
		return this.edition;
	}
}
