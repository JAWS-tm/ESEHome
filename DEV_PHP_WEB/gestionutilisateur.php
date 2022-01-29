<?php 

    require 'inc/header.php';

	include("inc/db.php");

	$sqlQueryAffiche = 'SELECT id, Pseudo FROM utilisateur WHERE Admin = 0 ORDER BY Pseudo';
	$recipesStatementAffiche = $pdo->prepare($sqlQueryAffiche);
	$recipesStatementAffiche->execute();
	$users = $recipesStatementAffiche->fetchAll();

	if(isset($_POST['formgrpuser']) AND isset($_POST['datagrp']) AND !empty($_POST['choixgroupeobjet'])){
	
		$data = $_POST['datagrp'];
		// POUR EVITER LES DOUBLON
		$sqlGrp = 'SELECT * FROM groupe_utilisateur WHERE id_utilisateur ='.$data;
		$reqGrp = $pdo->prepare($sqlGrp);
		$reqGrp->execute();
		if ($reqGrp->rowCount() !=0) {
		 	$sqlGrp2 = 'INSERT INTO groupe_utilisateur SET id_utilisateur = ?, id_groupe = ?, edition = ?';
		 	$reqGrp2 = $pdo->prepare($sqlGrp2);
			$reqGrp2->execute(array($data, $_POST['choixgroupeobjet'], false));
		 }
		 else {
		 	// PROBLEME DE CONCATENATION DE LA REQEUTE SQL
		 	$sqlGrp3 = "UPDATE groupe_utilisateur SET id_groupe ='".$_POST['choixgroupeobjet'].'"' WHERE id_utilisateur ="".$data;
		 	$reqGrp3 = $pdo->prepare($sqlGrp3);
			$reqGrp3->execute();
		 }



		header("Location: gestionutilisateur.php");
	}


?>

<link rel="stylesheet" href="css/inscription.css"/>
</head>
<body>

	
	<div class="container">
		<div class="contact-form">
			
			<div class="main">
					
				<p>Gestion des groupes utilisateur</p>
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
						

							<td>

								<select name="choixgroupeobjet" class="groupeobjet">
									<option value="">Choisir un groupe</option>
			                        <option value="1">Chambre</option>
			                        <option value="2">Cuisine</option>
			                        <option value="3">Salon</option>
			                        <option value="4">Exterieur</option>

			                    </select>
							</td>


							<td><input type="hidden" name="datagrp" value="<?php echo $recipe->id; ?>">
								<button type="submit" name="formgrpuser">Valider le groupe</button>
							</td>
						</tr>
					</form>
				<?php } ?>
				</table>	
			</div>

		</div>
	</div>
	<div class="lien">
		<p><a href="ajouterutilisateur.php">Ajouter un utilisateur</a></p>
		<p><a href="promouvoirutilisateur.php">Promouvoir un utilisateur</a></p>

		<p><a href="supprimerutilisateur.php">Supprimer un utilisateur</a></p>

	</div>


<?php require 'inc/footer.php';?>