<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Admin - Créer un groupe</title>
</head>
<body>

<h1>Création d'un nouveau groupe</h1>

<br><p style=color:red><em>${error }</em></p>
<br><p style=color:green><em>${succes3 }</em></p>

	<form name="creation_groupe" method="POST" action="Controleur?dest=create_group">
	
		Nom du groupe :<input type="text" name="groupname"><br>
		
		
		<input type="submit" value="Créer groupe">
	</form>

</body>
</html>