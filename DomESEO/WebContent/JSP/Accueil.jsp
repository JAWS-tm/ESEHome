<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Accueil - DomESEO</title>
</head>
<body>
	<header>
			
			<c:choose>
			<c:when test="${connecte == 'oui'}">  
      	 			test concluant  
    		</c:when>
    		</c:choose>
	</header>
		<div id="leftPart">
			<div id="connexion">
				<form method="POST" name="formulaire_connexion" action="Controleur?dest=connexion">
					<input type="text" name="identifiant" />
					<input type="password" name="mot_de_passe" />
					<input type="submit" name="connexion" value="se connecter" />
				</form>
			</div>
			<div id="Accès Visiteur">
				<p>Accéder au dashboard en accès visiteur</p>
				<button type="button">Accès</button>
			</div>
			<div id="Demande de privilège">
				<p>Faire une demande de privilage </p>
				<button type="button">Demande</button>
			</div>
		</div>
		<div id="rightPart">
			<div id="Présentation">
				<p>Ici, courte présentation de l'application + projet</p>
			</div>
		</div>
		
	
	<footer>
	
	
	
	
	</footer>

</body>
</html>