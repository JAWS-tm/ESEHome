package dao;

import beans.Utilisateur;

public class DAOUtilisateurBDD implements DAOUtilisateur {

	public DAOUtilisateurBDD() {
		// TODO Auto-generated constructor stub
	}

	@Override
	public void deleteUtilisateur(int id) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public Utilisateur getUtilisateurById(int id) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void ajouterUtilisateur(String pseudo, String mdp, int permission) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void updateUtilisateur(int id, String pseudo, String mdp, int permission) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void modifPseudo(int id, String pseudo) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void modifMDP(int id, String mdp) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void modifPermission(int id, int permission) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public Utilisateur getUtilisateurByPseudo(String pseudo) {
		// TODO Auto-generated method stub
		return null;
	}
}
