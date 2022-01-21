package dao;

import java.util.List;

import beans.Objet;
import beans.Objet_General;
import beans.Type;
import beans.Valeur;

public interface DAOObjet {
	
	public abstract List<Objet_General> getInfosObjets(); 
	public abstract List<Objet> getObjet();
	public abstract List<Valeur> getValue();
	public abstract List<Type> getType();
	public abstract int getIdByName(String groupe);

}
