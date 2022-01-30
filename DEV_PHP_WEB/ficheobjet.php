<?php
	
	session_start();

	include("inc/db.php");

	$sql ="SELECT nom_type, date_creation, state, valeur, nom, nom_groupe, modifiable
     FROM objet as OB
     INNER JOIN objet_groupe as OG ON OG.id_objet = OB.id
     INNER JOIN groupe as GR ON GR.id = OG.id_groupe
     INNER JOIN type as TY ON TY.id = OB.type_id
     INNER JOIN parametres as PA 
     INNER JOIN valeur as VA ON VA.objet_id = OB.id AND VA.parametre_id =PA.id
     WHERE OB.id =1";

	$req = $pdo->prepare($sql);
    $req->execute();

    $result = $req->fetch();

    echo $result->nom_type;
    echo " / " .$result->date_creation;
    echo " / " .$result->state;
    echo " / " .$result->valeur;
    echo " / " .$result->nom;
    echo " / " .$result->nom_groupe;
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

?>