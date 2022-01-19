package beans;

public class Objet_General {
	private String nom_Objet;
	private String valeur;
	
	public Objet_General() {
	}

	public String getNom_Objet() {
		return nom_Objet;
	}

	public void setNom_Objet(Type type) {
		this.nom_Objet = type.getNom_type();
	}

	public String getValeur() {
		return valeur;
	}

	public void setValeur(Valeur value) {
		this.valeur = value.getValeur();
	}
	
	
	
}
