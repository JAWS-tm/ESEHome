<!-- Author: Laura TRACZYK and Hugo MORIN-->

<?php session_start();
    require 'inc/header.php';
?>
    <div class="container contadm">
    		<div class="formadm">
    			<div class="main">


    				<h2>Espace Administrateur de <?php echo $_SESSION['auth']->Pseudo;?></h2>
    				<p>Numero d'identifiant : <?php echo $_SESSION['auth']->id;?></p>
                    <div class="square_button_container">
    				    <a class="square_link" href="ressource.php">
                            <img src="img/objects_list.png" alt="Ressources">
                            <span>Ressources</span>
                        </a>

                        <a class="square_link" href="ajouterutilisateur.php">
                            <img src="img/user_add.png" alt="Ajouter un utilisateur">
                            <span>Ajouter un utilisateur</span>
                        
                        </a>
                        <a class="square_link" href="supprimerutilisateur.php">
                            <img src="img/user_remove.png" alt="Supprimer un utilisateur">
                            <span>Supprimer un utilisateur</span>
                        </a>

                        <a class="square_link" href="promouvoirutilisateur.php">
                            <img src="img/user_rights.png" alt="Gerer les droits">
                            <span>Gerer les droits</span>
                        </a>


                        <a class="square_link" href="gestionutilisateur.php">
                           <img src="img/manage_groups.png" alt="Gestion des groupes">
                           <span>Gestion des groupes</span>
                        </a>
                        <a class="square_link" href="messages.php">
                          <img src="img/msg_objects.png" alt="Messages objets">
                          <span>Messages objets</span>
                        </a>

                        <a class="square_link" href="messages_user.php">
                         <img src="img/msg_user.png" alt="Messages utilisateurs">
                         <span>Messages utilisateurs</span>
                        </a>
                
                    </div>
    
    			</div>    
    		</div>
    </div>  		
<?php require 'inc/footer.php';?>