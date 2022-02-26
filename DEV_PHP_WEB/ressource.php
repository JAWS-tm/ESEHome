<!-- Author: Laura TRACZYK -->

<?php session_start();
    require 'inc/header.php';
    
    
    //rcuprer les objets propres  chaque groupe et leurs paramtres
    $sqladm = "SELECT id_objet,nom_groupe, nom_type
        FROM utilisateur as US
        INNER JOIN groupe_utilisateur as GU ON GU.id_utilisateur = US.id
        INNER JOIN groupe as GR ON GR.id = GU.id_groupe
        INNER JOIN objet_groupe as OG ON OG.id_groupe = GR.id
        INNER JOIN objet as OB ON OB.id = OG.id_objet
        INNER JOIN type as TY ON TY.id = OB.type_id
        
        WHERE US.id =".$_SESSION['auth']->id;
    
    $sqladm = "SELECT id_objet, nom_groupe, nom_type FROM objet as OB
                    INNER JOIN type as TY ON TY.id = OB.type_id
                    INNER JOIN objet_groupe as OG ON OG.id_objet = OB.id
                    INNER JOIN groupe as GR ON GR.id = OG.id_groupe";
    
    $reqadm = $pdo->prepare($sqladm);
    $reqadm->execute();
    $result = $reqadm->fetchAll(PDO::FETCH_ASSOC);
    
    //rcuprer les groupes d'objets auxquels l'utilisateur a accs
    $sqlgrpuser ="SELECT id_groupe FROM utilisateur AS UT
        INNER JOIN groupe_utilisateur AS GU ON GU.id_utilisateur = UT.id
        WHERE UT.id =".$_SESSION['auth']->id;
    $req = $pdo->prepare($sqlgrpuser);
    $req->execute();
    $resultats = $req->fetchAll(PDO::FETCH_ASSOC);
    //print_r($resultats); //retourne bien toutes les groupes associs  l'utilisateur
    //$groupe = array_column($resultats, 'id_groupe'); //met dans un tableau simple
    //$groupe = [1]; test
    //print_r($groupe); //[0]=>4, [1]=>1; // c'est bien ce qu'on veut
    
?>
<link rel="stylesheet" href="css/messages.css"/>
<link rel="stylesheet" type="text/css" href="css/styles.css">

    <header class="header">
		<a class="retour" href="admin.php">Retour</a>
	</header>
	
	<h1>Objets</h1>
		<!-- Tableau -->

			<div class="tableau">
				<div class="table_header">
				    <table>
				        <thead>
				            <tr>
						        <th class="id">Id</th>
						        <th class="pseudo">Groupe</th>
						        <th class="text">Type</th>
				        	</tr>
				        </thead>
				    </table>
				</div>
			    <div class="table_body">
			    	<table>
				    	<?php 
				    	foreach($result as $key => $value) //Affichage tableau ligne par ligne
				    	{?>
				        <tbody>
				        	<tr>
				        		<td><?php echo $value['id_objet'];?></td>
					            <td><?php echo $value['nom_groupe'];?></td>
					            <td><?php echo $value['nom_type'];?></td>       
				        	</tr>
				     	</tbody>
				        <?php
				        if(!$value){?>
				            <td><?php echo "aucun objet";?></td>
				        <?php }
				        	
					    }

					    ?>
			    	</table>
				</div>
			</div>
		</div>
		
		<?php require 'inc/footer.php';?>