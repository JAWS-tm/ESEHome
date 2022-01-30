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
    echo $result->date_creation;
    echo $result->state;
    echo $result->valeur;
    echo $result->nom;
    echo $result->nom_groupe;
    echo $result->modifiable;

?>