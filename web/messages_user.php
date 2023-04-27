<?php 
    session_start();
    include("inc/db.php");

    $msg = $pdo->query('SELECT * FROM message_admin ORDER BY id DESC');
    $messages = $msg->fetchAll(PDO::FETCH_ASSOC);
	$usr = $pdo->query('SELECT id, Pseudo  FROM USERS');
    $users = $usr->fetchAll(PDO::FETCH_ASSOC);
	setlocale(LC_TIME, "fr_FR");
    if ($_SESSION['auth']->admin == 1){
		if (isset($_GET["accept"]) && isset($_GET["id_user"]) && isset($_GET["group"]) && isset($_GET["id"])){
			$accept = $_GET["accept"];
			$id = $_GET["id"];
			if ($accept){
				$id_user = $_GET["id_user"];
				$group = $_GET["group"];
				$sqlverifdoublon = "SELECT COUNT(*) FROM users_groups WHERE id_user =:verifdata AND id_group = :verifcgo";
				$reqverifInsert = $pdo->prepare($sqlverifdoublon);
				$reqverifInsert->execute(array(':verifdata'=>$id_user, ':verifcgo'=>$group));
				$verifresult = $reqverifInsert->fetchAll(PDO::FETCH_ASSOC);
				$isverified = array_column($verifresult, 'COUNT(*)');
				if ($isverified == [0]) {
					// Insert du groupe dans la bdd 
					$sqlGrpInsert = "INSERT INTO users_groups (id_user, id_group) VALUES (?, ?)";
					$reqGrpInsert = $pdo->prepare($sqlGrpInsert);
					$reqGrpInsert->execute([$id_user, $group]);
				}
				}
			$sqlDltMsg = "DELETE FROM message_admin  WHERE id =".$id;
			$sqlDltMsg = $pdo->prepare($sqlDltMsg);
			$sqlDltMsg->execute();
			header("Location: messages_user.php");
			}
		}
	
		
?>
<link rel="stylesheet" href="css/messages.css"/>
<link rel="stylesheet" type="text/css" href="css/styles.css">
	
	<header class="header">
		<a class="retour" href="admin.php">Retour</a>
		<script src="https://kit.fontawesome.com/d944b11724.js" crossorigin="anonymous"></script>
	</header>

	<h1>Boite aux lettres</h1>
		<!-- Tableau -->
		
			<div class="tableau">
				<div class="table_header">
				    <table>
				        <thead>
				            <tr>
						        <!-- <th class="id">Id</th> -->
						        <th class="pseudo">pseudo</th>
								<!-- <th class="text">Objet</th> -->
								<th class="text">Texte</th>
						        <th class="date_m">Date</th>
								<th ></th>
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
					            <!-- <td><?php echo $value['id'];?></td> -->
					            <td><?php echo $users[array_search($value['id_user'], array_column($users, 'id'))]['Pseudo'];?></td>
                                <!-- <td><?php echo $value['object'];?></td> -->
                                <td><?php echo $value['message'];?></td>
					            <td><?= strftime("%d %b %Y",strtotime($value['message_date'])) ?></td>
								<td>
									<form class="div-icon" action="" method = "get">
									<input type="hidden" name="id" value="<?=$value['id']?>">
										<input type="hidden" name="id_user" value="<?=$value['id_user']?>">
										<input type="hidden" name="group" value="<?=$value['object']?>">
										<button class="btn-icon" type="submit" name="accept" value="1">
										<i class="icon-check fa-solid fa-check"></i>
									</button>
									<button class="btn-icon" type="submit" name="accept" value="0">
										<i class="icon-trash fa-solid fa-trash"></i>
									</button>
									</form>
									
								</td>
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