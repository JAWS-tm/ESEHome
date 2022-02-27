
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<!DOCTYPE html>
<html>
	<head>		
		<meta charset="UTF-8">
		<link rel="stylesheet" href="CSS/Dashboard.css">
    	<script src="JS/Dashboard.js"></script>
		<title>DashBoard</title>
	</head>
	<body>
	
		<c:if test="${ connecte == 'oui' }">
			<div id="select_groupe">
				<select id="groupe" size="1">
					<option value="all" selected>Tout les groupes</option>
					<c:forEach var="ligne" items="${ liste_groupe }">
						<option value="${ ligne.getId() }">${ ligne.getNom_groupe() }</option>
					</c:forEach>
				</select>
				<img src="CSS/icone/chevron_down.svg"/>
			</div>
		</c:if>
	
		
		
		<c:forEach var="g" items="${ liste_groupe }">
			<div id="${ g.getId()}" class="show groupe_of_object">
				<fieldset id="title_fieldset">
					<legend>${ g.getNom_groupe()}</legend>
				</fieldset>
				<div class="liste_objet">
					<c:forEach var="obj" items="${liste_objet}">
						<c:if test="${obj.getId_groupe() == g.getId() }">
							<div class="objet">
								<div class="objet_title">
									${ obj.getNom_Objet()}
								</div>
								<div class="objet_state">
									Valeur : ${ obj.getValeur()}
								</div>
							</div>
						</c:if>
					</c:forEach>
				</div>
			</div>
		</c:forEach>
	
	</body>
</html>