package beans;

public class Utilisateur {
	private int id;
	private String pseudo;
	private String mdp;
	private int admin;
	
	public Utilisateur() {}
	
	public Utilisateur(int id, String pseudo, String mdp, int admin) {
		this.setId(id);
		this.setPseudo(pseudo);
		this.setMdp(mdp);
<<<<<<< HEAD
		this.setAdmin(admin);
=======
		this.setAdmin(permission);
>>>>>>> branch 'dev_JEE' of https://172.24.0.69/b3/synthese/2021-2022/embarque.git
	
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

	public int getAdmin() {
		return admin;
	}

<<<<<<< HEAD
	public void setAdmin(int admin) {
		this.admin = admin;
=======
	public void setAdmin(int permission) {
		this.admin = permission;
>>>>>>> branch 'dev_JEE' of https://172.24.0.69/b3/synthese/2021-2022/embarque.git
	}

	public String getPseudo() {
		return pseudo;
	}

	public void setPseudo(String pseudo) {
		this.pseudo = pseudo;
	}

	
}
