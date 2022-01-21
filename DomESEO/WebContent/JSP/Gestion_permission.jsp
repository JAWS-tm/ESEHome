<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
	<h2>Liste des utilisateurs</h2>
	<table>
		<tr id="top">
			<th>N°</th>
		    <th>Pseudo</th>
		    <th>Admin</th>
		</tr>
		<c:forEach  var="u" items="${ liste }" >
			<tr>
				<td><c:out value="${ u.getId() }"/></td>
				<td><c:out value="${ u.getPseudo() }"/></td>
				<td><c:out value="${ u.getAdmin() }"/></td>
				<td>
				<form action="Controleur?dest=changement_groupe" name="groups" type="hidden" id="form" method="post">
      				<select  name="groups" type="hidden" id="assignated_group">
      					<option value="">--Modifier le groupe d'objet--</option>
      					<option value="groupe_1">groupe 1</option>
				   		<option value="groupe_2">groupe 2</option>
					    <option value="groupe_3">groupe 3</option>
					    <option value="groupe_4">groupe 4</option>
      				</select>
	       		</form> 
	       		</td>
				<td>  		        
				<form action="Controleur?dest=deleteUser" id="form" method="post">
		        	<input type="submit" class="button" value="suppression">
		        </form>
		        </td>
			</tr>
		</c:forEach>
	</table>
</body>
</html>