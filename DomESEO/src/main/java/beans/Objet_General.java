package beans;

public class Objet_General {
	private String nom_Objet;
	private String valeur;
	
	public Objet_General(String nom,String value) {
		this.nom_Objet = nom;
		this.valeur = value;
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
	
	
	
}
