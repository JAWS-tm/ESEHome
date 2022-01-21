
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<!DOCTYPE html>
<html>
<head>
<link rel="stylesheet" href="CSS/Visitor_Dashboard.css" type="text/css">
<meta charset="UTF-8">
<title>DashBoard</title>
</head>
<body>
	<header>
		<div id="connexion">
			<form method="POST" name="formulaire_connexion" action="Controleur?dest=connexion">
				<input type="text" name="identifiant" />
				<input type="password" name="mot_de_passe" />
				<input type="hidden" name="source" value="DashBoard" />
				<input type="submit" name="connexion" value="se connecter" /><br>
				<p>${ error }</p>
			</form>
		</div>
		<button onclick="window.location.href ='Controleur?dest=accueil'">Accueil</button>
	</header>
	<h1>Dashboard</h1><br>
	<p>Informations sur les objets DomESEO en accès visiteur</p><br>
	<div id="affichage_Objets">
		<c:forEach var="u" items="${ liste2 }">
			<div class="dashboard_tile">
				<div class="Nom_Objet">
					<p class="Name"><c:out value="${ u.getNom_Objet()}"/></p>
			
				</div>
				<div class="Info_objet">
					<p class="Value"><c:out value="${ u.getValeur() }"/></p>
				</div>
			</div>
		</c:forEach>
	
	</div>
	
	
	<footer></footer>	
</body>
</html>