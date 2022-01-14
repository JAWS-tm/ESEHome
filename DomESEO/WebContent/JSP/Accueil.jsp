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
			<form method="POST" name="formulaire_connexion" action="Controleur?dest=connexion">
				<input type="text" name="identifiant" />
				<input type="password" name="mot_de_passe" />
				<input type="submit" name="connexion" value="se connecter" />
			</form>
			<p>${ connecte }</p>
	</header>
	
	
	<footer>
	
	
	
	
	</footer>

</body>
</html>