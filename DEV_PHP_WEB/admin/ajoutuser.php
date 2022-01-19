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
	
	if(isset($_POST['chambre'])){
	    $droits = $droits + $_POST['chambre'];
	}
	if(isset($_POST['Cuisine'])){
	    $droits = $droits + $_POST['Cuisine'];
	}
	if(isset($_POST['SalleDeBain'])){
	    $droits = $droits + $_POST['SalleDeBain'];
	}



	if(empty($errors)){
		$req = $pdo->prepare("INSERT INTO utilisateur SET Pseudo = ?, MotDePasse = ?, Admin = ?, droit = ?");
		
		$username = htmlspecialchars($_POST['username']);
		$password = password_hash($_POST['password'], PASSWORD_BCRYPT);
		$admin = htmlspecialchars($_POST['admin']);
		$req->execute([$username, $password, $admin, $droits]);

		
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
					
				<p>Ajout d'un utilisateur</p>
					<form action="" method="POST">
					<input type="text" name="username" placeholder="Pseudo" class="champ" require/>
					  
					<input type="password" name="password" placeholder="Mot De Passe" class="champ" require/>
					<input type="password" name="password_confirm" placeholder="Confirmez le mot de passe" class="champ" require/>

					<input type="hidden" name="admin" value="0" require/>
					<p>Choisir ses droits</p>
					<input type="checkbox" name="chambre" value="1"> Chambre<br>
					<input type="checkbox" name="Cuisine" value="2"> Cuisine<br>
					<input type="checkbox" name="SalleDeBain" value="3"> Salle De Bain<br>
					
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



