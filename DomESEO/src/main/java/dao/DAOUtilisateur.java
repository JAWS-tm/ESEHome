package dao;
import beans.Utilisateur;

public interface DAOUtilisateur {

	public abstract void addUtilisateur(String pseudo, String mdp, int permission);
	
	public abstract void deleteUtilisateur(int id);
	
	public abstract void updateUtilisateur(int id, String pseudo, int permission);

	public abstract Utilisateur getUtilisateurById (int id);
}
