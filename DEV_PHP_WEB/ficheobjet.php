<?php
    include("inc/db.php");
	session_start();

	date_default_timezone_set('UTC');
	$id = $_GET['param'];
	$Date = date("Y-m-d H:i:s") ; 
	
	if($id >= 10){
	    $dest = "DDDDDD$id";
	    echo $dest;
	}else{
	    $dest = "DDDDDD0$id";
	    echo $dest;
	}
	
	// On f�rifie si l'objet est bien connect� 
	// solution bancale
	$req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ?');
	$req->execute([$dest]);
	$result = $req->fetchAll(PDO::FETCH_ASSOC);
	if($result){
	    $connect = 1;
	    echo $connect;
	}else{
	    $connect = 0;
	    echo $connect;
	}
	
	
	
	
	
	switch ($id){
	    
	    case 1:
            //TODO changer le parametre en fonvtion de l'objet tipe de message ext.... 	
            // Pour l'instant envoie d'un ping 
	       break;
	    
	    case 2:
	        //TODO changer le parametre en fonvtion de l'objet tipe de message ext.... 	
	        // Pour l'instant envoie d'un ping 
	       break;
	    
	    case 3:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['message'];
	                    $state = "La consomation est actuellement de $donn�e";
	                }   
	            }
	        }
	        
	        break;
	        
	    case 4:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['message'];
	                    $state = "La luminosit�e est actuellement de $donn�e";
	                }
	            }
	        }
	        break;
	        
	    case 5:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['message'];
	                    $state = "La temp�rature est actuellement de $donn�e";
	                }
	            }
	        }
	        
	        break;
	        
	    case 6:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['message'];
	                    $state = "La temp�rature est actuellement de $donn�e";
	                }
	            }
	        }
	        
	        break;
	        
	    case 7:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['message'];
	                    $state = "Le volet est actuellement de $donn�e";
	                }
	            }
	        }
	        
	        break;
	        
	    case 8:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['message'];
	                    $state = "L'alarme est actuellement de $donn�e";
	                }
	            }
	        }
	        
	        break;
	        
	    case 9:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['message'];
	                    $state = "Le detecteur d'incendie est actuellement $donn�e";
	                }
	            }
	        }
	        
	        break;
	        
	    case 10:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['message'];
	                    $state = "La ventilateur est actuellement $donn�e";
	                }
	            }
	        }
	        break;
	        
	    case 11:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['message'];
	                    $state = "La papi est actuellement $donn�e";
	                }
	            }
	        }
	        break;
	        
	    case 12:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['message'];
	                    $state = "Le niveau de la cuve est de $donn�e";
	                }
	            }
	        }
	        
	        break;
	        
	    case 13:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['message'];
	                    $state = "La qualit� de l'aire est de $donn�e";
	                }
	            }
	        }
	        
	        break;
	        
	    case 14:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['message'];
	                    $state = "La slider LCD est $donn�e";
	                }
	            }
	        }
	        
	        break;
	        
	    case 15:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['message'];
	                    $state = "L'�crant tactile est $donn�e";
	                }
	            }
	        }
	        
	        break;
	        
	    case 16:
	        $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ? AND type_message_id = 42 ');
	        $req->execute([$dest]);
	        $result = $req->fetchAll(PDO::FETCH_ASSOC);
	        if($result){
	            foreach ($result as $value){
	                if ($value === end($result)){
	                    $donn�e = $value['message'];
	                    $state = "Il est $donn�e";
	                }
	            }
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
    
	//faut recup l'id de l'objet � la place du 1
	
	$reqinfo = $pdo->prepare($sqlinfo);
    $reqinfo->execute();

    $result = $reqinfo->fetch();

    echo $result->nom_groupe;
    echo " / " .$result->nom;
    echo " / " .$result->date_creation;
    echo " / " .$result->nom_type;
    echo " / " .$result->state;
    echo " / " .$result->valeur;
    echo " / " .$result->modifiable;
    
    
    
    /* 
     	Via une plateforme hébergée par le serveur à laquelle il se connecte par login+mdp, l’utilisateur doté
        de droits ‘admin’ peut accéder à un ensemble de fonctionnalités.
    - Liste des objets associés à la station + visualisation de l’état de ces objets (connecté / date et heure du dernier message reçu / niveau de batterie, autres paramètres spécifiques…)

        -Chaque objet est présenté avec son nom choisi par l’utilisateur (nom dont l’objet n’a d’ailleurs pas connaissance).
        - Accès aux paramètres de chaque objet, et à leurs états (modification en attente, état validé, date de la dernière modification, …)
        - Accès aux événements reçus
        - Accès aux actions disponibles
        - Accès à la liste de règles (lecture, modification, ajout…)
  
        - Attention, une règle peut concerner plusieurs objets
            ▪   Exemple : le capteur de luminosité xx active la lumière nocturne yy.
        
        
        - Accès à la boîte aux lettres des messages pour chaque objet
        
        Selon les contextes, les données pourront être affichées sous forme de listes à plusieurs colonnes, dont on peut faire varier l’ordre de tri et dont on peut filtrer le contenu.   
     */
      
    $d =1;
    $a =4;

    if(isset($_POST['formmessage'])) {
        if (!empty($_POST['message'])) {
           
           $msg = "Utilisateur Numero " .$d . " / "; // $_SESSION['auth']->id
           $msg .= "Objet Numero ".$a." / "; // RECUP DANS UNE SESSION PAS ENCORE FAIT
           $msg .= $_POST['message'];
           
           $sqlmsg ="INSERT INTO message (message, permanent, type_message_id, date) VALUES (:msg, false, 1, NOW() );";
            
            try {
                $reqmsg = $pdo->prepare($sqlmsg);
                $reqmsg->bindParam(':msg', $msg, PDO::PARAM_STR);
                $reqmsg->execute();

                if ($reqmsg !== false) {
                    
                    header("Location ficheobjet.php");
                }
            } 
            catch (PDOException $e) {
                echo $e->getMessage();
            }                   
        }     
    }
    
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
        $errors['Permanent'] = "Un param�tre n'est pas valide";
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
            
       echo " Message envoy� ";
   }
        
}
?>

<div>
    <p>Envoyer un message pour modifier certains paramètres d’un objet ou de plusieurs objets</p>
    <form action="" method="POST">
                            
        <input type="text" name="message" placeholder="" class="champ" require/>
        <button type="submit" name="formmessage" class="btn">Envoyer</button>
    </form>

</div>

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
              <h2 class="card_title">G�rer <?php echo $result->nom_type;?></h2>
              <div class="card_element">
                <?php if($connect == 1){
                            echo 'Objet connect�';
                }else{
                    echo 'Objet non connect�';
                }
                ?>
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
              		<button class="demande">Demande modif</button>
              	</form>
                 
              </div>
          </div>
      </article>
	</div>
      <div class = "message">  
          <div class = "re�u" id="recu" style="display: block;">
          		<p> Dernier message re�u : <?php
                  	                                  $req = $pdo->prepare('SELECT * FROM message WHERE destinataire = ?');
                                                      $req->execute([$dest]);
                                                      $result = $req->fetchAll(PDO::FETCH_ASSOC);
                                                      if($result){
                                                          foreach ($result as $value){
                                                              if ($value === end($result))
                                                                  echo '<li>Message ('.$value['id'].') Destinataire : '.$value['destinataire'].'/ Date : '.$value['date'].'/ type de message : '.$value['type_message_id'].'/ Permanent : '.$value['permanent'].'</li>'; 
                                                          }
                                                      }else{
                                                          echo 'Pas de message re�u';
                                                      }?></p>
          </div>
          <div class = "envoy�" id="envoye" style="display: block;">
                <p> Dernier message envoy� : <?php
              	                                  $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ?');
                                                  $req->execute([$dest]);
                                                  $result = $req->fetchAll(PDO::FETCH_ASSOC);
                                                  if($result){
                                                      foreach ($result as $value){
                                                          if ($value === end($result))
                                                              echo '<li>Message ('.$value['id'].') Destinataire : '.$value['destinataire'].'/ Date : '.$value['date'].'/ type de message : '.$value['type_message_id'].'/ Permanent : '.$value['permanent'].'</li>'; 
                                                      }
                                                  }else{
                                                      echo 'Pas de message envoy�';
                                                  }?></p>
          </div>
          <button class="voir" id="btn">Voire tous les messages</button>
          <ul class="envoy�" id="envoyetout" style="display: none;">
          <?php 
          $req = $pdo->prepare('SELECT * FROM message WHERE emetteur = ?');
          $req->execute([$dest]);
          $result = $req->fetchAll(PDO::FETCH_ASSOC);
          if($result){
              echo '<li>Messages envoy�</li>';
              foreach ($result as $value){
                echo '<li>Message ('.$value['id'].') Destinataire : '.$value['destinataire'].'/ Date : '.$value['date'].'/ type de message : '.$value['type_message_id'].'/ Permanent : '.$value['permanent'].'</li>'; 
              }
          }else{
              echo '<li>Pas de message envoy�</li>';
          }?>    
          </ul>
          
          <ul class="re�u" id="recutout" style="display: none;">
          <?php 
          $req = $pdo->prepare('SELECT * FROM message WHERE destinataire = ?');
          $req->execute([$dest]);
          $result = $req->fetchAll(PDO::FETCH_ASSOC);
          if($result){
              echo '<li>Messages re�u</li>';
              foreach ($result as $value){
                echo '<li>Message ('.$value['id'].') Destinataire : '.$value['destinataire'].'/ Date : '.$value['date'].'/ type de message : '.$value['type_message_id'].'/ Permanent : '.$value['permanent'].'</li>'; 
              }
          }else{
              echo '<li>Pas de message re�u</li>';
          }?>    
          </ul>
      </div>
  </div>
    <script type="text/javascript" src="js/message.js"></script>
<?php /*require 'inc/footer.php';*/?>