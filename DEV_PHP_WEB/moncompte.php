<?php 

/*
	Author: MORIN HUGO
*/


    require 'inc/header.php';
	require 'inc/db.php';
	
	// Récupération du groupe auquel l'utilisateur est associé
	$sqlnomgrp = "SELECT name FROM groups as GR
				  INNER JOIN users_groups as GU ON GU.id_group = GR.id 
				  INNER JOIN users as UT ON UT.id = GU.id_user
				  WHERE UT.id = ".$_SESSION['auth']->id;
	$reqmoncompte = $pdo->prepare($sqlnomgrp);
    $reqmoncompte->execute() or exit(print_r($reqmoncompte->errorInfo()));
    // Compte le nombre de résultat de $reqmoncompte
    $count = $reqmoncompte->rowCount();

   

?>

	<!-- Information du compte -->
	<div class="container contadm">
		<div class="formadm">
			<div class="main">
				<h2>Espace mon compte</h2>
				<p>Nom d'utilisateur : <?php echo $_SESSION['auth']->pseudo;?></p>
				<!-- <p>Numero d'identifiant : <?php echo $_SESSION['auth']->id;?></p> -->
				
				<?php 
				if($_SESSION['auth']->admin == 1) { ?>
					<p> Appartient au groupe : TOUT LES GROUPES </p><?php 
				} 
				else { 
					if ($count == 0 && $_SESSION['auth']->admin == 0) {?>
						<p> Appartient au groupe : PAS DE GROUPE ASSOS</p><?php
					}
					elseif ($count != 0) {
						$result = $reqmoncompte->fetchAll(PDO::FETCH_ASSOC);?>
						<p> Appartient au groupe : <?php 
						foreach ($result as $key => $value) {
								echo $value['name'].' - ';
						}?></p><?php
						
					}
				}
				?>
					

			</div>    
		</div>
	</div>

<?php require 'inc/footer.php';?>