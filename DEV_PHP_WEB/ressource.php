<!-- Author: Laura TRACZYK -->

<?php session_start();
    require 'inc/header.php';
    require 'inc/db.php';
    
      
    $sqladm = "SELECT id_objet, nom_groupe, nom_type, date_creation, state FROM objet as OB
		INNER JOIN type as TY ON TY.id = OB.type_id
		INNER JOIN objet_groupe as OG ON OG.id_objet = OB.id
		INNER JOIN groupe as GR ON GR.id = OG.id_groupe";
    
    $reqadm = $pdo->prepare($sqladm);
    $reqadm->execute();
    $result = $reqadm->fetchAll(PDO::FETCH_ASSOC);
    
  
    
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
						        <th class="text">Date de création</th>
						        <th class="text">Etat</th>
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
					            <td><?php echo $value['date_creation'];?></td>
					            <td><?php echo $value['state'];?></td>    
				        	</tr>
				     	</tbody>


					   <?php } ?>
			    	</table>
				</div>
			</div>
		</div>
		
		<?php require 'inc/footer.php';?>