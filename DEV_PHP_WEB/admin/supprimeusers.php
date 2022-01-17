<?php
	session_start();
	require_once '../inc/db.php';
	
	$sqlQueryAffiche = 'SELECT id, username, email FROM users WHERE admin = 0 ORDER BY username';
	$recipesStatementAffiche = $pdo->prepare($sqlQueryAffiche);
	$recipesStatementAffiche->execute();
	$users = $recipesStatementAffiche->fetchAll();
	
	if ($_SESSION['status'] == '') {
		$_SESSION['status'] = '';
	}
	// Suppression du compte
	if(isset($_POST['formdeleteuser']) AND isset($_POST['datadelet'])){

		$data = $_POST['datadelet'];
		$sqlQueryEfface = 'DELETE FROM users WHERE id="'.$data.'"';
		$recipesStatementEfface = $pdo->prepare($sqlQueryEfface);
		$recipesStatementEfface->execute();
		
		if ($recipesStatementEfface) {
			$_SESSION['status'] = "Utilisateur N°".$data." effacé de la base de données !";
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
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title></title>
		
</head>
<body>



	<?php 
	if ($_SESSION['status']) {
	?>
	<div> 
       <?php echo $_SESSION['status']; ?>
     
    </div>

	<?php 
	
	} ?>

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
</body>
</html>


