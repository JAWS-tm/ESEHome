<?php
	session_start();
	if ($_SESSION['statusPromotion'] == '') {
		$_SESSION['statusPromotion'] = '';
	}
	require_once '../inc/db.php';
	
	$sqlQueryAffiche = 'SELECT id, username, admin FROM users WHERE admin = 0 ORDER BY username';
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
			$_SESSION['statusPromotion'] = "Utilisateur N°".$data." promu dans la base de données !";
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
	<title>ESEhome - PROMOUVOIR UTILISATEUR -</title>
		
</head>
<body>
	<?php /*require '../inc/header.php'; */?>
	
	<h1>ADMIN</h1>

	<?php 
	if ($_SESSION['statusPromotion']) {
	?>
	<div class="alert"> 
	   <?php echo $_SESSION['statusPromotion']; ?>
	 
	</div>

	<?php } ?>

	<div class="container">
		<div class="contact-form">
			
			<div class="main">
					
				<p>Promouvoir un utilisateur</p>
				<table>
				<?php
					// On affiche chaque recette une à une
					foreach ($users as $recipe) {
				?>	
					<form action="" method="post">
						<tr>
							<td><?php echo $recipe->id;?></td>
							<td><?php echo $recipe->username;?></td>
							<td><?php echo $recipe->admin;?></td>
							<td><input type="hidden" name="datapromo" value="<?php echo $recipe->id; ?>">
								<button type="submit" name="formpromouser">Promouvoir</button>
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


