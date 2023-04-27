<!-- Author: Laura TRACZYK -->

<?php 
    session_start();
    include("inc/db.php");
  
    $msg = $pdo->query("SELECT MSG.id, MSG.data, MSG.date, MSG.permanent, OBr.name as recipient, OBt.name as transmitter, OBr.physical_id as recipient_id, OBt.physical_id as transmitter_id, PARAM.name as param_name, PARAM.id as param_id, MT.name as msg_type FROM message as MSG 
    INNER JOIN object as OBr ON OBr.id = MSG.recipient 
    INNER JOIN object as OBt ON OBt.id = MSG.transmitter
    INNER JOIN parameters as PARAM ON PARAM.id = MSG.parameter_id    
    INNER JOIN message_type as MT ON MT.id = MSG.type_message    
    WHERE MSG.history = 0
    ORDER BY id DESC");
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
					            <td><?= $value['id'] ?></td>
					            <td><?= $value['recipient']." (#".$value['recipient_id'].")" ?></td>
					            <td><?= $value['transmitter']." (#".$value['transmitter_id'].")" ?></td>
					            <td><?= $value['param_name']." (#".$value['param_id'].")" ?></td>
					            <td><?= $value['data'] ?></td>
					            <td><?= $value['date'] ?></td>
					            <td><?= $value['permanent'] ?></td>
					            <td><?= $value['msg_type'] ?></td>
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