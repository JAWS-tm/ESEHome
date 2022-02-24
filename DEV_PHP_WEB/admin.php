<!-- Author: Laura TRACZYK and Hugo MORIN-->

<?php session_start();
    require 'inc/header.php';
?>
    <div class="container contadm">
    		<div class="formadm">
    			<div class="main">


    				<h2>Espace Administrateur de <?php echo $_SESSION['auth']->Pseudo;?></h2>
    				<p>Numero d'identifiant : <?php echo $_SESSION['auth']->id;?></p>
    				
                    <a class="link" href="ajouterutilisateur.php">Ajouter un utilisateur</a><br>
                    <a class="link" href="supprimerutilisateur.php">Supprimer un utilisateur</a><br>
                    <a class="link" href="promouvoirutilisateur.php">Promouvoir un utilisateur</a><br>
                    <a class="link" href="gestionutilisateur.php">Gestion d'un utilisateur</a><br>
                    <a class="link" href="messages.php">Boite aux lettres</a><br>
                    <a class="link" href="messages_admin.php">Messagerie</a><br>
                
                	
    
    			</div>    
    		</div>
    </div>  		
<?php require 'inc/footer.php';?>