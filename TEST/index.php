<?php 
	session_start();
	include("php/bdd.php");
	

	if(isset($_SESSION['id']) AND isset($_SESSION['admin'])){
		if ($_SESSION['admin'] === 0) {
			
			$sqladm = "SELECT id_objet,nom_groupe, nom_type
						FROM utilisateur as US
						INNER JOIN groupe_utilisateur as GU ON GU.id_utilisateur = US.id
						INNER JOIN groupe as GR ON GR.id = GU.id_groupe
						INNER JOIN objet_groupe as OG ON OG.id_groupe = GR.id
						INNER JOIN objet as OB ON OB.id = OG.id_objet
						INNER JOIN type as TY ON TY.id = OB.type_id

						WHERE US.id =".$_SESSION['id'];

		}
		else{
			$sqladm = "SELECT id_objet, nom_groupe, nom_type FROM objet as OB
                        INNER JOIN type as TY ON TY.id = OB.type_id
                        INNER JOIN objet_groupe as OG ON OG.id_objet = OB.id
                        INNER JOIN groupe as GR ON GR.id = OG.id_groupe";
		}

		$reqadm = $pdo->prepare($sqladm);
		$reqadm->execute();

		$result = $reqadm->fetchAll(PDO::FETCH_ASSOC);

		
			


	}
	



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


	<?php 
	if(isset($_SESSION['id']) AND isset($_SESSION['admin'])){
		foreach($result as $value) {
		    echo "Identifiant de l'objet : ".$value['id_objet'];
		    echo "( ".$value['nom_groupe']." : ".$value['nom_type']." )";
		 	
		 	echo '<a href="ficheobjet.php?id_objet="'.$value['id_objet'].'>CLIQUER ICI</a>';
		    echo "<br />";
		
		}
	}
	?>
	<div></div>

	
	<footer>footer</footer>
</body>
</html>