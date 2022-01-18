

<?php
	session_start();
	if ($_SESSION['statusRetrogradation'] == '') {
		$_SESSION['statusRetrogradation'] = '';
	}
	require_once '../inc/db.php';
	
	$sqlQueryAfficheAdmin = 'SELECT id, username, email, admin FROM users WHERE admin = 1 ORDER BY username';
	$recipesStatementAfficheAdmin = $pdo->prepare($sqlQueryAfficheAdmin);
	$recipesStatementAfficheAdmin->execute();
	$usersAdmin = $recipesStatementAfficheAdmin->fetchAll();
	
	// Promotion du compte
	if(isset($_POST['formpromouser']) AND isset($_POST['datapromo'])){


		
		if ($recipesStatementPromot) {
			$_SESSION['statusRetrogradation'] = "Demande de rétrogradation de l'utilisateur N°".$data." !";
			header("Location: promotionuser.php");
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
	<title>ESEhome - RETROGRADER UTILISATEUR -</title>
		
</head>
<body>
	<?php /*require '../inc/header.php'; */?>
	
	<h1>ADMIN</h1>

	<?php 
	if ($_SESSION['statusRetrogradation']) {
	?>
	<div class="alert"> 
	   <?php echo $_SESSION['statusRetrogradation']; ?>
	 
	</div>

	<?php } ?>

	<div class="container">
		<div class="contact-form">
			
			<div class="main">
					
				<p>Demande de rétrogradation d'un admin</p>
				<table>
				<?php
					// On affiche chaque recette une à une
					foreach ($usersAdmin as $recipe) {
				?>	
					<form action="" method="post">
						<tr>
							<td><?php echo $recipe->id;?></td>
							<td><?php echo $recipe->username;?></td>
							<td><?php echo $recipe->email;?></td>
							<td><?php echo $recipe->admin;?></td>
							<td><input type="hidden" name="datapromo" value="<?php echo $recipe->id; ?>">
								<button type="submit" name="formpromouser">Faire une demande</button>
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
