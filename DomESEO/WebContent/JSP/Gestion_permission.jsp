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
				<form action="Process?state=changement_droit" id="form" method="post">
      				<input type="submit" class="button" value="Changement_droit">
	       		</form> 
	       		</td>
				<td>  		        
					<form action="Process?state=delete" id="form" method="post">
		        	<input type="submit" class="button" value="suppression">
		        </form>
		        </td>
			</tr>
		</c:forEach>
	</table>
</body>
</html>