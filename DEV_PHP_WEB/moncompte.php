<?php session_start();

    require 'inc/header.php';
	require 'inc/db.php';
	
	$sqlnomgrp = "SELECT nom_groupe FROM groupe as GR
				  INNER JOIN groupe_utilisateur as GU ON GU.id_groupe = GR.id 
				  INNER JOIN utilisateur as UT ON UT.id = GU.id_utilisateur
				  WHERE UT.id = ".$_SESSION['auth']->id;
	$reqmoncompte = $pdo->prepare($sqlnomgrp);
    $reqmoncompte->execute() or exit(print_r($reqmoncompte->errorInfo()));
    $count = $reqmoncompte->rowCount();

    if ($_SESSION['auth']->Admin == 1) {
    	$result = (object) [
    		'nom_groupe' => 1
		];
    }
    else if ($_SESSION['auth']->Admin == 0) {
    	if ($count != 0) {
    	 $result = $reqmoncompte->fetch();
   		}
   		else{
   			$result = (object) [
    			'nom_groupe' => 0
			];
   		}
    }

?>


	<div class="container contadm">
		<div class="formadm">
			<div class="main">
				<h2>Espace mon compte de <?php echo $_SESSION['auth']->Pseudo;?></h2>
				<p>Numero d'identifiant : <?php echo $_SESSION['auth']->id;?></p>
				
				<?php if($result->nom_groupe == 0) {?>
					<p> Appartient au groupe : PAS DE GROUPE ASSOS</p>
				<?php } elseif ($result->nom_groupe == 1) { ?>
					<p> Appartient au groupe : TOUT LES GROUPES</p>
				
				<?php } else{ ?>
					<p> Appartient au groupe : <?php echo $result->nom_groupe;?></p>
                <?php } ?>
			</div>    
		</div>
	</div>

<?php require 'inc/footer.php';?>