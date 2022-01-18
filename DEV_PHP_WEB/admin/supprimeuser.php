<?php
	session_start();
	if ($_SESSION['statusSupprime'] == '') {
		$_SESSION['statusSupprime'] = '';
	}
	require_once '../inc/db.php';
	
	$sqlQueryAffiche = 'SELECT id, username, email FROM users WHERE admin = 0 ORDER BY username';
	$recipesStatementAffiche = $pdo->prepare($sqlQueryAffiche);
	$recipesStatementAffiche->execute();
	$users = $recipesStatementAffiche->fetchAll();
	

	// Suppression du compte
	if(isset($_POST['formdeleteuser']) AND isset($_POST['datadelet'])){

		$data = $_POST['datadelet'];
		$sqlQueryEfface = 'DELETE FROM users WHERE id="'.$data.'"';
		$recipesStatementEfface = $pdo->prepare($sqlQueryEfface);
		$recipesStatementEfface->execute();
		
		if ($recipesStatementEfface) {
			$_SESSION['statusSupprime'] = "Utilisateur N°".$data." effacé de la base de données !";
			header("Location: supprimeusers.php");
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
	<title>ESEhome - SUPPRIMER UTILISATEUR -</title>
		
</head>
<body>
	<?php /*require '../inc/header.php'; */?>
	<h1>ADMIN</h1>

	<?php 
	if ($_SESSION['statusSupprime']) {
	?>
	<div class="alert"> 
	   <?php echo $_SESSION['statusSupprime']; ?>
	 
	</div>

	<?php } ?>

	<div class="container">
		<div class="contact-form">
			
			<div class="main">
					
				<p>Supprimer un utilisateur</p>
				<table>
				<?php
					// On affiche chaque recette une à une
					foreach ($users as $recipe) {
				?>	
					<form action="" method="post">
						<tr>
							<td><?php echo $recipe->id;?></td>
							<td><?php echo $recipe->username;?></td>
							<td><?php echo $recipe->email;?></td>
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

	<?php /*require '../inc/footer.php';*/?>

	
</body>
</html>


