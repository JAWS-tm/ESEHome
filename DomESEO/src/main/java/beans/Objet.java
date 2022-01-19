package beans;

public class Objet {
	private int id;
	private int type_id;
	private boolean state;
	private Valeur valeur;
	private Type type;
	
	public Objet(int id, int type_id, boolean state, Valeur val, Type type) {
		this.id = id;
		this.type_id = type_id;
		this.state = state;
		this.valeur = val;
		this.type = type;
	}
	
	public void setId(int id) {
		this.id = id;
	}
	
	public void setId_type(int id) {
		this.type_id = id;
	}
	
	public void setState(boolean state) {
		this.state = state;
	}
	
	public void setValeur(Valeur val) {
		this.valeur = val;
	}
	
	public void setType(Type type) {
		this.type = type;
	}
	
	public int getId() {
		return this.id;
	}
	
	public int getId_type() {
		return this.type_id;
	}
	
	public boolean getState() {
		return this.state;
	}
	
	public Valeur getValeur() {
		return this.valeur;
	}
	
	public Type getType() {
		return this.type;
	}
}
