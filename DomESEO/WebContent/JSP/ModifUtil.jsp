<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Gérer l'utilisateur ${us.getPseudo()}</title>
</head>
<body>

<h1>Fiche Utilisateur ${us.getPseudo()}</h1>

	<p>Modifier rôle</p>
	<p>Modifier groupe</p>

<form action="Controleur?dest=deleteUser" id="form" method="post"

onsubmit="return confirm('Etes-vous sûr de vouloir supprimer cet utilisateur ? Cette action est irréversible.');">
		        	
		        	<input id="idUtil2" type="hidden" name="idUtil2" value="${us.getId() }" />
		        	<input type="submit" class="button" value="Supprimer l'utilisateur">
		        	
</form>


<input type="button" onclick="window.location.href ='Controleur?dest=pageAdmin'" value="Retour">

</body>
</html>