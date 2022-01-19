<?php

if(!empty($_POST)){
	$errors = array();
	require_once '../inc/db.php';

	if (isset($_POST['btndemande'])) {
		if (!empty($_POST['username'])) {
			
			$sql = 'SELECT COUNT(*) AS num FROM users WHERE admin=1 AND username="'.$_POST['username'].'"';
			$recipesStatement = $pdo->prepare($sql);
			$recipesStatement->execute();
			$row = $recipesStatement->fetch(PDO::FETCH_ASSOC);
			if ($row['num'] >0) {
			 	
			 } ;
		}
		
	}


}

?>

<!DOCTYPE html>
<html>
<head>
	<link rel="stylesheet" href="../css/admin.css"/>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>ESEhome - RETROGRADATION ADMIN -</title>
</head>
<body>

	<?php /*require '../inc/header.php'; */?>
	<h1>ADMIN</h1>
	

	<div class="container">
		<div class="contact-form">
			
			<div class="main">
					
				<p>Demander la rétrogradation d'un admin</p>
					<form action="" method="POST">
					<input type="text" name="username" placeholder="Pseudo" class="champ" require/>

					<button type="submit" class="btn" name="btndemande">Faire une demande</button>
				</form>
			  </div>
		</div>
	</div>
	
	<div class="lien">
		<p><a href="ajoutuser.php">Ajouter un utilisateur</a></p>
		<p><a href="gestionuser.php">Gestion des utilisateurs</a></p>
		
	</div>



	<?php /*require '../inc/footer.php';*/?>
</body>
</html>