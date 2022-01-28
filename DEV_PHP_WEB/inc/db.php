<?php
    try
    {
        // On se connecte � MySQL
        $pdo = new PDO('mysql:host=localhost; dbname=bdd_synthese; charset=utf8', 'root', '');
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        $pdo->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_OBJ);
    }
    catch(Exception $e)
    {
        // En cas d'erreur, on affiche un message et on arr�te tout
        die('Erreur : '.$e->getMessage());
    }

?>