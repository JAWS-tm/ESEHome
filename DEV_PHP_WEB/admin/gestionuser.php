<?php
session_start();
if ($_SESSION['statu'] == '') {
	$_SESSION['statu'] = '';
}
require_once '../inc/db.php';

$sqlQueryAffiche = 'SELECT id, username, email, admin FROM users WHERE admin = 0 ORDER BY username';
$recipesStatementAffiche = $pdo->prepare($sqlQueryAffiche);
$recipesStatementAffiche->execute();
$users = $recipesStatementAffiche->fetchAll();

// Promotion du compte
if(isset($_POST['formpromouser']) AND isset($_POST['datapromo'])){
	
	$data = $_POST['datapromo'];
	$sqlQueryPromot = 'UPDATE users SET admin = 1 WHERE id="'.$data.'"';
	$recipesStatementPromot = $pdo->prepare($sqlQueryPromot);
	$recipesStatementPromot->execute();
	
	if ($recipesStatementPromot) {
		$_SESSION['statu'] = "Utilisateur N°".$data." a été promu au rang d'admin !";
		header("Location: gestionuser.php");
	}
	else{
		echo "OUPS, il y a une erreur !!!";
	}
	
}


// Gestion du compte
if(isset($_POST['formdeleteuser']) AND isset($_POST['datadelet'])){
	
	$data = $_POST['datadelet'];
	$sqlQueryEfface = 'DELETE FROM users WHERE id="'.$data.'"';
	$recipesStatementEfface = $pdo->prepare($sqlQueryEfface);
	$recipesStatementEfface->execute();
	
	if ($recipesStatementEfface) {
		$_SESSION['statu'] = "Utilisateur N°".$data." effacé de la base de données !";
		header("Location: gestionuser.php");
	}
	else{
		echo "OUPS, il y a une erreur !!!";
	}
	
}

?>

<!DOCTYPE html>
<html>
<head>
	<link rel="stylesheet" href="../css/admin.css"/>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>ESEhome - GESTION UTILISATEUR -</title>
		
</head>
<body>
	<?php /*require '../inc/header.php'; */?>
	<h1>ADMIN</h1>

	<?php 
	if ($_SESSION['statu']) {
	?>
	<div class="alert"> 
	   <?php echo $_SESSION['statu']; ?>
	 
	</div>

	<?php } ?>

	<div class="container">
		<div class="contact-form">
			
			<div class="main">
					
				<p>Gestion utilisateur</p>
				<table id="table">
				<tr>
					<th>ID</th>
					<th>PSEUDO</th>
					<th>EMAIL</th>
					<th>STATUT</th>
				</tr>
				<?php
					// On affiche chaque recette une à une
					foreach ($users as $recipe) {
				?>	
					<form action="" method="post">
						<tr>
							<td><?php echo $recipe->id;?></td>
							<td><?php echo $recipe->username;?></td>
							<td><?php echo $recipe->email;?></td>
							<td><?php echo $recipe->admin;?></td>
							<td id="espace"><input type="hidden" name="datapromo" value="<?php echo $recipe->id; ?>">
								<button type="submit" name="formpromouser">Promouvoir</button>
							</td>
							<td><input type="hidden" name="datadelet" value="<?php echo $recipe->id; ?>">
								<button type="submit" name="formdeleteuser">Supprimer le compte</button>
							</td>
						</tr>
					</form>
				<?php } ?>
				</table>	
			</div>
		</div>
	</div>
	<div class="lien">
		<p><a href="ajoutuser.php">Ajouter un utilisateur</a></p>
		<p><a href="rétrogradationuser.php">Demande de rétrogradation d'un admin</a></p>
	</div>

	<?php /*require '../inc/footer.php';*/?>

	
</body>
</html>


