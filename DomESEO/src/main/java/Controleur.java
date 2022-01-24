import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import beans.Groupe;
import beans.Objet_General;
import beans.Utilisateur;
import dao.DAOFactory;
import dao.DAOGroupe_Objet;
import dao.DAOObjet;
import dao.DAOUtilisateur;
//import dao.DAOUtilisateurMariaDB;


/**
 * Servlet implementation class Controleur
 */
@WebServlet("/Controleur")
public class Controleur extends HttpServlet {
	
	private static final long serialVersionUID = 1L;
    private Utilisateur utilisateur;   
    private DAOUtilisateur daoUtilisateur;
    private DAOObjet daoObjet;
    private DAOGroupe_Objet daoGroupe_Objet;
    

    public Controleur() {
        super();
    }

    public void init() {
    	DAOFactory daoFactory = DAOFactory.getInstance();
    	this.daoUtilisateur = daoFactory.getDAOUtilisateur("MariaDB");
    	this.daoObjet = daoFactory.getDAOObjet("MariaDB");
    	this.daoGroupe_Objet = daoFactory.getDAOGroupe_Objet("MariaDB");
    	
    }
    
	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
		processRequest(request, response, request.getParameter("dest"));
	}

	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
		processRequest(request, response, request.getParameter("dest"));
	}
	
	
	
	protected void processRequest(HttpServletRequest request, HttpServletResponse response,String dest) throws ServletException, IOException {
		
		String destination = dest;
		HttpSession session = request.getSession();
		if(destination != null) {
			
			switch(destination) {
			
				case "accueil":
					
					request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
					
				break;
					
					
				case "connexion":
					String page = "/JSP/Accueil.jsp";
					boolean error = true;
					
					if(request.getParameter("identifiant") != null && !request.getParameter("identifiant").isEmpty()) {
						
						if(request.getParameter("mot_de_passe") != null && !request.getParameter("mot_de_passe").isEmpty()) {
					
							if(this.daoUtilisateur.checkPseudo(request.getParameter("identifiant"))) {
						
								if(this.daoUtilisateur.checkLogin(request.getParameter("identifiant"), request.getParameter("mot_de_passe"))) {
									
									this.utilisateur = this.daoUtilisateur.getUtilisateurByPseudo(request.getParameter("identifiant"));
									
									if(this.utilisateur.getAdmin() == 1) {
										
										error = false;
										request.setAttribute("connecte", "oui");
										request.setAttribute("admin", "oui");
										
									} else if(this.utilisateur.getAdmin() == 0) {
										
										error = false;
										request.setAttribute("connecte", "oui");
										request.setAttribute("admin", "non");
										
									} else {
										request.setAttribute("error", "Votre compte n'a pas été vérifié !");
										request.setAttribute("privilege", "non");
									}
									
								} else {
									request.setAttribute("error", "Mot de passe incorrect. Veuillez réessayer.");
								}
							
							} else {
								request.setAttribute("error", "Cet utilisateur n'existe pas.");
							}
							
						} else {
							request.setAttribute("error", "Veuillez indiquer un mot de passe.");
						}
						
					} else {
						request.setAttribute("error", "Veuillez indiquer le pseudonyme de l'utilisateur.");
					}
					
					
					if(error) {
						switch(request.getParameter("source")) {
						case "Accueil":
							page = "/JSP/Accueil.jsp";
							break;
						case "DashBoard":
							page = "/JSP/DashBoard.jsp";
							break;
						default:
							//On n'est pas censé arriver là
							System.out.println("ERREUR : source dans connexion");
							break;
						}
					}
					request.getRequestDispatcher(page).forward(request, response);
					break;
				case "gestion_droit":
					List<Utilisateur> liste = this.daoUtilisateur.listDB();
					request.setAttribute("liste", liste);
					request.getRequestDispatcher("/JSP/PageAdmin.jsp").forward(request, response);
					break;	
				case "changement_groupe":
					String groupe=request.getParameter("groups");
					int identifiant = this.daoObjet.getIdByName(groupe);
					this.daoUtilisateur.addgroup(identifiant);
					request.getRequestDispatcher("/JSP/PageAdmin.jsp").forward(request, response);
					break;
					
					
					
				case "modifUtil":
					
					System.out.println(dest);
					int idUtil = Integer.parseInt(request.getParameter("idUtil"));
					
					Utilisateur us = daoUtilisateur.getUtilisateurById(idUtil);
					
					request.setAttribute("us", us);
					
					request.getRequestDispatcher("/JSP/ModifUtil.jsp").forward(request, response);

					
					break;
				
				case "create_user_page":
					
					System.out.println(dest);
					request.getRequestDispatcher("/JSP/CreateUser.jsp").forward(request, response);
				
					break;
					
				case "create_user":
					
					if((request.getParameter("pseudo") != null && !request.getParameter("pseudo").isEmpty()) && (request.getParameter("password") != null && !request.getParameter("password").isEmpty()) && (request.getParameter("confirm_password") != null && !request.getParameter("confirm_password").isEmpty())) {
						
						if(request.getParameter("password").equals(request.getParameter("confirm_password"))) {
							
							if(!this.daoUtilisateur.checkPseudo(request.getParameter("pseudo"))) {
								
								this.daoUtilisateur.ajouterUtilisateur(request.getParameter("pseudo"), request.getParameter("password"), 0);
								request.setAttribute("succesC", "L'utilisateur "+request.getParameter("pseudo")+" a été créé avec succès.");
								
							} else { 
								
								request.setAttribute("infoC", "Le pseudo a déjà été utilisé !");
							}
						}else {
							
							request.setAttribute("infoC", "Les deux mots de passe ne sont pas équivalents !");
						}
					} else {
						
						request.setAttribute("infoC", "Tous les champs ne sont pas complétés !");
					}
					request.getRequestDispatcher("/JSP/CreateUser.jsp").forward(request, response);
					
					
					break;
					
				case "add_user_page":
					request.getRequestDispatcher("/JSP/Demande_privilege.jsp").forward(request, response);
						
					break;

				case "add_user":
					
					if((request.getParameter("pseudo") != null && !request.getParameter("pseudo").isEmpty()) && (request.getParameter("password") != null && !request.getParameter("password").isEmpty()) && (request.getParameter("confirm_password") != null && !request.getParameter("confirm_password").isEmpty())) {
						
						if(request.getParameter("password").equals(request.getParameter("confirm_password"))) {
							
							if(!this.daoUtilisateur.checkPseudo(request.getParameter("pseudo"))) {
								
								this.daoUtilisateur.ajouterUtilisateur(request.getParameter("pseudo"), request.getParameter("password"), -1);
								request.setAttribute("succes", "Demande envoyée !");
								
							} else { 
								
								request.setAttribute("info", "Le pseudo a déjà été utilisé !");
							}
						}else {
							
							request.setAttribute("info", "Les deux mots de passe ne sont pas équivalents !");
						}
					} else {
						
						request.setAttribute("info", "Tous les champs ne sont pas complétés !");
					}
					request.getRequestDispatcher("/JSP/Demande_privilege.jsp").forward(request, response);
					break;
				case "visitor_dashboard":
					List<Objet_General> liste2 = this.daoObjet.getInfosObjets();
					request.setAttribute("liste2", liste2);
					request.getRequestDispatcher("/JSP/DashBoard.jsp").forward(request, response);
					break;
				case "user_dashboard" :
					String verif;
					String choix = "default";
					int idGroupe;
					List<Objet_General> liste_default = new ArrayList<>();
					verif = request.getParameter("verif");
					
					List<Groupe> liste_groupe = this.daoGroupe_Objet.getNomGroupe(this.utilisateur.getId());
					request.setAttribute("listeVues", liste_groupe);
					
					if(verif != null) { 
						choix = request.getParameter("choice");
					}
					
					if(choix.contains("default")) {
						liste_default.clear();
						liste_default = this.daoObjet.getInfosObjets();
					}else{
						idGroupe = Integer.valueOf(choix);
						liste_default.clear();
						liste_default = this.daoObjet.getInfosObjets_FromGroup(this.utilisateur.getId(), idGroupe);
					}
					request.setAttribute("liste2", liste_default);
					request.getRequestDispatcher("/JSP/User_Dashboard.jsp").forward(request, response);
					break;
				default:
					//On ne doit pas se retrouver ici !
					request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
					break;
			}
			
		} else {
			
			//On arrive sur le site et on n'a pas encore mis de destination --> renvoie à l'accueil
			request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
		}
		
	}

}