import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import beans.Objet_General;
import beans.Utilisateur;
import dao.DAOFactory;
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
    

    public Controleur() {
        super();
    }

    public void init() {
    	DAOFactory daoFactory = DAOFactory.getInstance();
    	this.daoUtilisateur = daoFactory.getDAOUtilisateur("MariaDB");
    	this.daoObjet = daoFactory.getDAOObjet("MariaDB");
    	
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
					
					if(request.getParameter("identifiant") != null && !request.getParameter("identifiant").isEmpty()) {
						
						if(request.getParameter("mot_de_passe") != null && !request.getParameter("mot_de_passe").isEmpty()) {
					
							if(this.daoUtilisateur.checkPseudo(request.getParameter("identifiant"))) {
						
								if(this.daoUtilisateur.checkLogin(request.getParameter("identifiant"), request.getParameter("mot_de_passe"))) {
									
									this.utilisateur = this.daoUtilisateur.getUtilisateurByPseudo(request.getParameter("identifiant"));
									
									if(this.utilisateur.getAdmin() == 1) {
										
										request.setAttribute("connecte", "oui");
										request.setAttribute("admin", "oui");
										
									} else if(this.utilisateur.getAdmin() == 0) {
										
										request.setAttribute("connecte", "oui");
										request.setAttribute("admin", "non");
										
									} else {
										request.setAttribute("error", "Votre compte n'a pas été vérifié !");
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
					request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
				case "gestion_droit":
					List<Utilisateur> liste = this.daoUtilisateur.listDB();
					request.setAttribute("liste", liste);
					
					request.getRequestDispatcher("/JSP/Gestion_permission.jsp").forward(request, response);
					break;	
				case "changement_groupe":
					String groupe=request.getParameter("groups");
					int identifiant = this.daoObjet.getIdByName(groupe);
					this.daoUtilisateur.addgroup(identifiant);
					request.getRequestDispatcher("/JSP/Gestion_permission.jsp").forward(request, response);

				case "add_user_page":
					List<Objet_General> liste2 = this.daoObjet.getInfosObjets();
					request.setAttribute("liste2", liste2);
					request.getRequestDispatcher("/JSP/AddUser.jsp").forward(request, response);
						
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
					request.getRequestDispatcher("/JSP/AddUser.jsp").forward(request, response);
					break;
				case "visitor_dashboard":
					
					
					
					request.getRequestDispatcher("/JSP/DashBoard.jsp").forward(request, response);
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
