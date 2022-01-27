<?php
include("php/bdd.php");

if(isset($_POST['forminscription'])) {
    $pseudo = htmlspecialchars($_POST['username']);
    $mdp = $_POST['password'];
    $mdp2 = $_POST['password_confirm'];
    $choix = $_POST['choixgroupeobjet'];
    if(!empty($_POST['username']) AND !empty($_POST['password']) AND !empty($_POST['password_confirm']) AND !empty($_POST['choixgroupeobjet']) ) {
        $pseudolength = strlen($pseudo);
        if($pseudolength <= 255) {
            $reqpseudo = $pdo->prepare("SELECT * FROM utilisateur WHERE Pseudo = ?");
            $reqpseudo->execute(array($pseudo));
            $pseudoexist = $reqpseudo->rowCount();
            if ($pseudoexist == 0) {
                if ($mdp == $mdp2) {
                    
                    $mdp=password_hash($_POST['password'], PASSWORD_DEFAULT);
                    $admin = 0;
                    
                    
                    $reqinsert = $pdo->prepare("INSERT INTO utilisateur SET Pseudo = ?, MotDePasse = ?, Admin = ?");
                    $reqinsert->execute(array($pseudo, $mdp, $admin));
                    
                    $lastinsert = $pdo->lastInsertId();

                    $reqinsertgrp = $pdo->prepare("INSERT INTO groupe_utilisateur SET id_utilisateur = ?, id_groupe = ?, edition = ?");
                    $reqinsertgrp->execute(array($lastinsert, $choix, false));
                    

                    header("Location: connexion.php");
                    
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

<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>ESEHOME</title>
</head>
<body>

    <?php include('html/header.php'); ?>

	<h1>S'inscrire</h1>
	
	<div class="container">
		<div class="contact-form">

			<div class="main">

				<h2>Inscription</h2>
				<form action="" method="POST">

					<input type="text" name="username" placeholder="Nom d'utilisateur" class="champ" require/>
					<input type="password" name="password" placeholder="Mot De Passe" class="champ" require/>
					<input type="password" name="password_confirm" placeholder="Confirmez votre mot de passe" class="champ" require/>
					
                    <select name="choixgroupeobjet" class="groupeobjet">

                        <option value="1">Groupe1</option>
                        <option value="2">Groupe2</option>
                        <option value="3">Groupe3</option>


                    </select>

					<button type="submit" name="forminscription" class="btn">M'inscrire</button>
                    <?php
                    if(isset($erreur)) {
                        echo '<font color="red">'.$erreur."</font>";
                    }
                    ?>
				</form>
                Déjà inscrit? <a href="connexion.php">Connectez-vous ici</a>



			</div>    
		</div>
	</div>



</body>
</html>