package dao;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.PreparedStatement;
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
	
	public List<Groupe> getNomGroupe(int id){
		List<Groupe> liste = new ArrayList<>();
		try (Connection connexion = daoFactory.getConnection();
			      Statement statement = connexion.createStatement();
			      ResultSet result = statement.executeQuery(
			    		  "SELECT groupe.id, groupe.nom_groupe FROM groupe INNER JOIN groupe_utilisateur ON groupe.id = groupe_utilisateur.id_groupe WHERE groupe_utilisateur.id_utilisateur =" +id+ ";")) {
			        while (result.next()) {
			        	int id_grp = result.getInt("id");
			        	String nom_groupe = result.getString("nom_groupe");
			        	Groupe groupe = new Groupe(id_grp,nom_groupe);
			        	liste.add(groupe);
			        }
			    } catch (SQLException e) {
			        e.printStackTrace();
			    }
			    return liste;
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
			 
			        	Groupe groupe = new Groupe(id,nom_groupe);
			        	liste.add(groupe);
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
			        	Groupe_utilisateur groupe_Util = new Groupe_utilisateur(id,id_util,id_grp,edition);
			        	liste.add(groupe_Util);
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
			        	Groupe_objet groupe_Objet = new Groupe_objet(id,id_obj,id_grp);
			        	liste.add(groupe_Objet);
			        }
			    } catch (SQLException e) {
			        e.printStackTrace();
			    }
			    return liste;
	}
	
	
	
	@Override
	public Groupe getGroupeByNom(String nom_groupe) {
		
		Groupe group = null;
		
		try (Connection connexion = daoFactory.getConnection()) {
			
			PreparedStatement prepST = connexion.prepareStatement(
					"SELECT * FROM groupe WHERE nom_groupe=?;");
			
			prepST.setString(1, nom_groupe);
			
			
			try (ResultSet result = prepST.executeQuery()) {
				
				result.next();
				int id = result.getInt("id");
				
				String nom = result.getString("nom_groupe");
				
				group = new Groupe(id, nom);
				
				
			}
		} catch (SQLException e) {
			
			System.out.println("ERROR : getGroupeByNom()");
			e.printStackTrace();
		}
		
		return group;
	}
	
	
	
	
	@Override
	public void createNewGroup(String nom_groupe) {
		
		boolean check = false;
		
		try (Connection connexion = daoFactory.getConnection()) {
			
			try {					
				PreparedStatement prepST1 = connexion.prepareStatement(
						"SELECT * FROM groupe WHERE nom_groupe=?;");
				prepST1.setString(1, nom_groupe);
				
				try (ResultSet result = prepST1.executeQuery()) {
	
					if(result.next()) {
						check = true;
					}
				}
				if(check == false) {
					
					PreparedStatement prepST = connexion.prepareStatement(
							"INSERT INTO groupe(nom_groupe)"
							+ "VALUES(?);");
					prepST.setString(1, nom_groupe);
					
					prepST.executeUpdate();
				
				} else {
					
					System.out.println("Groupe avec ce nom déjà existant.");
				}
			
		
		} catch(SQLException e) {
			
			System.out.println("ERROR : createNewGroup???()");
			e.printStackTrace();
		}
			
		} catch(SQLException e) {
			
			System.out.println("ERROR : createNewGroup()");
			e.printStackTrace();
		}
	
		
	}
	
	
}
