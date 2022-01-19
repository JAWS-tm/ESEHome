package beans;

/*
 * Classe permettant de faire l'union entre objet_groupe et groupe_utilisateur
 */

public class Groupe {
	private int id;
	private String nom_groupe;
	
	public Groupe(int id, String nom) {
		this.id = id;
		this.nom_groupe = nom;
	}
	
	public void setId(int id) {
		this.id = id;
	}
	
	public void setNom_groupe(String nom) {
		this.nom_groupe = nom;
	}
	
	public int getId() {
		return this.id;
	}
	
	public String getNom_groupe() {
		return this.nom_groupe;
	}
}
