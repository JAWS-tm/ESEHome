<?php session_start();
if (isset($_SESSION['start']) && (time() - $_SESSION['start'] > 1800)) {
    session_unset();
    session_destroy();
    echo "Vous avez été inactif 30min, veuillez vous reconnecter";
}
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
                    <a class="link" href="messages_user.php">Messagerie</a><br>
                
                	
    
    			</div>    
    		</div>
    </div>  		
<?php require 'inc/footer.php';?>