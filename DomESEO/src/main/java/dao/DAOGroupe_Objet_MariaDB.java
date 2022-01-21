package dao;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import beans.Groupe;
import beans.Groupe_objet;
import beans.Groupe_utilisateur;

public class DAOGroupe_Objet_MariaDB implements DAOGroupe_Objet{
	
	private final DAOFactory daoFactory;
	
	public DAOGroupe_Objet_MariaDB(DAOFactory daoFactory) {
		this.daoFactory = daoFactory;
	}
	
	public List<Groupe> getGroupe(){
		List<Groupe> liste = new ArrayList<>();
		try (Connection connexion = daoFactory.getConnection();
			      Statement statement = connexion.createStatement();
			      ResultSet result = statement.executeQuery(
			    		  "SELECT id, nom_groupe FROM groupe;")) {
			        while (result.next()) {
			        	int id = result.getInt("id");
			        	String nom_groupe = result.getString("nom_groupe");
			 
			        	Groupe type = new Groupe(id,nom_groupe);
			        	liste.add(type);
			        }
			    } catch (SQLException e) {
			        e.printStackTrace();
			    }
			    return liste;
	}
	
	
	public List<Groupe_utilisateur> getGroupe_Utilisateur(){
		List<Groupe_utilisateur> liste = new ArrayList<>();
		Boolean edition = false;
		try (Connection connexion = daoFactory.getConnection();
			      Statement statement = connexion.createStatement();
			      ResultSet result = statement.executeQuery(
			    		  "SELECT id, id_utilisateur, id_groupe, edition FROM groupe_utilisateur;")) {
			        while (result.next()) {
			        	int id = result.getInt("id");
			        	int id_util = result.getInt("id_utilisateur");
			        	int id_grp = result.getInt("id_groupe");
			        	int edit = result.getInt("edition");
			        	if(edit == 1) {
			        		edition = true;
			        	}
			        	Groupe_utilisateur type = new Groupe_utilisateur(id,id_util,id_grp,edition);
			        	liste.add(type);
			        }
			    } catch (SQLException e) {
			        e.printStackTrace();
			    }
			    return liste;
	}
	
	public List<Groupe_objet> getGroupe_Objet(){
		List<Groupe_objet> liste = new ArrayList<>();
		try (Connection connexion = daoFactory.getConnection();
			      Statement statement = connexion.createStatement();
			      ResultSet result = statement.executeQuery(
			    		  "SELECT id, id_objet, id_groupe FROM objet_groupe;")) {
			        while (result.next()) {
			        	int id = result.getInt("id");
			        	int id_obj = result.getInt("id_objet");
			        	int id_grp = result.getInt("id_groupe");
			        	Groupe_objet type = new Groupe_objet(id,id_obj,id_grp);
			        	liste.add(type);
			        }
			    } catch (SQLException e) {
			        e.printStackTrace();
			    }
			    return liste;
	}
}
