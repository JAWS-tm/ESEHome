<?php

if(!empty($_POST)){
	$errors = array();
	require_once '../inc/db.php';

	if(empty($_POST['username']) || !preg_match('/^[a-zA-Z0-9_]+$/',$_POST['username'])){
		$errors['username'] = "Le pseudo n'est pas valide";
	}else{
		$req = $pdo->prepare('SELECT id FROM users WHERE username = ?');
		$username = htmlspecialchars($_POST['username']);
		$req->execute([$username]);
		$user = $req->fetch();
		if($user){
			$errors['username'] = 'Ce pseudo est déjà pris !!';
		}
	}

	if(empty($_POST['email'])){
		$errors['email'] = "L'email n'est pas valide";
	}else{
		$req = $pdo->prepare('SELECT id FROM users WHERE email = ?');
		$email = htmlspecialchars($_POST['email']);
		$req->execute([$email]);
		$user = $req->fetch();
		if($user){
			$errors['email'] = 'Cet email est déjà pris !!';
		}
	}

	if(empty($_POST['password']) || $_POST['password'] != $_POST['password_confirm']){
		$errors['password'] = "Vous devez entrer un mot de passe valide";
	}




	if(empty($errors)){
		$req = $pdo->prepare("INSERT INTO users SET username = ?, email = ?, mdp = ?, admin = ?");
		
		$username = htmlspecialchars($_POST['username']);
		$email = htmlspecialchars($_POST['email']);
		$password = password_hash($_POST['password'], PASSWORD_BCRYPT);
		$type = $_POST["optradio"];
		$req->execute([$username, $email, $password, $type]);

		
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
					<input type="email" name="email" placeholder="Email" class="champ" require/>
				  

					
					<input type="password" name="password" placeholder="Mot De Passe" class="champ" require/>
					<input type="password" name="password_confirm" placeholder="Confirmez le mot de passe" class="champ" require/>

					<input type="radio" name="optradio" value="0" checked>User
					<input type="radio" name="optradio" value="1" >Admin<br><br>
					
					<button type="submit" class="btn">Ajouter</button>
				</form>
			  </div>
		</div>
	</div>
	
	
	<div class="lien">
		<p><a href="gestionuser.php">Gestion des utilisateurs</a></p>
		<p><a href="rétrogradationuser.php">Demande de rétrogradation d'un admin</a></p>
	</div>



	<?php /*require '../inc/footer.php';*/?>
</body>
</html>


