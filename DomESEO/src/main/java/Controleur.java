import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import beans.Utilisateur;
import dao.DAOFactory;
import dao.DAOUtilisateur;
import dao.DAOUtilisateurMariaDB;

/**
 * Servlet implementation class Controleur
 */
@WebServlet("/Controleur")
public class Controleur extends HttpServlet {
	
	private static final long serialVersionUID = 1L;
    private Utilisateur utilisateur;   
    private DAOUtilisateur daoUtilisateur;
    
    
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Controleur() {
        super();
        // TODO Auto-generated constructor stub
    }

    public void init() {
    	DAOFactory daoFactory = DAOFactory.getInstance();
    	this.daoUtilisateur = daoFactory.getDAOUtilisateur("MariaDB");
    	
    }
    
	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		processRequest(request, response, request.getParameter("dest"));
		//response.getWriter().append("Served at: ").append(request.getContextPath());
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		//doGet(request, response);
		processRequest(request, response, request.getParameter("dest"));
	}
	
	protected void processRequest(HttpServletRequest request, HttpServletResponse response,String dest) throws ServletException, IOException {
		String destination = dest;
		
		if(destination != null) {
			
			switch(destination) {
				case "accueil":
					request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
					break;
				case "connexion":
					if((request.getParameter("identifiant") !="") && (request.getParameter("mot_de_passe") != "")) {
						
						if(this.daoUtilisateur.checkLogin(request.getParameter("identifiant"), request.getParameter("mot_de_passe"))) {
							
							this.utilisateur = this.daoUtilisateur.getUtilisateurByPseudo(request.getParameter("identifiant"));
							
							if(this.utilisateur.getAdmin() == 1) {
								
								request.setAttribute("connecte", "oui");
								request.setAttribute("admin", "oui");
								
							}else if(this.utilisateur.getAdmin() == 0) {
								
								request.setAttribute("connecte", "oui");
								request.setAttribute("admin", "non");
								
							}else {
								request.setAttribute("error", "Votre compte n'a pas �t� v�rifi� !");
							}
							
						}else {
							request.setAttribute("error", "La combinaison identifiant/mot de passe n'est pas valide !");
						}
						
					}else {
						request.setAttribute("error", "Veuillez compl�ter tous les champs !");
					}
					request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
				case "add_user_page":
					
						request.getRequestDispatcher("/JSP/AddUser.jsp").forward(request, response);
						
					break;
				case "add_user":
					if((request.getParameter("pseudo") !="") && (request.getParameter("password") != "")&& (request.getParameter("confirm_password") != "")) {
						
						if(request.getParameter("password").equals(request.getParameter("confirm_password"))) {
							
							if(!this.daoUtilisateur.checkPseudo(request.getParameter("pseudo"))) {
								
								this.daoUtilisateur.ajouterUtilisateur(request.getParameter("pseudo"), request.getParameter("password"), -1);
								request.setAttribute("info", "Demande envoy� !");
							}else { 
								
								request.setAttribute("info", "Le pseudo a d�j� �t� utilis� !");
							}
						}else {
							
							request.setAttribute("info", "Les deux mots de passe ne sont pas �quivalents !");
						}
					}else {
						request.setAttribute("info", "Tous les champs ne sont pas compl�t�s !");
					}
					request.getRequestDispatcher("/JSP/AddUser.jsp").forward(request, response);
					break;
				default:
					//On ne doit pas se retrouver ici !
					request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
					break;
			}
			
		}else {
			
			//On arrive sur le site et on n'a pas encore mis de destination --> renvoie � l'accueil
			request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
		}
		
	}

}
