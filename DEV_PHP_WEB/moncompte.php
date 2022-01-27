<?php

	session_start();
	

	if (!isset($_SESSION['id'])) {

		header("Location: index.php");
	}

	include("php/bdd.php");
	
	$sqlnomgrp = "SELECT nom_groupe FROM groupe as GR
				  INNER JOIN groupe_utilisateur as GU ON GU.id_groupe = GR.id 
				  INNER JOIN utilisateur as UT ON UT.id = GU.id_utilisateur
				  WHERE UT.id = ".$_SESSION['id'];
	$reqmoncompte = $pdo->prepare($sqlnomgrp);
    $reqmoncompte->execute();
    $result = $reqmoncompte->fetch();

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

				<h2>Espace mon compte de <?php echo $_SESSION['pseudo'];?></h2>
				<p> Numero d'identifiant : <?php echo $_SESSION['id'];?></p>
				<p> Appartient au groupe : <?php echo $result->nom_groupe;?></p>
                
				<?php if ($_SESSION['admin'] == 1) { ?>
					<p>Ajouter un utilisateur : <a href="ajouterutilisateur.php">ici</a></p>
					<p>Supprimer un utilisateur : <a href="supprimerutilisateur">ici</a></p>
					<p>Promouvoir un utilisateur : <a href="promouvoirutilisateur">ici</a></p>
					<p>Demander la rétrogradation d'un admin : <a href="">ici</a></p>
				<?php } ?>


			</div>    
		</div>
	</div>

</body>
</html>