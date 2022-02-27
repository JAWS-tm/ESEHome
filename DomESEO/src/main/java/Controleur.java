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
			
			if(session.getAttribute("connecte") == "oui") {
						
				switch(destination) {
					case "deconnexion":
						session.removeAttribute("connecte");
						session.removeAttribute("id_user");
						session.removeAttribute("admin");
						session.removeAttribute("first_letter_user");
						processRequest(request, response, "accueil");
						break;		
						
					case "editUser":
						if((request.getParameter("pseudo") != null && !request.getParameter("pseudo").isEmpty()) && (request.getParameter("pass") != null && !request.getParameter("pass").isEmpty()) && (request.getParameter("confirm_pass") != null && !request.getParameter("confirm_pass").isEmpty())) {

							if(request.getParameter("pass").equals(request.getParameter("confirm_pass"))) {
								Utilisateur us = this.daoUtilisateur.getUtilisateurById((int)session.getAttribute("id_user"));
								if(this.daoUtilisateur.getUtilisateurByPseudo(request.getParameter("pseudo")) == null || (this.daoUtilisateur.getUtilisateurByPseudo(request.getParameter("pseudo"))).getId() == (int)(session.getAttribute("id_user"))) {
									us.setPseudo(request.getParameter("pseudo"));
									us.setMdp(request.getParameter("pass"));
									us.getAdmin();
									this.daoUtilisateur.updateUtilisateur((int)session.getAttribute("id_user"), request.getParameter("pseudo"), request.getParameter("pass"), us.getAdmin());
									request.setAttribute("succesC", "L'utilisateur "+request.getParameter("pseudo")+" a été créé avec succès.");
								}else {
									request.setAttribute("infoC", "Le pseudo a déjà été utilisé !");
								}
							}else {
								request.setAttribute("infoC", "Les deux mots de passe ne sont pas équivalents !");
							}
						} else {
							request.setAttribute("infoC", "Tous les champs ne sont pas complétés !");
						}
						processRequest(request, response, "modifUtil");
						break;
						
					case "pageAdmin":
						if(session.getAttribute("admin") == "oui") {
							List<Utilisateur> liste = this.daoUtilisateur.listDB();
							request.setAttribute("liste", liste);
							request.getRequestDispatcher("/JSP/PageAdmin.jsp").forward(request, response);
						}else {
							processRequest(request, response, "accueil");
						}
						break;
						
						
					case "changement_groupe":
						String groupe=request.getParameter("groups");
						int identifiant = this.daoObjet.getIdByName(groupe);
						this.daoUtilisateur.addgroup(identifiant);
						request.getRequestDispatcher("/JSP/PageAdmin.jsp").forward(request, response);
						break;
						
					case "modifUtil":
						int idUtil = (int)session.getAttribute("id_user");
						Utilisateur us = daoUtilisateur.getUtilisateurById(idUtil);
						request.setAttribute("us", us);
						request.getRequestDispatcher("/JSP/ModifUtil.jsp").forward(request, response);
						break;
					
					case "create_user_page":
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
						processRequest(request, response, "accueil");
						break;
						
					case "create_group_page":
						request.getRequestDispatcher("/JSP/CreateGroup.jsp").forward(request, response);
						break;
						
					case "create_group":
						String groupname = request.getParameter("groupname").trim();
						if(groupname != null && !groupname.isEmpty()) {
							if(daoGroupe_Objet.getGroupeByNom(groupname) == null) {
								daoGroupe_Objet.createNewGroup(groupname);
								request.setAttribute("succes3", "Le groupe "+groupname+" a été créé.");
							} else {
								request.setAttribute("error", "Un groupe avec ce nom existe déjà. Veuillez réessayer.");
							}
						} else {
							request.setAttribute("error", "Veuillez indiquer le nom du nouveau groupe.");
						}
						request.getRequestDispatcher("/JSP/CreateGroup.jsp").forward(request, response);
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
						
					case "deleteUser":
						int idUtil2 = Integer.parseInt(request.getParameter("idUtil2"));
						daoUtilisateur.deleteUtilisateur(idUtil2);
						request.setAttribute("liste", this.daoUtilisateur.listDB());
						request.getRequestDispatcher("/JSP/PageAdmin.jsp").forward(request, response);
						break;						
						
					case "accueil":
						List<Objet_General> liste_objet = this.daoObjet.getInfosObjets();
						List<Groupe> liste_groupe = this.daoGroupe_Objet.getNomGroupe(this.utilisateur.getId());
						request.setAttribute("liste_objet", liste_objet);
						request.setAttribute("liste_groupe", liste_groupe);
						request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
						break;
						
					case "user_dashboard" :
						String verif;
						String choix = "default";
						int idGroupe;
						List<Objet_General> liste_default = new ArrayList<>();
						verif = request.getParameter("verif");
						List<Groupe> list_group = this.daoGroupe_Objet.getNomGroupe(this.utilisateur.getId());
						request.setAttribute("listeVues", list_group);
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
						processRequest(request, response, "accueil");
						break;
				}
			}else {
				switch(destination) {
				
					case "accueil":
						if(session.getAttribute("connecte") == "oui") {
							request.setAttribute("id_user", session.getAttribute("id_user"));
						}
						request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
						break;
						
					case "connexion":
						if(request.getParameter("identifiant") != null && !request.getParameter("identifiant").isEmpty()) {
							if(request.getParameter("mot_de_passe") != null && !request.getParameter("mot_de_passe").isEmpty()) {
								if(this.daoUtilisateur.checkPseudo(request.getParameter("identifiant"))) {
									if(this.daoUtilisateur.checkLogin(request.getParameter("identifiant"), request.getParameter("mot_de_passe"))) {
										this.utilisateur = this.daoUtilisateur.getUtilisateurByPseudo(request.getParameter("identifiant"));
										if(this.utilisateur.getAdmin() == 1) {
											session.setAttribute("connecte", "oui");
											session.setAttribute("id_user", this.utilisateur.getId());
											session.setAttribute("admin", "oui");
											session.setAttribute("first_letter_user",this.utilisateur.getPseudo().substring(0, 1).toUpperCase());
											processRequest(request, response, "accueil");
										} else if(this.utilisateur.getAdmin() == 0) {
											session.setAttribute("connecte", "oui");
											session.setAttribute("id_user", this.utilisateur.getId());
											session.setAttribute("admin", "non");
											session.setAttribute("first_letter_user",this.utilisateur.getPseudo().substring(0, 1).toUpperCase());
											processRequest(request, response, "accueil");
										} else {
											request.setAttribute("is_error", "oui");
											request.setAttribute("error", "Pseudo ou mot de passe incorrect. Veuillez réessayer.");
											request.setAttribute("privilege", "non");
										}
									} else {
										request.setAttribute("is_error", "oui");
										request.setAttribute("error", "Pseudo ou mot de passe incorrect. Veuillez réessayer.");
									}
								} else {
									request.setAttribute("is_error", "oui");
									request.setAttribute("error", "Pseudo ou mot de passe incorrect. Veuillez réessayer.");
								}
							} else {
								request.setAttribute("is_error", "oui");
								request.setAttribute("error", "Veuillez indiquer un mot de passe.");
							}
						} else {
							request.setAttribute("is_error", "oui");
							request.setAttribute("error", "Veuillez indiquer le pseudonyme de l'utilisateur.");
						}
						request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
						break;
					default:
						request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
						break;
				}
			}
			
		} else {
			
			//On arrive sur le site et on n'a pas encore mis de destination --> renvoie à l'accueil
			request.getRequestDispatcher("/JSP/Accueil.jsp").forward(request, response);
		}
		
	}

}