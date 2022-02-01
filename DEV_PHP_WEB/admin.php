<?php session_start();
require 'inc/header.php';?>



    <div class="container">
    		<div class="contact-form">
    			<div class="main">
    				<h2>Espace Administrateur de <?php echo $_SESSION['auth']->Pseudo;?></h2>
    				<p>Numero d'identifiant : <?php echo $_SESSION['auth']->id;?></p>
    				
                	<a href="ajouterutilisateur.php">Ajouter un utilisateur</a>
                	<a href="supprimerutilisateur">Supprimer un utilisateur</a>
                	<a href="promouvoirutilisateur">Promouvoir un utilisateur</a>
    
    			</div>    
    		</div>
    </div>  		
    <?php require 'inc/footer.php';?>