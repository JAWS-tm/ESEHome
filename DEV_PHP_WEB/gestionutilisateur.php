<?php

/*
	Author: MORIN HUGO
*/


    require 'inc/header.php';
	require 'inc/db.php';

	// Affichage de tous les utilisateurs
	$sqlQueryAffiche = 'SELECT id, pseudo FROM users WHERE admin = 0 ORDER BY pseudo';
	$recipesStatementAffiche = $pdo->prepare($sqlQueryAffiche);
	$recipesStatementAffiche->execute() or exit(print_r($recipesStatementAffiche->errorInfo()));
	$users = $recipesStatementAffiche->fetchAll();



	// Si le formulaire est complet et valide (Ajouter un groupe)
	if(isset($_POST['formgrpuser']) AND isset($_POST['datagrp']) AND !empty($_POST['choixgroupeobjet'])){
	
		$data = $_POST['datagrp']; // ID de l'utilisateur
		$cgo = $_POST['choixgroupeobjet']; // Groupe

		$sqlverifdoublon = "SELECT COUNT(*) FROM users_groups WHERE id_user =:verifdata AND id_group = :verifcgo";
		$reqverifInsert = $pdo->prepare($sqlverifdoublon);
	 	$reqverifInsert->execute();
		$verifresult = $reqverifInsert->fetchAll(PDO::FETCH_ASSOC);
		$isverified = array_column($verifresult, 'COUNT(*)');
	 	if ($isverified == [0]) {
	 	 	// Insert du groupe dans la bdd 
			$sqlGrpInsert = "INSERT INTO users_groups (id_user, id_group) VALUES (?, ?)";
		 	$reqGrpInsert = $pdo->prepare($sqlGrpInsert);
		 	$reqGrpInsert->execute();
	 	 } 

		header("Location: gestionutilisateur.php");
	}

	// Si le formulaire est complet et valide (Enlever un groupe)
	if(isset($_POST['formgrpusersupp']) AND isset($_POST['datagrpsupp']) AND !empty($_POST['choixgroupeobjet'])){
	
		$datasupp = $_POST['datagrpsupp']; // ID de l'utilisateur
		$cgo = $_POST['choixgroupeobjet']; // Groupe

		// Supprimer de la bdd 

		$sql = "DELETE FROM users_groups WHERE id_user = :datasupp AND id_group = :cgo";

	 	$reqGrpSuppr = $pdo->prepare($sql);
	 	$reqGrpSuppr->execute(array(':datasupp'=>$datasupp, ':cgo'=>$cgo)) or exit(print_r($reqGrpSuppr->errorInfo()));

	 	header("Location: gestionutilisateur.php");
	}



?>

<link rel="stylesheet" href="css/inscription.css"/>
</head>
<body>

	<h1>ADMIN</h1>
	<div class="container contadm">
		<div class="formadm">
			
			<div class="main">
					
				<p>Gestion des groupes utilisateur</p>
				<table id="table">
				<tr>
					<th>ID</th>
					<th>PSEUDO</th>
					<th>GROUPE ASSOCIE</th>
					<th>CHOIX GROUPE</th>
				</tr>
				<?php
				
					foreach ($users as $recipe) {

							$sqlgrpUtilisateur = 'SELECT name FROM groups AS GR
							INNER JOIN users_groups AS GU ON GU.id_group = GR.id
							INNER JOIN users AS UT ON UT.id = GU.id_user
							WHERE UT.id ='.$recipe->id;

							$recipesStatementgrpUtilisateur = $pdo->prepare($sqlgrpUtilisateur);
							$recipesStatementgrpUtilisateur->execute() or exit(print_r($recipesStatementgrpUtilisateur->errorInfo()));
							$groupes = $recipesStatementgrpUtilisateur->fetchAll();
						


				?>	
					<form action="#" method="post">
						<tr>
							<td><?php echo $recipe->id;?></td>
							<td><?php echo $recipe->pseudo;?></td>
							
							<td><?php foreach ($groupes as $groupesutlisateur) {
								
								echo $groupesutlisateur->name.' ';
								 
								
							}?></td>
							<td>

								<select name="choixgroupeobjet" class="groupeobjet">
									<option value="">Choisir un groupe</option>
			                        <option value="1">Chambre</option>
			                        <option value="2">Cuisine</option>
			                        <option value="3">Salon</option>
			                        <option value="4">Exterieur</option>

			                    </select >
							</td>


							<td><input type="hidden" name="datagrp" value="<?php echo $recipe->id; ?>">
								<button type="submit" name="formgrpuser" value="selectedValue">Valider le groupe</button>
							</td>
						
							<td><input type="hidden" name="datagrpsupp" value="<?php echo $recipe->id; ?>">
								<button type="submit" name="formgrpusersupp">Supprimer du groupe</button>
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