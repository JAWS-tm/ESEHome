<!-- Author: Raimbault PL  -->
 
<?php

	
  require 'inc/header.php';
  require 'inc/db.php';
    
	date_default_timezone_set('UTC');
	$id = $_GET['param'];
	$Date = date("Y-m-d H:i:s") ; 
	
	if($id >= 10){
	    $dest = "DDDDDD$id";
	}else{
	    $dest = "DDDDDD0$id";
	} 

	// print_r($_POST);
	
	// On v�rifie si l'objet est bien connect� 
	// solution bancale
	$req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ?');
	$req->execute([$dest]);
	$result = $req->fetchAll(PDO::FETCH_ASSOC);
	if($result){
	    $connect = 1;
	}else{
	    $connect = 0;
	}
	
	
	switch ($id){
	    
	    case 1:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE" ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = " $donn�e";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	       break;
	    
	    case 2:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE" ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = " $donn�e";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	       break;
	    
	    case 3:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE" ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = "La consomation est actuellement de $donn�e";
	                }   
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 4:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE" ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = "La luminosite est actuellement de $donn�e";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        break;
	        
	    case 5:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE" ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = "La temperature est actuellement de $donn�e";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 6:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE" ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = "La temperature est actuellement de $donn�e";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 7:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE" ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = "Le volet est actuellement de $donn�e";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 8:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE" ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = "L'alarme est actuellement de $donn�e";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 9:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE"');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = "Le detecteur d'incendie est actuellement $donn�e";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 10:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE"');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = "Le ventilateur est actuellement $donn�e";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        break;
	        
	    case 11:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE"');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        $state = "La papi est actuellement 0";
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = "Le papi est actuellement $donn�e";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        break;
	        
	    case 12:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE" ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = "Le niveau de la cuve est de $donn�e";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 13:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE" ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = "La qualite de l'air est de $donn�e";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 14:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE"');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = "Le slider LCD est $donn�e";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 15:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE" ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = "L'�cran tactile est $donn�e";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 16:
	        $req = $pdo->prepare('SELECT * FROM messages WHERE emetteur = ? AND type_messages = "PARAMETER_WRITE" ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['messages'];
	                    $state = "Il est $donn�e";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;  
	}
	


	$sqlinfo ="SELECT nom_type, date_creation, state, nom, nom_groupe
     FROM objet as OB
     INNER JOIN objet_groupe as OG ON OG.id_objet = OB.id
     INNER JOIN groupe as GR ON GR.id = OG.id_groupe
     INNER JOIN type as TY ON TY.id = OB.type_id
     INNER JOIN parametres as PA
     WHERE OB.id = '$id'";
    
	//faut recup l'id de l'objet � la place du 1
	
	$reqinfo = $pdo->prepare($sqlinfo);
    $reqinfo->execute();

    $result = $reqinfo->fetch();

    
if(!empty($_POST)){
    $errors = array();
    require_once 'inc/db.php';
        
    if(empty($_POST['Emetteur']) || $_POST['Emetteur'] != "EEEEEE00"){
        $errors['Emetteur'] = "L'emetteur n'est pas valide";
    }
        
    if(empty($_POST['Destinataire']) ){
        $errors['Destinataire'] = "Pas de detinataire pour cette demande";
    }
    
    if(empty($_POST['Type_messages']) ){
        $errors['Type_messages'] = "Pas de Type_messages_id pour cette demande";
    }
    
    if(empty($_POST['Paramettre_id']) ){
        $errors['Paramettre_id'] = "Pas de Paramettre_id pour cette demande";
    }
    
    if(empty($_POST['messages']) ){
        $errors['messages'] = "Pas de messages pour cette demande";
    }
    
    if(empty($_POST['Date']) ){
        $errors['Date'] = "La date n'est pas valide";
    }
    
    if(empty($_POST['Permanent'])){
        $errors['Permanent'] = "Un param�tre n'est pas valide";
    }
        
    if(empty($errors)){
       $req = $pdo->prepare("INSERT INTO messages SET destinataire = ?, emetteur = ?, parametre_id = ?, message = ?, date = ?, permanent = ?, type_messages = ?");
       $destinataire = htmlspecialchars($_POST['Destinataire']);
       $emetteur = htmlspecialchars($_POST['Emetteur']);
       $Paramettre_id = htmlspecialchars($_POST['Paramettre_id']);
       $Type_messages = htmlspecialchars($_POST['Type_messages']);
       $message = htmlspecialchars($_POST['messages']);
       $Date = htmlspecialchars($_POST['Date']);
       $Permanent =  htmlspecialchars($_POST['Permanent']);
       $req->execute([$destinataire, $emetteur, $Paramettre_id,$message,$Date,$Permanent,$Type_messages]);
            
      // echo " messages envoye ";
   }
        
}
?>

<link rel="stylesheet" href="css/objet.css">
<link rel="stylesheet" href="css/ficheobjet.css">
<link rel="stylesheet" href="css/colors.css">
 <div class="object-sections">
    <h2 class="section-title">Objet</h2>
	<form method="post" class="object-card">
		<div class="object-actions">
			<img class="object-img" src="img/chambre.jpg">
			<div class="actions">
				
				<!-- <div class="action-card-container">
					<span class="card-title">Thermostat</span>
					<div class="level-card action-card">
						<i class="fa-solid fa-angle-up up-down-arrow" id="upValue"></i>
						<div><input class="value value-input" id="value" type="text" min="10" max="30" value="25">
						<span class="value">°C</span></div>
						<i class="fa-solid fa-angle-down up-down-arrow" id="downValue"></i>

					</div>
				</div> -->
				<div class="action-card-container two-actions-card">
					<div>
						<span class="card-title">Température</span>
						<div class="display-card action-card">
							<i class="fa-solid fa-temperature-high"></i>
							<span class="value">25°C</span>
						</div>
					</div>
					<div>
						<span class="card-title">Humidité</span>
						<div class="display-card action-card">
							<i class="fa-solid fa-droplet"></i>
							<span class="value">42%</span>
						</div>
					</div>
				</div>
				<div class="action-card-container">
					<span class="card-title">Eclairage</span>
					<label for="checkbox" class="switch-card action-card">
						<input type="checkbox" id="checkbox">
						<div class="power-button">
							<i class="fa-solid fa-power-off"></i>
						</div>
					</label>
				</div>
				<div class="action-card-container">
					<span class="card-title">Luminosité</span>
					<div class="brightness-card action-card">
						<div class="brightness">
							<input id="brightnessRange" type="range" min="0" max="100" step="1" value=""  onchange="showVal(this.value)">
						</div>
						<img src="img/brightness.png" alt="">
					</div>
				</div>
				<div class="action-card-container">
					<span class="card-title">Chauffage</span>
					<div class="selector-card action-card">
						<input type="radio" id="mode1" name="radMod">
						<label class="item-selector" for="mode1">
							<span>Confort</span>
						</label>
						<input type="radio" id="mode2" name="radMod">
						<label class="item-selector" for="mode2">
							<span>Eco</span>
						</label>
						<input type="radio" id="mode3" name="radMod" checked="checked">
						<label class="item-selector" for="mode3">
							<span>Désactivé</span>
						</label>	
					</div>
				</div>
				<!-- <div class="action-card-container">
					<span class="card-title">Couleur</span>
					<div class="color-card action-card">
						<div id="color-border">
							<input type="color" value="#e66465">
						</div>
					</div>
				</div> -->

			</div>
		</div>
		<div class="object-status-container">
			<p>Gestion de l'objet</p> 
			<p class="object-status">Objet déconnecté</p>
		</div>
		<input type="submit" class="button" value="Valider">

	</form>
	<h2 class="section-title">Messages reçus</h2>
	<div class="object-card object-received-msg">
		<table class="table">
			<tr class="table-first-collum">
				<th>Emetteur</th>
				<th>Type</th>
				<th>Données</th>
				<th>Permanent</th>
				<th>Date</th>
			</tr>
			<tr class="table-collums">
				<td>DDDDDD00</td>
				<td>PARAMETER_IS</td>
				<td>0x550201</td>
				<td>TRUE</td>
				<td>5 janvier 2023 10:52</td>
			</tr>
			<tr class="table-collums">
				<td>DDDDDD00</td>
				<td>PARAMETER_IS</td>
				<td>0x550201</td>
				<td>TRUE</td>
				<td>5 janvier 2023 10:52</td>
			</tr>
			<tr class="table-collums">
				<td>DDDDDD00</td>
				<td>PARAMETER_IS</td>
				<td>0x550201</td>
				<td>TRUE</td>
				<td>5 janvier 2023 10:52</td>
			</tr>
			<tr class="table-collums">
				<td>DDDDDD00</td>
				<td>PARAMETER_IS</td>
				<td>0x550201</td>
				<td>TRUE</td>
				<td>5 janvier 2023 10:52</td>
			</tr>
		</table>
	</div>
	<h2 class="section-title">Messages envoyés</h2>
	<div class="object-card object-sent-msg">
	<table class="table">
			<tr class="table-first-collum">
				<th>Emetteur</th>
				<th>Type</th>
				<th>Données</th>
				<th>Permanent</th>
				<th>Date</th>
			</tr>
			<tr class="table-collums">
				<td>DDDDDD00</td>
				<td>PARAMETER_IS</td>
				<td>0x550201</td>
				<td>TRUE</td>
				<td>5 janvier 2023 10:52</td>
			</tr>
			<tr class="table-collums">
				<td>DDDDDD00</td>
				<td>PARAMETER_IS</td>
				<td>0x550201</td>
				<td>TRUE</td>
				<td>5 janvier 2023 10:52</td>
			</tr>
			<tr class="table-collums">
				<td>DDDDDD00</td>
				<td>PARAMETER_IS</td>
				<td>0x550201</td>
				<td>TRUE</td>
				<td>5 janvier 2023 10:52</td>
			</tr>
			<tr class="table-collums">
				<td>DDDDDD00</td>
				<td>PARAMETER_IS</td>
				<td>0x550201</td>
				<td>TRUE</td>
				<td>5 janvier 2023 10:52</td>
			</tr>
		</table>
	</div>
</div>

<script type="text/javascript" src="js/message.js"></script>
<script type="text/javascript" src="js/object.js"></script>
<?php require 'inc/footer.php';?>