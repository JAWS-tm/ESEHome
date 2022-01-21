<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Visitor - DashBoard</title>
</head>
<body>
	<div id="object-view">
		<form method="POST" name="formulaire_Choix" action="Controleur?dest=user_dashboard&verif=true">
			<p>
				<label for="choice">Choisissez les vues d'objets que vous souhaitez visualiser</label>
				<select name="choice" id="choice">
					<option value="default" selected>Dahsboard par défaut</option>
				
				<c:forEach var="u" items="${ listeVues }">
					<option value="${ u.getId()}"><c:out value="${ u.getNom_groupe()}"/></option>
				</c:forEach>
				
				</select>
			</p>
			<input type="submit" value="Changer de Vue"/>
		</form>
	</div>
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
</body>
</html>