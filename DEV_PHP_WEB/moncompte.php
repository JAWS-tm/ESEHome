<?php
	require 'inc/header.php';

	require_once 'inc/db.php';

	if (!isset($_SESSION['auth']->id)) {

		header("Location: index.php");
	}

	include("inc/db.php");
	
	$sqlnomgrp = "SELECT nom_groupe FROM groupe as GR
				  INNER JOIN groupe_utilisateur as GU ON GU.id_groupe = GR.id 
				  INNER JOIN utilisateur as UT ON UT.id = GU.id_utilisateur
				  WHERE UT.id = ".$_SESSION['auth']->id;
	$reqmoncompte = $pdo->prepare($sqlnomgrp);
    $reqmoncompte->execute();
    $result = $reqmoncompte->fetch();

    
  

?>

<link rel="stylesheet" href="css/inscription.css"/>
<body>

	<div class="container">
		<div class="contact-form">

			<div class="main">

				<h2>Espace mon compte de <?php echo $_SESSION['auth']->Pseudo;?></h2>
				<p> Numero d'identifiant : <?php echo $_SESSION['auth']->id;?></p>
				
				<?php if($result->nom_groupe == 0) {?>
					<p> Appartient au groupe : PAS DE GROUPE ASSOS</p>
				<?php } else{ ?>
					<p> Appartient au groupe : <?php echo $result->nom_groupe;?></p>
                <?php } ?>
				<?php if ($_SESSION['auth']->Admin == 1) { ?>
					<p>Ajouter un utilisateur : <a href="ajouterutilisateur.php">ici</a></p>
					<p>Supprimer un utilisateur : <a href="supprimerutilisateur">ici</a></p>
					<p>Promouvoir un utilisateur : <a href="promouvoirutilisateur">ici</a></p>
					
				<?php } ?>

				<a href="deconnexion.php">Deconnexion</a>
			</div>    
		</div>
	</div>

<?php require 'inc/footer.php';?>