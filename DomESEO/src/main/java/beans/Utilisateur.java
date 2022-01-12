package beans;

public class Utilisateur {
	private int id;
	private String pseudo;
	private String mdp;
	private int permission;
	
	public Utilisateur() {}
	
	public Utilisateur(int id, String pseudo, String mdp, int permission) {
		this.setId(id);
		this.setPseudo(pseudo);
		this.setMdp(mdp);
		this.setPermission(permission);
	
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getMdp() {
		return mdp;
	}

	public void setMdp(String mdp) {
		this.mdp = mdp;
	}

	public int getPermission() {
		return permission;
	}

	public void setPermission(int permission) {
		this.permission = permission;
	}

	public String getPseudo() {
		return pseudo;
	}

	public void setPseudo(String pseudo) {
		this.pseudo = pseudo;
	}

	
}
