package beans;
/*
 * Classe permettant de faire le lien entre les objets et les groupes qui leur ont été attribués
 * 
 */
public class Groupe_objet {
	private int id;
	private int id_objet;
	private int id_groupe;
	
	public Groupe_objet(int id,int id_objet,int id_groupe) {
		this.id = id;
		this.id_groupe = id_groupe;
		this.id_objet = id_objet;
	}
	
	public void setId(int id) {
		this.id = id;
	}
	
	public void setId_objet(int id) {
		this.id_objet = id;
	}
	
	public void setId_groupe(int id) {
		this.id_groupe = id;
	}
	
	public int getId() {
		return this.id;
	}
	
	public int getId_objet() {
		return this.id_objet;
	}
	
	public int getId_groupe() {
		return this.id_groupe;
	}
}
