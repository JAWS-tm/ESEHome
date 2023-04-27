<?php

/*
	Author: MORIN HUGO
*/


    require 'inc/header.php';
	require 'inc/db.php';

	// Recherche dans la bdd les utilisateurs non admin
	$sqlQueryAffiche = 'SELECT id, pseudo, admin FROM users WHERE admin = 0 ORDER BY pseudo';
	$recipesStatementAffiche = $pdo->prepare($sqlQueryAffiche);
	$recipesStatementAffiche->execute();
	$users = $recipesStatementAffiche->fetchAll();

	if(isset($_POST['formdeleteuser']) AND isset($_POST['datadelet'])){
	
		$data = $_POST['datadelet'];
		// Supprime les utilisateurs dans la bdd
		$sqlQueryEfface = 'DELETE FROM users WHERE id="'.$data.'"';
		$recipesStatementEfface = $pdo->prepare($sqlQueryEfface);
		$recipesStatementEfface->execute() or exit(print_r($recipesStatementEfface->errorInfo()));
		
		// redirige vers la même page si l'admin veux supprimer un autre utilisateur
		header("Location: supprimerutilisateur.php");

	}
?>

<link rel="stylesheet" href="css/inscription.css"/>
</head>
<body>

	<h1>ADMIN</h1>
	<div class="container contadm">
		<div class="formadm">
			
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
							<td><?php echo $recipe->pseudo;?></td>
							<td><?php echo $recipe->admin;?></td>

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
		<p><a href="gestionutilisateur.php">Gestion des groupes utilisateur</a></p>
		
	</div>


<?php require 'inc/footer.php';?>