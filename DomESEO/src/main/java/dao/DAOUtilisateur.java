package dao;

import beans.Utilisateur;

public interface DAOUtilisateur {
	
	public abstract void ajouterUtilisateur(String pseudo, String mdp, int permission);
	
	public abstract void updateUtilisateur(int id, String pseudo, String mdp, int permission);
	
	public abstract void modifPseudo(int id, String pseudo);
	
	public abstract void modifMDP(int id, String mdp);
	
	public abstract void modifPermission(int id, int permission);
	
	public abstract Utilisateur getUtilisateurById(int id);
	
	public abstract Utilisateur getUtilisateurByPseudo(String pseudo);
	
	public abstract void deleteUtilisateur(int id);
	
}

