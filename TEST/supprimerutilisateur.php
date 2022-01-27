<?php 

	include("php/bdd.php");

	$sqlQueryAffiche = 'SELECT id, Pseudo, Admin FROM utilisateur WHERE Admin = 0 ORDER BY Pseudo';
	$recipesStatementAffiche = $pdo->prepare($sqlQueryAffiche);
	$recipesStatementAffiche->execute();
	$users = $recipesStatementAffiche->fetchAll();

	if(isset($_POST['formdeleteuser']) AND isset($_POST['datadelet'])){
	
		$data = $_POST['datadelet'];
		$sqlQueryEfface = 'DELETE FROM utilisateur WHERE id="'.$data.'"';
		$recipesStatementEfface = $pdo->prepare($sqlQueryEfface);
		$recipesStatementEfface->execute();
		
		if ($recipesStatementEfface) {

			header("Location: supprimerutilisateur.php");
		}
		else {
			$erreur = "Erreur dans la base de données !";
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

	<div class="container">
		<div class="contact-form">
			
			<div class="main">
					
				<p>Supprimer utilisateur</p>
				<table id="table">
				<tr>
					<th>ID</th>
					<th>PSEUDO</th>
					<th>STATUT</th>
				</tr>
				<?php
				
					foreach ($users as $recipe) {
				?>	
					<form action="" method="post">
						<tr>
							<td><?php echo $recipe->id;?></td>
							<td><?php echo $recipe->Pseudo;?></td>
							<td><?php echo $recipe->Admin;?></td>

							<td><input type="hidden" name="datadelet" value="<?php echo $recipe->id; ?>">
								<button type="submit" name="formdeleteuser">Supprimer le compte</button>
							</td>
						</tr>
					</form>
				<?php } ?>
				</table>	
			</div>

			<?php
				if(isset($erreur)) {
					echo '<font color="red">'.$erreur."</font>";
			}
			?>
		</div>
	</div>
	<div class="lien">
		<p><a href="ajouterutilisateur.php">Ajouter un utilisateur</a></p>
		<p><a href="promouvoirutilisateur.php">Promouvoir un utilisateur</a></p>
		<p><a href="retrogradationadmin.php">Demande de rétrogradation d'un admin</a></p>
	</div>


</body>
</html>
