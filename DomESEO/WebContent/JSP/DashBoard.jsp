<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>DashBoard</title>
</head>
<body>
	<header></header>
	<h1>Dashboard</h1><br>
	<p>Informations sur les objets DomESEO en accès visiteur</p><br>
	<div id="affichage_Objets">
		<c:forEach var="u" items="${ liste }">
			<div class="Nom_Objet">
			
			
			</div>
		
		
		
		</c:forEach>
	
	</div>
	
	
	<footer></footer>	
</body>
</html>