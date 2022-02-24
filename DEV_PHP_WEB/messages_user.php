<?php 
    session_start();
    include("inc/db.php");
  
    $msg = $pdo->query('SELECT * FROM messages_admin ORDER BY id DESC');
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
						        <th class="pseudo">Pseudo</th>
						        <th class="text">Texte</th>
						        <th class="date_m">Date</th>
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
					            <td><?php echo $value['pseudo'];?></td>
					            <td><?php echo $value['text'];?></td>
					            <td><?php echo $value['date_m'];?></td>
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