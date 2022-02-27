package beans;

public class Objet_General {
	private String nom_Objet;
	private String valeur;
	private int id_groupe;
	
	public Objet_General(String nom,String value) {
		this.nom_Objet = nom;
		this.valeur = value;
	}
	
	public Objet_General(String nom,String value, int id_groupe) {
		this.nom_Objet = nom;
		this.valeur = value;
		this.setId_groupe(id_groupe);
	}
	

	public String getNom_Objet() {
		return nom_Objet;
	}

	public void setNom_Objet(String type) {
		this.nom_Objet = type;
	}

	public String getValeur() {
		return valeur;
	}

	public void setValeur(String value) {
		this.valeur = value;
	}

	public int getId_groupe() {
		return id_groupe;
	}

	public void setId_groupe(int id_groupe) {
		this.id_groupe = id_groupe;
	}
	
	
	
}
