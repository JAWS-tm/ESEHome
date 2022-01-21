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
				<c:if test="${ admin == 'oui' }">
					<button onclick="window.location.href ='Controleur?dest=page_admin'">Partie Admin</button>
				</c:if>
				<c:if test="${ admin == 'non' }">
					<button onclick="window.location.href ='Controleur?dest=user_dashboard'">Accès au Dashboard de votre compte</button>
				</c:if>
    		</c:when>
    		
    		<c:otherwise>
    			<div id="leftPart">
					<div id="connexion">
						<form method="POST" name="formulaire_connexion" action="Controleur?dest=connexion">
							<input type="text" name="identifiant" />
							<input type="password" name="mot_de_passe" />
							<input type="hidden" name="source" value="Accueil" />
							<input type="submit" name="connexion" value="se connecter" /><br>
							<p>${ error }</p>
						</form>
					</div>
				<c:if test="${ privilege != 'non' }">
					<div id="Demande de privilège">
						<p>Faire une demande de privilège </p>
						<button type="button" onclick="window.location.href ='Controleur?dest=add_user_page'">Demande</button>
					</div>
				</c:if>
				
					<div id="Accès Visiteur">
						<p>Accéder au dashboard en accès visiteur</p>
						<button type="button" onclick="window.location.href = 'Controleur?dest=visitor_dashboard'">Accès</button>
					</div>
				</div>
    		</c:otherwise>
    	</c:choose>
	</header>
		<div id="rightPart">
			<div id="Présentation">
				<p>Ici, courte présentation de l'application + projet</p>
			</div>
		</div>	
	<footer>
	
	
	
	
	</footer>

</body>
</html>