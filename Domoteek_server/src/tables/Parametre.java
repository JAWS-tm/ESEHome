package tables;

public class Parametre {
	
	private int parametre_id ;
	private int parametre_type ;
	private int parametre_contenu ;
	
	public Parametre( int parametre_id, int parametre_type, int parametre_contenu) {
		this.parametre_id = parametre_id;
		this.parametre_type = parametre_type;
		this.parametre_contenu = parametre_contenu;
	}
	
	public int getParametre_id() {
		return  parametre_id;
	}
	public void setParametre_id(int parametre_id) {
		this.parametre_id = parametre_id ;
	}
	
	public int getParametre_type() {
		return  parametre_type;
	}
	public void setParametre_type(int parametre_type) {
		this.parametre_type = parametre_type ;
	}
	
	public int getParametre_contenu() {
		return  parametre_contenu;
	}
	public void setParametre_contenu(int parametre_contenu ) {
		this.parametre_contenu = parametre_contenu ;
	}

}
