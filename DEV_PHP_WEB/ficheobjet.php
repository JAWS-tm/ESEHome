<?php
    require 'inc/header.php';
    include("inc/db.php");
    
	date_default_timezone_set('UTC');
	$id = $_GET['param'];
	$Date = date("Y-m-d H:i:s") ; 
	
	if($id >= 10){
	    $dest = "DDDDDD$id";
	}else{
	    $dest = "DDDDDD0$id";
	}
	
	// On férifie si l'objet est bien connecté 
	// solution bancale
	$req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ?');
	$req->execute([$dest]);
	$result = $req->fetchAll(PDO::FETCH_ASSOC);
	if($result){
	    $connect = 1;
	}else{
	    $connect = 0;
	}
	
	
	
	
	
	switch ($id){
	    
	    case 1:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = " $donnée";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	       break;
	    
	    case 2:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = " $donnée";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	       break;
	    
	    case 3:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = "La consomation est actuellement de $donnée";
	                }   
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 4:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = "La luminosite est actuellement de $donnée";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        break;
	        
	    case 5:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = "La temperature est actuellement de $donnée";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 6:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = "La temperature est actuellement de $donnée";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 7:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = "Le volet est actuellement de $donnée";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 8:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = "L'alarme est actuellement de $donnée";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 9:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = "Le detecteur d'incendie est actuellement $donnée";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 10:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = "Le ventilateur est actuellement $donnée";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        break;
	        
	    case 11:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        $state = "La papi est actuellement 0";
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = "Le papi est actuellement $donnée";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        break;
	        
	    case 12:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = "Le niveau de la cuve est de $donnée";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 13:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = "La qualite de l'air est de $donnée";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 14:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = "Le slider LCD est $donnée";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 15:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = "L'écran tactile est $donnée";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;
	        
	    case 16:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donnée = $value['message'];
	                    $state = "Il est $donnée";
	                }
	            }
	        }else{
	            $state = "Pas de donnees";
	        }
	        
	        break;  
	}
	


	$sqlinfo ="SELECT nom_type, date_creation, state, valeur, nom, nom_groupe, modifiable
     FROM objet as OB
     INNER JOIN objet_groupe as OG ON OG.id_objet = OB.id
     INNER JOIN groupe as GR ON GR.id = OG.id_groupe
     INNER JOIN type as TY ON TY.id = OB.type_id
     INNER JOIN parametres as PA 
     INNER JOIN valeur as VA ON VA.objet_id = OB.id AND VA.parametre_id =PA.id
     WHERE OB.id = '$id'";
    
	//faut recup l'id de l'objet à la place du 1
	
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
    
    if(empty($_POST['Type_message_id']) ){
        $errors['Type_message_id'] = "Pas de Type_message_id pour cette demande";
    }
    
    if(empty($_POST['Paramettre_id']) ){
        $errors['Paramettre_id'] = "Pas de Paramettre_id pour cette demande";
    }
    
    if(empty($_POST['Message']) ){
        $errors['Message'] = "Pas de Message pour cette demande";
    }
    
    if(empty($_POST['Date']) ){
        $errors['Date'] = "La date n'est pas valide";
    }
    
    if(empty($_POST['Permanent'])){
        $errors['Permanent'] = "Un paramètre n'est pas valide";
    }
        
    if(empty($errors)){
       $req = $pdo->prepare("INSERT INTO message SET destinataire = ?, emetteur = ?, parametre_id = ?, message = ?, date = ?, permanent = ?, type_message_id = ?");
       $destinataire = htmlspecialchars($_POST['Destinataire']);
       $emetteur = htmlspecialchars($_POST['Emetteur']);
       $Paramettre_id = htmlspecialchars($_POST['Paramettre_id']);
       $Type_message_id = htmlspecialchars($_POST['Type_message_id']);
       $Message = htmlspecialchars($_POST['Message']);
       $Date = htmlspecialchars($_POST['Date']);
       $Permanent =  htmlspecialchars($_POST['Permanent']);
       $req->execute([$destinataire, $emetteur, $Paramettre_id,$Message,$Date,$Permanent,$Type_message_id]);
            
       echo " Message envoye ";
   }
        
}
?>

<link rel="stylesheet" href="css/objet.css">
<link rel="stylesheet" href="css/ficheobjet.css">
 <div class="user_ban">
    <h1>Objet</h1>
  </div>
<div class="fiche">
  <div class="artic">
      <article class="card">
          <div class="card_thumb">
            <img src="img/chambre.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory"><?php echo $result->nom_type;?></div>
              <h2 class="card_title">Gérer <?php echo $result->nom_type;?></h2>
              <div class="card_element">
                <?php if($connect == 1){ ?>
              			<p class="connect">Objet connecte</p>
               <?php }else{ ?>
                   <p class="disconnect">Objet deconnecte</p>
                <?php }?>
                 <p class="etat"><?php echo $state; ?></p>
              	<form action="" method="POST">
              		<input type="hidden"  name="Emetteur" value="EEEEEE00" require/>
                    <input type="hidden"  name="Destinataire" value="<?php echo $dest; ?>" require/>
                    <input type="hidden"  name="Type_message_id" value="30" require/>
                    <input type="hidden"  name="Paramettre_id" value="01" require/>
                    <input type="hidden"  name="Message" value="02" require/>
                    <input type="hidden"  name="Permanent" value="1" require/>
                    <input type="hidden"  name="Date" value="<?php echo $Date; ?>" require/>
              		<button type="submit" class="action">Action</button>
              	</form>
               	<form action="" method="POST">
              		<input type="hidden"  name="Emetteur" value="EEEEEE00" require/>
                    <input type="hidden"  name="Destinataire" value="<?php echo $dest; ?>" require/>
                    <input type="hidden"  name="Type_message_id" value="30" require/>
                    <input type="hidden"  name="Paramettre_id" value="01" require/>
                    <input type="hidden"  name="Message" value="02" require/>
                    <input type="hidden"  name="Permanent" value="1" require/>
                    <input type="hidden"  name="Date" value="<?php echo $Date; ?>" require/>
              		<button type="submit" class="demande">Demande modif</button>
              	</form>
                 
              </div>
          </div>
      </article>
	</div>
      <div class = "message">  
          <div class = "reçu" id="recu" style="display: block;">
          		<p> Dernier message reçu : <?php
                  	                                  $req = $pdo->prepare('SELECT * FROM message WHERE destinataire = ?');
                                                      $req->execute([$dest]);
                                                      $result = $req->fetchAll(PDO::FETCH_ASSOC);
                                                      if($result){
                                                          foreach ($result as $value){
                                                              if ($value === end($result))
                                                                  echo '<li>Message ('.$value['id'].') Destinataire : '.$value['destinataire'].'/ Date : '.$value['date'].'/ type de message : '.$value['type_message_id'].'/ Permanent : '.$value['permanent'].'</li>'; 
                                                          }
                                                      }else{
                                                          echo 'Pas de message recu';
                                                      }?></p>
          </div>
          <div class = "envoyé" id="envoye" style="display: block;">
                <p> Dernier message envoyé : <?php
              	                                  $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ?');
                                                  $req->execute([$dest]);
                                                  $result = $req->fetchAll(PDO::FETCH_ASSOC);
                                                  if($result){
                                                      foreach ($result as $value){
                                                          if ($value === end($result))
                                                              echo '<li>Message ('.$value['id'].') Destinataire : '.$value['destinataire'].'/ Date : '.$value['date'].'/ type de message : '.$value['type_message_id'].'/ Permanent : '.$value['permanent'].'</li>'; 
                                                      }
                                                  }else{
                                                      echo 'Pas de message envoye';
                                                  }?></p>
          </div>
          <button class="voir" id="btn"  style="display: block;">Voir tous les messages</button>
          <button class="voir" id="Fermer"  style="display: none;">Reduire</button>
          <ul class="envoyé" id="envoyetout" style="display: none;">
          <?php 
          $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ?');
          $req->execute([$dest]);
          $result = $req->fetchAll(PDO::FETCH_ASSOC);
          if($result){
              echo '<li>Messages envoyé</li>';
              foreach ($result as $value){
                echo '<li>Message ('.$value['id'].') Destinataire : '.$value['destinataire'].'/ Date : '.$value['date'].'/ type de message : '.$value['type_message_id'].'/ Permanent : '.$value['permanent'].'</li>'; 
              }
          }else{
              echo '<li>Pas de message envoye</li>';
          }?>    
          </ul>
          
          <ul class="reçu" id="recutout" style="display: none;">
          <?php 
          $req = $pdo->prepare('SELECT * FROM message WHERE destinataire = ?');
          $req->execute([$dest]);
          $result = $req->fetchAll(PDO::FETCH_ASSOC);
          if($result){
              echo '<li>Messages recu</li>';
              foreach ($result as $value){
                echo '<li>Message ('.$value['id'].') Destinataire : '.$value['destinataire'].'/ Date : '.$value['date'].'/ type de message : '.$value['type_message_id'].'/ Permanent : '.$value['permanent'].'</li>'; 
              }
          }else{
              echo '<li>Pas de message recu</li>';
          }?>    
          </ul>
      </div>
  </div>
    <script type="text/javascript" src="js/message.js"></script>
<?php require 'inc/footer.php';?>