<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<head>
	<meta charset="UTF-8">
	<title>Edition profil - DomESEO</title>
	<link rel="stylesheet" href="CSS/Body.css">
	<link rel="stylesheet" href="CSS/ModifUtil.css">
</head>
<body>
	<%@include file="Header.jsp" %>
	<video id="bgVideo" preload="true" autoplay loop muted>
      	<source src="CSS/video/test.mp4" type="video/mp4" >
  	</video>
  	<div id="body">
  		<fieldset id="modif_fieldset">
  			<legend>Pomme</legend>
  		</fieldset>
	  	<h1>Fiche Utilisateur ${us.getPseudo()}</h1>
	
		<p>Modifier rôle</p>
		<p>Modifier groupe</p>
	
		<form action="Controleur?dest=deleteUser" id="form" method="post"
		
		onsubmit="return confirm('Etes-vous sûr de vouloir supprimer cet utilisateur ? Cette action est irréversible.');">
				        	
				        	<input id="idUtil2" type="hidden" name="idUtil2" value="${us.getId() }" />
				        	<input type="submit" class="button" value="Supprimer l'utilisateur">
				        	
		</form>
	
	
		<input type="button" onclick="window.location.href ='Controleur?dest=pageAdmin'" value="Retour">
  	</div>
</body>
</html>