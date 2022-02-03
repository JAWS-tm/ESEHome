package dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import beans.Mot_de_passe;
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
					try {
						prepST.setString(2, new Mot_de_passe(mdp).hashMdp());
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					prepST.setInt(3, permission);//On met à 0 de base, l'admin a déjà été créé
					
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
			try {
				prepST.setString(2, new Mot_de_passe(mdp).hashMdp());
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
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
			
			try {
				prepST.setString(2, new Mot_de_passe(mdp).hashMdp());
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
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
	public void modifAdmin(int id, int permission) {
		
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


	/**
	    * Détermine si les identifiants de l'utilisateur sont valides
	    *
	    * @param  login     pseudonyme de l'utilisateur
	    * @param  mdp       mot de passe du compte de l'utilisateur
	    * 
	    * @return boolean
	*/
	@Override
	public boolean checkLogin(String login, String mdp) {
		try (Connection connexion = daoFactory.getConnection()) {
			
			PreparedStatement prepST = connexion.prepareStatement( 
				"SELECT * FROM utilisateur WHERE Pseudo=? AND MotDePasse=? ;");
			
			prepST.setString(1, login);
			try {
				prepST.setString(2, new Mot_de_passe(mdp).hashMdp());
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			try (ResultSet result = prepST.executeQuery()){
				if(result.next()) {
					return true;
				}
			}
			
		} catch(SQLException e) {
			
			System.out.println("ERROR : checkLogin()");
			e.printStackTrace();
		}
		return false;
	}


	
	/**
	    * Détermine si un compte avec le pseudo indiqué existe
	    *
	    * @param  pseudo     pseudonyme de l'utilisateur
	    * 
	    * @return boolean
	*/
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
			
			System.out.println("ERROR : checkPseudo()");
			e.printStackTrace();
		}
		return false;
	}
	
	public List<Utilisateur> listDB(){ 
		List<Utilisateur> liste = new ArrayList<>();
		try (Connection connect = daoFactory.getConnection()){
			Statement state = connect.createStatement();
			ResultSet result = state.executeQuery("SELECT id, Pseudo, Admin FROM utilisateur;"); {
				while (result.next()) {
					int id = result.getInt("id");
					String pseudo = result.getString("Pseudo");
					int admin = result.getInt("Admin");
					System.out.println(id);
					System.out.println(pseudo);
					System.out.println(admin);
					Utilisateur u = new Utilisateur();
					u.setId(id);
					u.setPseudo(pseudo);
					u.setAdmin(admin);
					liste.add(u);
				}
			} 
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return liste;
	}
	
	public void addgroup(int id) {
		try (Connection connexion = daoFactory.getConnection()) {
			PreparedStatement prepST = connexion.prepareStatement(
					"INSERT INTO groupe_utilisateur(id_utilisateur, id_groupe, edition) VALUES(?,?,?);");
			prepST.setInt(1, 2);
			prepST.setInt(2, id);
			prepST.setInt(3, 1);				
			prepST.executeUpdate();

		} catch(SQLException e) {
		
		System.out.println("ERROR1 : ajouterUtilisateur()");
		e.printStackTrace();
		}
	}

}
