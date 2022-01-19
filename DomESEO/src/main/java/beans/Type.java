package beans;

public class Type {
	private int id;
	private String nom_type;
	
	public Type(int id, String nom_type) {
		this.id = id;
		this.nom_type = nom_type;
	}
	
	public void setId(int id) {
		this.id = id;
	}
	
	public void setNom_type(String nom) {
		this.nom_type = nom;
	}
	
	public int getId() {
		return this.id;
	}
	
	public String getNom_type() {
		return this.nom_type;
	}
}
