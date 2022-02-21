<?php
	
	session_start();

	include("inc/db.php");

	$sqlinfo ="SELECT nom_type, date_creation, state, valeur, nom, nom_groupe, modifiable
     FROM objet as OB
     INNER JOIN objet_groupe as OG ON OG.id_objet = OB.id
     INNER JOIN groupe as GR ON GR.id = OG.id_groupe
     INNER JOIN type as TY ON TY.id = OB.type_id
     INNER JOIN parametres as PA 
     INNER JOIN valeur as VA ON VA.objet_id = OB.id AND VA.parametre_id =PA.id
     WHERE OB.id =1";
    
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
?>

<div>
    <p>Envoyer un message pour modifier certains paramètres d’un objet ou de plusieurs objets</p>
    <form action="" method="POST">
                            
        <input type="text" name="message" placeholder="" class="champ" require/>
        <button type="submit" name="formmessage" class="btn">Envoyer</button>
    </form>

</div>

<link rel="stylesheet" href="css/objet.css">
 <div class="user_ban">
    <h1>Objet</h1>
  </div>
  <div class="artic">
      <article class="card">
          <div class="card_thumb">
            <img src="img/chambre.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">objet</div>
              <h2 class="card_title">G�rer "objet"</h2>
              <div class="card_element">
                  <button class="action">Action</button>
                  <button class="demande">Demande modif</button>
              </div>
          </div>
      </article>  
  </div>
    
<?php /*require 'inc/footer.php';*/?>