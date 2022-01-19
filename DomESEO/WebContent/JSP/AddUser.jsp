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
		<input type="text" name="pseudo">
		<input type="password" name="password">
		<input type="password" name="confirm_password">
	</form>
</body>
</html>