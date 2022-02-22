<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html>
<head>
	<link rel="stylesheet" href="CSS/Header.css">
	<link rel="stylesheet" href="CSS/Body.css">
	<script src="LIB/jquery/jquery-3.6.0.min.js"></script>
    <script src="JS/Header.js"></script>
</head>
<div id="header">
	<div id="logo_header">
		<img id="domeseo_logo_header" src="CSS/icone/logo_header.svg">
	</div>
	<div id="div_droite_header">
		<c:if test="${ connecte == 'oui' }">
			<div id="profil_header">
			<button id="profil_bouton"  type="button" onclick="toggle_profil_menu()">A</button>
			</div>
		</c:if>
		<c:if test="${ connecte != 'oui' }">
			<button id="connexion_bouton" type="button" onclick="ouvrir_connexion_popin()">Connexion</button>
		</c:if>
	</div>
</div>
<div id="profil_menu_popin" class="close">
		<button type="button" class="profil_menu_bouton" onclick="window.location.href ='Controleur?dest=deconnexion'"><img class="profil_menu_bouton_icon" src="CSS/icone/editer_profil.svg"></button>
		<button type="button" class="profil_menu_bouton" onclick="window.location.href ='Controleur?dest=deconnexion'"><img class="profil_menu_bouton_icon red_svg" src="CSS/icone/deconnexion.svg"></button>
</div>
<div id="connexion_popin" style="display : none;">
	<div id="div_formulaire_connexion">
		<div id="title">
			<p>Connexion</p><img id="connexion_logo" src="CSS/icone/connexion.svg" />
		</div>
		<form method="POST" name="formulaire_connexion" action="Controleur?dest=connexion">
			<div id="formulaire">
				<fieldset>
				    <legend>Pseudo</legend>
					<input type="text" name="identifiant" />
				</fieldset>
			 	<fieldset>
					<legend>Mot de passe</legend>
					<input type="password" name="mot_de_passe" />
				</fieldset>
				<p style=color:red>${ error }</p>
			</div>
			<div id="boutton_formulaire_connexion">
				<button id="boutton_connexion" type="submit" name="connexion">
					<img id="check_connexion" class="green_svg" src="CSS/icone/check.svg" />
					<p>Se connecter</p>
				</button><br>
				<button id="fermeture_connexion_bouton" class="" type="button" onclick="fermer_connexion_popin()">
					<p>Fermer</p>
					<img id="close_connexion" class="red_svg" src="CSS/icone/croix.svg" />
				</button>
			</div>
		</form>
	</div>
</div>
</html>

<%--
				<button type="button" onclick="window.locatioxn.href ='Controleur?dest=add_user_page'">Demande</button>
				--%>