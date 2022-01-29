<?php


 	require 'inc/header.php';
	include("inc/db.php");

	if(isset($_POST['formajoutuser'])) {
	    $pseudoajout = htmlspecialchars($_POST['usernameajout']);
	    $mdpajout = $_POST['passwordajout'];
	    $mdpajout2 = $_POST['passwordajout_confirm'];
	    
	    if(!empty($_POST['usernameajout']) AND !empty($_POST['passwordajout']) AND !empty($_POST['passwordajout_confirm'])) {
	        $pseudoajoutlength = strlen($pseudoajout);
	        if($pseudoajoutlength <= 255) {
	            $reqpseudoajout = $pdo->prepare("SELECT * FROM utilisateur WHERE Pseudo = ?");
	            $reqpseudoajout->execute(array($pseudoajout));
	            $pseudoajoutexist = $reqpseudoajout->rowCount();
	            if ($pseudoajoutexist == 0) {
	                if ($mdpajout == $mdpajout2) {
	                    
	                    $mdpajout=password_hash($_POST['passwordajout'], PASSWORD_DEFAULT);
	                    $admin = 0;
	                    
	                    $reqinsertajout = $pdo->prepare("INSERT INTO utilisateur SET Pseudo = ?, MotDePasse = ?, Admin = ?");
	                    $reqinsertajout->execute(array($pseudoajout, $mdpajout, $admin));

	                    
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


	<div class="container">
		<div class="contact-form">
			
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
		
		<p><a href="promouvoirutilisateur.php">Promouvoir un utilisateur</a></p>
		<p><a href="gestionutilisateur.php">Gestion des groupes utilisateur</a></p>
		<p><a href="supprimerutilisateur.php">Supprimer un utilisateur</a></p>

	</div>


<?php require 'inc/footer.php';?>