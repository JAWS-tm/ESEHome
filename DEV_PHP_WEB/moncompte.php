<?php 

/*
	Author: MORIN HUGO
*/

    require 'inc/header.php';
	require 'inc/db.php';
	
	// Récupération du groupe auquel l'utilisateur est associé
	$sqlnomgrp = "SELECT nom_groupe FROM groupe as GR
				  INNER JOIN groupe_utilisateur as GU ON GU.id_groupe = GR.id 
				  INNER JOIN utilisateur as UT ON UT.id = GU.id_utilisateur
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
				<h2>Espace mon compte de <?php echo $_SESSION['auth']->Pseudo;?></h2>
				<p>Numero d'identifiant : <?php echo $_SESSION['auth']->id;?></p>
				
				<?php 
				if($_SESSION['auth']->Admin == 1) { ?>
					<p> Appartient au groupe : TOUT LES GROUPES </p><?php 
				} 
				else { 
					if ($count == 0 && $_SESSION['auth']->Admin == 0) {?>
						<p> Appartient au groupe : PAS DE GROUPE ASSOS</p><?php
					}
					elseif ($count != 0) {
						$result = $reqmoncompte->fetchAll(PDO::FETCH_ASSOC);?>
						<p> Appartient au groupe : <?php 
						foreach ($result as $key => $value) {
								echo $value['nom_groupe'].' - ';
						}?></p><?php
						
					}
				}
				?>
					

			</div>    
		</div>
	</div>

<?php require 'inc/footer.php';?>