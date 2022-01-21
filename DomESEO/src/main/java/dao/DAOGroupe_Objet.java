package dao;

import java.util.List;

import beans.Groupe;
import beans.Groupe_objet;
import beans.Groupe_utilisateur;

public interface DAOGroupe_Objet {
	
	public abstract List<Groupe> getNomGroupe(int id);
	
	public abstract List<Groupe> getGroupe();
	
	public abstract List<Groupe_utilisateur> getGroupe_Utilisateur();
	
	public abstract List<Groupe_objet> getGroupe_Objet();
}
