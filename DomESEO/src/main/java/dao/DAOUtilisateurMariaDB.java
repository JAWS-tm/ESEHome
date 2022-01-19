package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import beans.Utilisateur;

public class DAOUtilisateurMariaDB implements DAOUtilisateur {
	
	private final DAOFactory daoFactory;
	
	public DAOUtilisateurMariaDB(DAOFactory daoFactory) {
		this.daoFactory = daoFactory;
	}
	
	
	/**
	    * Crée une nouvelle entrée dans la table Utilisateur. 
	    *
	    * @param  pseudo  		le pseudonyme (username) de l'utilisateur
	    * @param  mdp     		mot de passe du compte de l'utilisateur
	    * @param  permission	privilèges de l'utilisateur
	    * 
	    * @return void
	*/
	@Override
	public void ajouterUtilisateur(String pseudo, String mdp, int permission) {
		
		try (Connection connexion = daoFactory.getConnection()) {
			
			
				if(!checkPseudo(pseudo)) {
					
					PreparedStatement prepST = connexion.prepareStatement(
							"INSERT INTO utilisateur(Pseudo, MotDePasse, Admin) VALUES(?,?,?);");
					prepST.setString(1, pseudo);
					prepST.setString(2, mdp);
					prepST.setInt(3, 0);			//On met à 0 de base, l'admin a déjà été créé
					
					prepST.executeUpdate();
	
				} else {
					
					System.out.println("Un autre utilisateur est déjà en possession de ce pseudonyme.");
				}
			
			} catch(SQLException e) {
			
			System.out.println("ERROR1 : ajouterUtilisateur()");
			e.printStackTrace();
			}
		
	}
	
	
	/**
	    * Met à jour une entrée existante de la table Utilisateur. 
	    *
	    * @param  id            identifiant unique de l'utilisateur
	    * @param  pseudo  		le pseudonyme (username) de l'utilisateur
	    * @param  mdp     		mot de passe du compte de l'utilisateur
	    * @param  permission	privilèges de l'utilisateur
	    * 
	    * @return void
	*/
	@Override
	public void updateUtilisateur(int id, String pseudo, String mdp, int permission) {
		
		try (Connection connexion = daoFactory.getConnection()) {
			
			PreparedStatement prepST = connexion.prepareStatement( 
				"UPDATE utilisateur SET Pseudo=?, MotDePasse=?, Admin=? WHERE id=?;");
			
			prepST.setString(1, pseudo);
			prepST.setString(2, mdp);
			prepST.setInt(3, permission);
			prepST.setInt(4, id);
			
			prepST.executeUpdate();
			
		} catch(SQLException e) {
			
			System.out.println("ERROR : updateUtilisateur()");			
			e.printStackTrace();
		}
		
	}
	
	
	/**
	    * Met à jour le pseudonyme d'un utilisateur existant. 
	    *
	    * @param  id     	identifiant unique de l'utilisateur
	    * @param  pseudo	nouveau pseudo
	    * 
	    * @return void
	*/
	@Override
	public void modifPseudo(int id, String pseudo) {
		
		try (Connection connexion = daoFactory.getConnection()) {
			
			PreparedStatement prepST = connexion.prepareStatement( 
				"UPDATE utilisateur SET Pseudo=? WHERE id=?;");
			
			prepST.setString(1, pseudo);
			prepST.setInt(2, id);
			
			prepST.executeUpdate();
			
		} catch(SQLException e) {
			
			System.out.println("ERROR : modifPseudo()");			
			e.printStackTrace();
		}
		
	}
	
	
	/**
	    * Met à jour le mot de passe d'un utilisateur existant. 
	    *
	    * @param  id     	identifiant unique de l'utilisateur
	    * @param  mdp		nouveau mot de passe
	    * 
	    * @return void
	*/
	@Override
	public void modifMDP(int id, String mdp) {
		
		try (Connection connexion = daoFactory.getConnection()) {
			
			PreparedStatement prepST = connexion.prepareStatement( 
				"UPDATE utilisateur SET MotDePasse=? WHERE id=?;");
			
			prepST.setString(1, mdp);
			prepST.setInt(2, id);
			
			prepST.executeUpdate();
			
		} catch(SQLException e) {
			
			System.out.println("ERROR : modifMDP()");			
			e.printStackTrace();
		}
		
	}
	
	
	/**
	    * Met à jour les privilèges d'un utilisateur existant. 
	    *
	    * @param  id     		identifiant unique de l'utilisateur
	    * @param  permission	nouveaux privilèges
	    * 
	    * @return void
	*/
	@Override
	public void modifPermission(int id, int permission) {
		
		try (Connection connexion = daoFactory.getConnection()) {
			
			PreparedStatement prepST = connexion.prepareStatement( 
				"UPDATE utilisateur SET Admin=? WHERE id=?;");
			
			prepST.setInt(1, permission);
			prepST.setInt(2, id);
			
			prepST.executeUpdate();
			
		} catch(SQLException e) {
			
			System.out.println("ERROR : modifPermission()");			
			e.printStackTrace();
		}
		
	}
	
	
	/**
	    * Retrouve un utilisateur à partir de son identifiant unique. 
	    *
	    * @param  id     identifiant unique de l'utilisateur
	    * 
	    * @return un objet de type Utilisateur
	*/
	@Override
	public Utilisateur getUtilisateurById(int id) {
		
		Utilisateur utilisateur = null;
		
		try (Connection connexion = daoFactory.getConnection()) {
			
			PreparedStatement prepST = connexion.prepareStatement(
					"SELECT * FROM utilisateur WHERE id=?;");
			
			prepST.setInt(1, id);
			
			
			try (ResultSet result = prepST.executeQuery()) {
				
				if (result.next()) {
					
					int identifiant = result.getInt("id");
					String pseudo = result.getString("Pseudo");
					String mdp = result.getString("MotDePasse");
					int permission = result.getInt("Admin");
					
					utilisateur = new Utilisateur(identifiant, pseudo, mdp, permission);
				
				}
			}
		} catch (SQLException e) {
			
			System.out.println("ERROR : getUtilisateurById()");
			e.printStackTrace();
		}
		
		return utilisateur;
		
	}
	
	
	/**
	    * Retrouve un utilisateur à partir de son pseudoyme. 
	    *
	    * @param  pseudo     pseudonyme de l'utilisateur
	    * 
	    * @return un objet de type Utilisateur
	*/
	@Override
	public Utilisateur getUtilisateurByPseudo(String pseudo) {
		
		Utilisateur utilisateur = null;
		
		try (Connection connexion = daoFactory.getConnection()) {
			
			PreparedStatement prepST = connexion.prepareStatement(
					"SELECT * FROM utilisateur WHERE Pseudo=?;");
			
			prepST.setString(1, pseudo);
			
			
			try (ResultSet result = prepST.executeQuery()) {
				
				if (result.next()) {
					
					int identifiant = result.getInt("id");
					String pseudonyme = result.getString("Pseudo");
					String mdp = result.getString("MotDePasse");
					int permission = result.getInt("Admin");
					
					utilisateur = new Utilisateur(identifiant, pseudonyme, mdp, permission);
				
				}
			}
		} catch (SQLException e) {
			
			System.out.println("ERROR : getUtilisateurByPseudo()");
			e.printStackTrace();
		}
		
		return utilisateur;
		
	}
	
	
	/**
	    * Supprime un utilisateur à partir de son identifiant. 
	    *
	    * @param  id     identifiant de l'utilisateur
	    * 
	    * @return void
	*/
	@Override
	public void deleteUtilisateur(int id) {
		
		try (Connection connexion = daoFactory.getConnection()) {
			
			PreparedStatement prepST = connexion.prepareStatement( 
				"DELETE FROM utilisateur WHERE id=?;");
			
			prepST.setInt(1, id);
			
			prepST.executeUpdate();
			
		} catch(SQLException e) {
			
			System.out.println("ERROR : deleteUtilisateur()");
			e.printStackTrace();
		}
	}


	@Override
	public boolean checkLogin(String login, String mdp) {
		try (Connection connexion = daoFactory.getConnection()) {
			
			PreparedStatement prepST = connexion.prepareStatement( 
				"SELECT * FROM utilisateur WHERE Pseudo=? AND MotDePasse=? ;");
			
			prepST.setString(1, login);
			prepST.setString(2, mdp);
			
			try (ResultSet result = prepST.executeQuery()){
				if(result.next()) {
					return true;
				}
			}
			
		} catch(SQLException e) {
			
			System.out.println("ERROR : deleteUtilisateur()");
			e.printStackTrace();
		}
		return false;
	}


	@Override
	public boolean checkPseudo(String pseudo) {
		try (Connection connexion = daoFactory.getConnection()) {
			
			PreparedStatement prepST = connexion.prepareStatement( 
				"SELECT * FROM utilisateur WHERE Pseudo=?;");
			
			prepST.setString(1, pseudo);
			
			try (ResultSet result = prepST.executeQuery()){
				if(result.next()) {
					return true;
				}
			}
			
		} catch(SQLException e) {
			
			System.out.println("ERROR : deleteUtilisateur()");
			e.printStackTrace();
		}
		return false;
	}
	
	
}
