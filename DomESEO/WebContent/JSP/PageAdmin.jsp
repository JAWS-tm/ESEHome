<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>domESEO - Administrateur</title>
</head>
<body>
	<h2>Liste des utilisateurs</h2>
	
<!-- 	<p style=color:blue><em>Les utilisateurs affichés en bleu ont fait une demande de privilège. Veuillez modifier leur rôle.</em></p>
 -->	
	
	<table>
		<tr id="top">
			<th>N°</th>
		    <th>Pseudo</th>
		    <th>-</th>
		</tr>
		<c:forEach  var="u" items="${ liste }" >
			<tr>
			
			
			<%-- <c:if test="${u.getAdmin() == -1 }"> --%>
				<td><c:out value="${ u.getId() }"/></td>
				<td><c:out value="${ u.getPseudo() }"/></td>
			<%-- </c:if>	 --%>
				<td>
				
					<form name="frm" method="post" action="Controleur?dest=modifUtil">
							
						<input id="idUtil" type="hidden" name="idUtil" value="${u.getId() }" />		
						<input id="modif" type="submit" name="btnModif" value="Modifier les attributs" />
								
					</form>
					
				</td>
					
				<!-- <td>
				<form action="Controleur?dest=changement_groupe" name="groups" type="hidden" id="form" method="post">
      				<select  name="utilisateurs" type="hidden" id="assignated_group">
      					<option value="">--Modifier le groupe d'objet--</option>
      					<option value="groupe_1">groupe 1</option>
				   		<option value="groupe_2">groupe 2</option>
					    <option value="groupe_3">groupe 3</option>
					    <option value="groupe_4">groupe 4</option>
      				</select>
	       		</form> 
	       		</td> -->
				
			</tr>
		</c:forEach>
	</table>
	
	<br><br>
	
	Création d'un nouvel utilisateur
	<button onclick="window.location.href ='Controleur?dest=create_user_page'">Création Utilisateur</button>
	
	<br>
	
	Création d'un nouveau groupe
	<button onclick="window.location.href ='Controleur?dest=create_group_page'">Création Groupe</button>
<!-- 	<input type="button" onclick="window.location.href ='Controleur?dest=connexion'" value="Retour">
 -->	
 
 <!-- à modifier une fois que les variables de session sont gérées -->
</body>
</html>