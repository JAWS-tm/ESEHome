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
					System.out.println("1");
					if((request.getParameter("identifiant") !="") && (request.getParameter("mot_de_passe") != "")) {
						
						if(this.daoUtilisateur.checkLogin(request.getParameter("identifiant"), request.getParameter("mot_de_passe"))) {
							
							this.utilisateur = this.daoUtilisateur.getUtilisateurByPseudo(request.getParameter("identifiant"));
							request.setAttribute("connecte", "oui");
							request.setAttribute("admin", "oui");
							
						}else {
							request.setAttribute("error", "La combinaison identifiant/mot de passe n'est pas valide !");
						}
						
					}else {
						request.setAttribute("error", "Veuillez compléter tous les champs !");
					}
					request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
				case "add_user_page":
					if(this.utilisateur.getAdmin() == 1) {
						request.getRequestDispatcher("/JSP/AddUser.jsp").forward(request, response);
					}else {
						request.setAttribute("connecte", "oui");
						processRequest(request, response, "accueil");
					}
					break;
				case "add_user":
					if(request.getParameter("password").equals(request.getParameter("confirm_password"))) {
						
						if(!this.daoUtilisateur.checkPseudo(request.getParameter("pseudo"))) {
							
							this.daoUtilisateur.ajouterUtilisateur(request.getParameter("pseudo"), request.getParameter("password"), 0);
							request.setAttribute("info", "Utilisateur créé !");
						}else { 
							
							request.setAttribute("info", "Le pseudo a déjà été utilisé !");
						}
					}else {
						
						request.setAttribute("info", "Les deux mots de passe ne sont pas équivalents !");
					}
					request.getRequestDispatcher("/JSP/AddUser.jsp").forward(request, response);
					break;
				default:
					//On ne doit pas se retrouver ici !
					request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
					break;
			}
			
		}else {
			
			//On arrive sur le site et on n'a pas encore mis de destination --> renvoie à l'accueil
			request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
		}
		
	}

}
