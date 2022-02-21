<?php session_start();
require 'inc/header.php';?>



    <div class="container">
    		<div class="contact-form">
    			<div class="main">
    				<h2>Espace Administrateur de <?php echo $_SESSION['auth']->Pseudo;?></h2>
    				<p>Numero d'identifiant : <?php echo $_SESSION['auth']->id;?></p>
    				
                    <div id="user">
                        <a class="link" href="ajouterutilisateur.php">Ajouter un utilisateur</a><br>
                        <a class="link" href="supprimerutilisateur">Supprimer un utilisateur</a><br>
                        <a class="link" href="promouvoirutilisateur">Promouvoir un utilisateur</a><br>
                    </div>
                	
    
    			</div>    
    		</div>
    </div>  		
    <?php require 'inc/footer.php';?>