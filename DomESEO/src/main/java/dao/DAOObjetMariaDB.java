package dao;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import beans.Objet;
import beans.Objet_General;
import beans.Type;
import beans.Valeur;

public class DAOObjetMariaDB implements DAOObjet{
	
	private final DAOFactory daoFactory;
	
	public DAOObjetMariaDB(DAOFactory daoFactory) {
		this.daoFactory = daoFactory;
	}
	
	public List<Objet_General> getInfosObjets(){
	
		List<Objet_General> liste = new ArrayList<>();
		
		List<Valeur> listeValeurs = new ArrayList<>();
		List<Objet> listeObjet = new ArrayList<>();
		List<Type> listeTypes = new ArrayList<>();
		
		for (int i = 0; i < getObjet().size(); i++) {
			listeObjet.add(getObjet().get(i));
		}
		for(int i = 0; i < getValue().size(); i++) {
			listeValeurs.add(getValue().get(i));
		}
		for(int i = 0; i < getType().size(); i++) {
			listeTypes.add(getType().get(i));
		}
		
		for(int i = 0; i < listeObjet.size(); i++) {
			for(int j = 0; j <listeValeurs.size(); j++) {
				for(int k = 0; k<listeTypes.size(); k++) {
					if((listeObjet.get(i).getId() == listeValeurs.get(j).getId_objet()) && (listeObjet.get(i).getId_type() == listeTypes.get(k).getId())) {
						Objet_General objet = new Objet_General();
						objet.setNom_Objet(listeTypes.get(k));
						objet.setValeur(listeValeurs.get(j));
						liste.add(objet);
					}
				}
			}
		}
		return liste;
	}
	
	public List<Objet> getObjet(){
		List<Objet> liste = new ArrayList<>();
		 try (Connection connexion = daoFactory.getConnection();
			      Statement statement = connexion.createStatement();
			      ResultSet result = statement.executeQuery(
			    		  "SELECT id, type_id, state FROM objet;")) {
			        while (result.next()) {
			        	int id = result.getInt("id");
			        	int type_id = result.getInt("type_id");
			        	int state = result.getInt("state");
			 
			        	Objet objet = new Objet(id,type_id,state);
			        	liste.add(objet);
			        }
			    } catch (SQLException e) {
			        e.printStackTrace();
			    }
			    return liste;
	}
	
	public List<Valeur> getValue(){
		List<Valeur> liste = new ArrayList<>();
		try (Connection connexion = daoFactory.getConnection();
			      Statement statement = connexion.createStatement();
			      ResultSet result = statement.executeQuery(
			    		  "SELECT id, parametre_id, objet_id, valeur FROM valeur;")) {
			        while (result.next()) {
			        	int id = result.getInt("id");
			        	int param_id = result.getInt("parametre_id");
			        	int objet_id = result.getInt("objet_id");
			        	String value = result.getString("valeur");
			 
			        	Valeur valeur = new Valeur(id,param_id,objet_id,value);
			        	liste.add(valeur);
			        }
			    } catch (SQLException e) {
			        e.printStackTrace();
			    }
			    return liste;
	}
	
	public List<Type> getType(){
		List<Type> liste = new ArrayList<>();
		try (Connection connexion = daoFactory.getConnection();
			      Statement statement = connexion.createStatement();
			      ResultSet result = statement.executeQuery(
			    		  "SELECT id, nom_type FROM type;")) {
			        while (result.next()) {
			        	int id = result.getInt("id");
			        	String nom_type = result.getString("nom_type");
			 
			        	Type type = new Type(id,nom_type);
			        	liste.add(type);
			        }
			    } catch (SQLException e) {
			        e.printStackTrace();
			    }
			    return liste;
	}
	
}
