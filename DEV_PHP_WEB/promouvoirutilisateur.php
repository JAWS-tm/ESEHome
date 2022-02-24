<?php

/*
	Author: MORIN HUGO
*/

	require 'inc/header.php';
	require 'inc/db.php';

	// Recherche dans la bdd les utilisateurs non admin
	$sqlQueryAffiche = 'SELECT id, Pseudo, Admin FROM utilisateur WHERE Admin = 0 ORDER BY Pseudo';
	$recipesStatementAffiche = $pdo->prepare($sqlQueryAffiche);
	$recipesStatementAffiche->execute();
	$users = $recipesStatementAffiche->fetchAll();

	
	if(isset($_POST['formpromouser']) AND isset($_POST['datapromo'])){
		
		$data = $_POST['datapromo'];
		// L'utilisateur sélectionné sera up en admin
		$sqlQueryPromot = 'UPDATE utilisateur SET Admin = 1 WHERE id="'.$data.'"';
		$recipesStatementPromot = $pdo->prepare($sqlQueryPromot);
		$recipesStatementPromot->execute() or exit(print_r($recipesStatementPromot->errorInfo()));
		
		// redirige vers la même page si l'admin veux promouvoir un autre utilisateur
		header("Location: promouvoirutilisateur.php");
		
	}

?>
<link rel="stylesheet" href="css/inscription.css"/>
</head>
<body>
	<h1>ADMIN</h1>
	<div class="container contadm">
		<div class="formadm">
			
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