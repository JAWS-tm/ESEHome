<?php
	
	include("php/bdd.php");

	if (isset($_POST['formconnexion'])) {
		$pseudoconnect = htmlspecialchars($_POST['usernameconnect']);
		$mdpconnect = $_POST['passwordconnect'];
		
		if (!empty($_POST['usernameconnect']) AND !empty($_POST['passwordconnect'])) {
			
			$requser = $pdo->prepare("SELECT * FROM utilisateur WHERE Pseudo = ?");
			
			$requser->execute(array($pseudoconnect));
			$userexist = $requser->fetch();
			
			if($userexist && password_verify($mdpconnect, $userexist->MotDePasse )) {
				
				session_start();
				
				$_SESSION['id'] = $userexist->id;
				$_SESSION['pseudo'] = $userexist->Pseudo;
				$_SESSION['admin'] = $userexist->Admin;
				
				header("Location: index.php");
			}
			else {
				$erreur = "L'utilisateur n'existe pas !";
			}
		}
		else {
			$erreur = "Tous les champs doivent être complétés !";
		}
	}



?>


<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>ESEHOME</title>
</head>
<body>

	<?php include('html/header.php'); ?>
	
	<h1>Se Connecter</h1>
	
	<div class="container">
		<div class="contact-form">

			<div class="main">
				<h2>Connexion</h2>
				<form action="" method="POST">

					<input type="text" name="usernameconnect" placeholder="Nom d'utilisateur" class="champ" require/>
					<input type="password" name="passwordconnect" placeholder="Mot De Passe" class="champ" require/>
					

					<button type="submit" name="formconnexion" class="btn">M'inscrire</button>

					<?php
					if(isset($erreur)) {
						echo '<font color="red">'.$erreur."</font>";
					}
					?>
				</form>

				Vous êtes nouveau ici? <a href="inscription.php">S'inscrire</a>
				<br>
                <a href="deconnexion.php">Se déconnecter</a>
			</div>

		</div>
	</div>



</body>
</html>