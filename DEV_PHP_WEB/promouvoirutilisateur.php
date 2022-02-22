<?php


	require 'inc/header.php';
	require 'inc/db.php';

	$sqlQueryAffiche = 'SELECT id, Pseudo, Admin FROM utilisateur WHERE Admin = 0 ORDER BY Pseudo';
	$recipesStatementAffiche = $pdo->prepare($sqlQueryAffiche);
	$recipesStatementAffiche->execute();
	$users = $recipesStatementAffiche->fetchAll();

	// Promotion du compte
	if(isset($_POST['formpromouser']) AND isset($_POST['datapromo'])){
		
		$data = $_POST['datapromo'];
		$sqlQueryPromot = 'UPDATE utilisateur SET Admin = 1 WHERE id="'.$data.'"';
		$recipesStatementPromot = $pdo->prepare($sqlQueryPromot);
		$recipesStatementPromot->execute() or exit(print_r($recipesStatementPromot->errorInfo()));
		
		header("Location: promouvoirutilisateur.php");
		
	}

?>

</head>
<body>
	
	<div class="container">
		<div class="contact-form">
			
			<div class="main">
					
				<p>Promouvoir utilisateur</p>
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

							<td><input type="hidden" name="datapromo" value="<?php echo $recipe->id; ?>">
								<button type="submit" name="formpromouser">Promouvoir le compte</button>
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
		<p><a href="gestionutilisateur.php">Gestion des groupes utilisateur</a></p>
		<p><a href="supprimerutilisateur.php">Supprimer un utilisateur</a></p>

	</div>

<?php require 'inc/footer.php';?>