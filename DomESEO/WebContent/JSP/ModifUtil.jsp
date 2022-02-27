<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<head>
	<meta charset="UTF-8">
	<title>Edition profil - DomESEO</title>
	<link rel="stylesheet" href="CSS/ModifUtil.css">
</head>
<body>
	<%@include file="Header.jsp" %>
  	<div id="body">
  		<fieldset id="modif_fieldset">
  			<legend>Modification du profil</legend>
  		</fieldset>
  		<!-- value="${us.getPseudo() }" -->
  		
  		<form action="Controleur?dest=editUser" method="post" class="form_with_input" autocomplete="off">
  			<label class="label_input">Pseudo</label>
  			<input class="input_form" name="pseudo" value="${us.getPseudo() }"/>
  			<label class="label_input">Mot de passe</label>
  			<input class="input_form" type="password" name="pass"/>
  			<label class="label_input">Confirmation de mot de passe</label>
  			<input class="input_form" type="password" name="confirm_pass" />
  			<button class="button_validate"><p>Modifier</p><img src="CSS/icone/editer_profil.svg" class="green_svg"/></button>
  		</form>
  		
  		<form action="Controleur?dest=accueil" method="post">
  			<button id="go_back_dashboard" type="submit"><img src="CSS/icone/fleche_gauche.svg" /><p>Revenir à l'accueil</p></button>
  		</form>
  		
  	</div>
</body>
</html>