<?php

if(!empty($_POST)){
	$errors = array();
	$droits = 0;
	require_once '../inc/db.php';

	if(empty($_POST['username']) || !preg_match('/^[a-zA-Z0-9_]+$/',$_POST['username'])){
		$errors['username'] = "Le pseudo n'est pas valide";
	}else{
		$req = $pdo->prepare('SELECT id FROM utilisateur WHERE Pseudo = ?');
		$username = htmlspecialchars($_POST['username']);
		$req->execute([$username]);
		$user = $req->fetch();
		if($user){
			$errors['username'] = 'Ce pseudo est déjà pris !!';
		}
	}


	if(empty($_POST['password']) || $_POST['password'] != $_POST['password_confirm']){
		$errors['password'] = "Vous devez entrer un mot de passe valide";
	}
	



	if(empty($errors)){
		$req = $pdo->prepare("INSERT INTO utilisateur SET Pseudo = ?, MotDePasse = ?, Admin = ?");
		$username = htmlspecialchars($_POST['username']);
		$password = password_hash($_POST['password'], PASSWORD_BCRYPT);
		$admin = htmlspecialchars($_POST['admin']);
		$req->execute([$username, $password, $admin]);	
		
		require_once '../goupe_utilisater.php';
	}
}

?>

<!DOCTYPE html>
<html>
<head>
	<link rel="stylesheet" href="../css/admin.css"/>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>ESEhome - AJOUT UTILISATEUR -</title>
</head>
<body>

	<?php /*require '../inc/header.php'; */?>
	<h1>ADMIN</h1>
	<?php if(!empty($errors)): ?>
		<div class="alert">
			<p>Vous n'avez pas rempli le formulaire correctement</p>
			<ul>
				<?php foreach($errors as $error): ?>
					<li><?= $error; ?></li>
				<?php endforeach; ?>
			</ul>
		</div>
	<?php endif; ?>

	<div class="container">
		<div class="contact-form">
			
			<div class="main">
					
				<h2>Ajout d'un utilisateur</h2>
					<form action="" method="POST">
					<input type="text" name="username" placeholder="Nom d'utilisateur ou adresse e-mail" class="champ" require/>
					  
					<input type="password" name="password" placeholder="Mot De Passe" class="champ" require/>
					<input type="password" name="password_confirm" placeholder="Confirmez le mot de passe" class="champ" require/>

					<input type="hidden" name="admin" value="0" require/>
					<h2>Choisir ses droits</h2>
					<p>
					<input type="checkbox" name="lumiere" id="droit1" value="1" />
					<label for="droit1" aria-describedby="label">Lumiere</label>
					</p>
					<p>
					<input type="checkbox" name="alarm" id="droit2" value="2">
					<label for="droit2" aria-describedby="label">Alarm</label> 
					</p>
					<p>
					<input type="checkbox" name="meteo" id="droit3" value="3">
					<label for="droit3" aria-describedby="label">Meteo</label> 
					</p>
					<button type="submit" class="btn">Ajouter</button>
				</form>
			  </div>
		</div>
	</div>
		
	<div class="lien">
		<p><a href="gestionuser.php">Gestion des utilisateurs</a></p>
		<p><a href="rétrogradationuser.php">Demande de rétrogradation d'un admin</a></p>
	</div>



	<?php require '../inc/footer.php';?>



