<?php
include("php/bdd.php");

if(isset($_POST['formajoutuser'])) {
    $pseudoajout = htmlspecialchars($_POST['usernameajout']);
    $mdpajout = $_POST['passwordajout'];
    $mdpajout2 = $_POST['passwordajout_confirm'];
    $choix = $_POST['choixgroupeobjet'];
    if(!empty($_POST['usernameajout']) AND !empty($_POST['passwordajout']) AND !empty($_POST['passwordajout_confirm']) AND !empty($_POST['choixgroupeobjet']) ) {
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

                    $lastinsertajout = $pdo->lastInsertId();

                    $reqinsertgrpajout = $pdo->prepare("INSERT INTO groupe_utilisateur SET id_utilisateur = ?, id_groupe = ?, edition = ?");
                    $reqinsertgrpajout->execute(array($lastinsertajout, $choix, false));

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
					
				<p>Ajout d'un utilisateur</p>
					<form action="" method="POST">
					<input type="text" name="usernameajout" placeholder="Nom d'utilisateur" class="champ" require/>
					<input type="password" name="passwordajout" placeholder="Mot De Passe" class="champ" require/>
					<input type="password" name="passwordajout_confirm" placeholder="Confirmez le mot de passe" class="champ" require/>


					<select name="choixgroupeobjet" class="groupeobjet">

                        <option value="1">Groupe1</option>
                        <option value="2">Groupe2</option>
                        <option value="3">Groupe3</option>

                    </select>
					
					<button type="submit" name="formajoutuser" class="btn">Ajouter</button>
					<?php
					if(isset($erreur)) {
						echo '<font color="red">'.$erreur."</font>";
					}
					?>
				</form>
			  </div>
		</div>
	</div>

	<div class="lien">
		<p><a href="supprimerutilisateur.php">Supprimer un utilisateur</a></p>
		<p><a href="promouvoirutilisateur.php">Promouvoir un utilisateur</a></p>
		<p><a href="retrogradationadmin.php">Demande de rétrogradation d'un admin</a></p>
	</div>


</body>
</html>
