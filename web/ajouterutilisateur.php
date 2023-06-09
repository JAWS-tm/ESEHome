<?php

/*
	Author: MORIN HUGO
*/


 	require 'inc/header.php';
	require 'inc/db.php';

	if(isset($_POST['formajoutuser'])) {
	    $pseudoajout = htmlspecialchars($_POST['usernameajout']);
	    $mdpajout = $_POST['passwordajout'];
	    $mdpajout2 = $_POST['passwordajout_confirm'];
	    
	    if(!empty($_POST['usernameajout']) AND !empty($_POST['passwordajout']) AND !empty($_POST['passwordajout_confirm'])) {
	        $pseudoajoutlength = strlen($pseudoajout);
	        if($pseudoajoutlength <= 255) {
	        	// Récupération des informations de l'utilisateur
	            $reqpseudoajout = $pdo->prepare("SELECT * FROM users WHERE pseudo = ?");
	            $reqpseudoajout->execute(array($pseudoajout));
	            $pseudoajoutexist = $reqpseudoajout->rowCount();
	            if ($pseudoajoutexist == 0) {
	                if ($mdpajout == $mdpajout2) {
	                    
	                    // hash du mot de passe
	                    $mdpajout=password_hash($_POST['passwordajout'], PASSWORD_DEFAULT);
	                    
	                    // Insert dans la bdd
	                    $reqinsertajout = $pdo->prepare("INSERT INTO users SET pseudo = ?, password = ?, admin = 0");
	                    $reqinsertajout->execute(array($pseudoajout, $mdpajout));

	                    
                   		header("Location: ajouterutilisateur.php");
	                    	                    
	                }
	                else {
	                    $erreur = "Vos mots de passes ne correspondent pas !";
	                }
	            }
	            else {
	                $erreur = "Votre pseudo existe déjà !";
	            }
	        }
	        else {
	            $erreur = "Votre pseudo ne doit pas dépasser 255 caractères !";
	        }
	    }
	    else {
	        $erreur = "Tous les champs doivent être complétés !";
	    }
	}
?>



<link rel="stylesheet" href="css/inscription.css"/>
</head>
<body>

	<h1>ADMIN</h1>
	<div class="container contadm">
		<div class="formadm">
			
			<div class="main">
					
				<p>Ajout d'un utilisateur</p>
					<form action="" method="POST">
					<input type="text" name="usernameajout" placeholder="Nom d'utilisateur" class="champ" require/>
					<input type="password" name="passwordajout" placeholder="Mot De Passe" class="champ" require/>
					<input type="password" name="passwordajout_confirm" placeholder="Confirmez le mot de passe" class="champ" require/>


					
					<button type="submit" name="formajoutuser" class="btn">Ajouter</button>
					<?php
					if(isset($erreur)) {
						echo '<br">'.$erreur;
					}
					?>
				</form>
			  </div>
		</div>
	</div>
	<br>
	<div class="lien">

		<p><a href="supprimerutilisateur.php">Supprimer un utilisateur</a></p>
		<p><a href="promouvoirutilisateur.php">Promouvoir un utilisateur</a></p>
		<p><a href="gestionutilisateur.php">Gestion des groupes utilisateur</a></p>

	</div>



<?php require 'inc/footer.php';?>