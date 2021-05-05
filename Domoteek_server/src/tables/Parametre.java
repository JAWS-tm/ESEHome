package tables;

public class Parametre {
	
	private byte parametre_id ;
	private byte parametre_type ;
	private byte parametre_contenu ;
	
	public Parametre( byte parametre_id, byte parametre_type, byte parametre_contenu) {
		this.parametre_id = parametre_id;
		this.parametre_type = parametre_type;
		this.parametre_contenu = parametre_contenu;
	}
	
	public byte getParametre_id() {
		return  parametre_id;
	}
	public void setParametre_id(byte parametre_id) {
		this.parametre_id = parametre_id ;
	}
	
	public byte getParametre_type() {
		return  parametre_type;
	}
	public void setParametre_type(byte parametre_type) {
		this.parametre_type = parametre_type ;
	}
	
	public byte getParametre_contenu() {
		return  parametre_contenu;
	}
	public void setParametre_contenu(byte parametre_contenu ) {
		this.parametre_contenu = parametre_contenu ;
	}

}
