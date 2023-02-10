<!-- Author: Laura TRACZYK -->

<?php session_start();
    require 'inc/header.php';
    require 'inc/db.php';
    
    //récupère les infos des objets
    $sqladm = "SELECT id_object, OB.name object_name, TY.name as type_name, GR.name as group_name, creation_date, state FROM object as OB
		INNER JOIN object_type as TY ON TY.id = OB.type_id
		INNER JOIN group_objects as OG ON OG.id_object = OB.id
		INNER JOIN groups as GR ON GR.id = OG.id_group";
    
    $reqadm = $pdo->prepare($sqladm);
    $reqadm->execute();
    $result = $reqadm->fetchAll(PDO::FETCH_ASSOC);
    
    //récupère les infos des utilisateurs
    $user = "SELECT * FROM users ORDER BY id ASC";
    $utilisateur = $pdo->prepare($user);
    $utilisateur->execute();
    $users = $utilisateur->fetchAll(PDO::FETCH_ASSOC);
    
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
                                <th class="pseudo">Nom</th>
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
				        		<td><?php echo $value['id_object'];?></td>
                                <td><?php echo $value['object_name'];?></td>
					            <td><?php echo $value['group_name'];?></td>
					            <td><?php echo $value['type_name'];?></td>
					            <td><?php echo $value['creation_date'];?></td>
					            <td><?php echo $value['state'];?></td>    
				        	</tr>
				     	</tbody>
					   <?php } ?>
			    	</table>
				</div>
			</div>
		
		<h1>Utilisateurs</h1>
		<!-- Tableau -->

			<div class="tableau">
				<div class="table_header">
				    <table>
				        <thead>
				            <tr>
						        <th class="id">Id</th>
						        <th class="pseudo">Pseudo</th>
						        <th class="text">Statut (1=admin / 0=user)</th>
				        	</tr>
				        </thead>
				    </table>
				</div>
			    <div class="table_body">
			    	<table>
				    	<?php 
				    	foreach($users as $key => $value2) //Affichage tableau ligne par ligne
				    	{?>
				        <tbody>
				        	<tr>
				        		<td><?php echo $value2['id'];?></td>
					            <td><?php echo $value2['pseudo'];?></td>
					            <td><?php echo $value2['admin'];?></td>
				        	</tr>
				     	</tbody>
					   <?php } ?>
			    	</table>
				</div>
			</div>
		
		<?php require 'inc/footer.php';?>