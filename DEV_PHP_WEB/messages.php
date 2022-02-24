<?php 
    session_start();
    include("inc/db.php");
  
    $msg = $pdo->query('SELECT * FROM messages ORDER BY id DESC');
    $messages = $msg->fetchAll(PDO::FETCH_ASSOC);
		
?>
<link rel="stylesheet" href="css/messages.css"/>
<link rel="stylesheet" type="text/css" href="css/styles.css">
	
	<header class="header">
		<a class="retour" href="admin.php">Retour</a>
	</header>
	
	<h1>Boite aux lettres</h1>
		<!-- Tableau -->

			<div class="tableau">
				<div class="table_header">
				    <table>
				        <thead>
				            <tr>
						        <th class="id">Id</th>
						        <th class="destinataire">Destinataire</th>
						        <th class="emetteur">Emetteur</th>
						        <th class="param_id">Parametres Id</th>
						        <th class="message">Message</th>
						        <th class="date">Date</th>
						        <th class="permanent">Permanent</th>
						        <th class="type_message_id">Type message id</th>
				        	</tr>
				        </thead>
				    </table>
				</div>
			    <div class="table_body">
			    	<table>
				    	<?php 
				    	foreach ($messages as $key => $value) //Affichage tableau ligne par ligne
				    	{?>
				        <tbody>
				        	<tr>
					            <td><?php echo $value['id'];?></td>
					            <td><?php echo $value['destinataire'];?></td>
					            <td><?php echo $value['emetteur'];?></td>
					            <td><?php echo $value['parametre_id'];?></td>
					            <td><?php echo $value['message'];?></td>
					            <td><?php echo $value['date'];?></td>
					            <td><?php echo $value['permanent'];?></td>
					            <td><?php echo $value['type_messages_id'];?></td>
				        	</tr>
				     	</tbody>
				        <?php
				        	
					    }

					    ?>
			    	</table>
				</div>
			</div>
		</div>
		
		<?php require 'inc/footer.php';?>