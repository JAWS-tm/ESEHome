<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Admin - Cr�er un utilisateur</title>
</head>
<body>

<h1>Cr�er un utilisateur</h1>

<br><p style=color:red><em>${infoC }</em></p>
	<br><p style=color:green><em>${succesC }</em></p>
	<form name="create_utilisateur" method="POST" action="Controleur?dest=create_user">
		Pseudonyme :<input type="text" name="pseudo"><br>
		Mot de passe :<input type="password" name="password"><br>
		Confirmation du mot de passe :<input type="password" name="confirm_password"><br>
		
		<p><em>L'utilisateur a par d�faut le r�le d'un utilisateur typique.</em></p>
		<input type="button" onclick="javascript:history.go(-1)" value="Retour">
		<input type="submit" value="Cr�er">
	</form>

</body>
</html>