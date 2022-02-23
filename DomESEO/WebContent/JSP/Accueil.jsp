<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<title>Accueil - DomESEO</title>
	<link rel="stylesheet" href="CSS/Body.css">
	<link rel="stylesheet" href="CSS/Accueil.css">
</head>
<body>
	<%@include file="Header.jsp" %>
	<%--<c:if test="${ connecte == 'oui' }">
		<%@include file="User_Dashboard.jsp" %>
	</c:if>
	<c:if test="${ connecte != 'oui' }">
		<%@include file="Visiteur_Dashboard.jsp" %>
	</c:if>--%>
				
						<p>Accéder au dashboard en accès visiteur</p>
						<button type="button" onclick="window.location.href = 'Controleur?dest=visitor_dashboard'">Accès</button>
			
		<div id="rightPart">
			<div id="Présentation">
				<p>Ici, courte présentation de l'application + projet</p>
			</div>
		</div>	

</body>
<div id="connexion_popin" style="display : none;">
	<form method="POST" name="formulaire_connexion" action="Controleur?dest=connexion">
		<input type="text" name="identifiant" />
		<input type="password" name="mot_de_passe" />
		<input type="hidden" name="source" value="Accueil" />
		<input type="submit" name="connexion" value="se connecter" /><br>
		<p style=color:red>${ error }</p>
	</form>
	<button id="fermeture_connexion_bouton" class="" type="button" onclick="fermer_connexion_popin()">Fermer</button>
</div>
</html>