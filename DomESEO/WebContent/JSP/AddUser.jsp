<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Ajout d'un utilisateur</title>
</head>
<body>
	<p>${ info }</p>
	<form name="ajouter_utilisateur" method="POST" action="Controleur?dest=add_user">
		pseudo :<input type="text" name="pseudo"><br>
		mot de passe :<input type="password" name="password"><br>
		confirmer le mot de passe :<input type="password" name="confirm_password"><br>
		<input type="submit" value="ajouter">
	</form>
</body>
</html>