package beans;

public class Valeur {
	private int id;
	private int id_parametre;
	private int id_objet;
	private int valeur;
	
	public Valeur(int id, int id_param, int id_obj,int val) {
		this.id = id;
		this.id_parametre = id_param;
		this.id_objet = id_obj;
		this.valeur = val;
	}
	
	public void setId(int id) {
		this.id = id;
	}
	
	public void setId_parametre(int id) {
		this.id_parametre = id;
	}
	
	public void setId_objet(int id) {
		this.id_objet = id;
	}
	
	public void setValeur(int val) {
		this.valeur = val;
	}
	
	public int getId() {
		return this.id;
	}
	
	public int getId_parametre() {
		return this.id_parametre;
	}
	
	public int getId_objet() {
		return this.id_objet;
	}
	
	public int getValeur() {
		return this.valeur;
	}

}
