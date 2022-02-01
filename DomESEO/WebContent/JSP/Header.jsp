<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html>
<head>
	<link rel="stylesheet" href="CSS/Header.css">
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
				<p>Faire une demande de privilège </p>
				<button type="button" onclick="window.location.href ='Controleur?dest=add_user_page'">Demande</button>
				<button type="button" onclick="window.location.href ='Controleur?dest=deconnexion'">Déconnexion</button>
			</div>
		</c:if>
		<c:if test="${ connecte != 'oui' }">
			<button id="connexion_bouton" class="header_bouton" type="button" onclick="ouvrir_connexion_popin()">Connexion</button>
		</c:if>
	</div>
</div>

</html>