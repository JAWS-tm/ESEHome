<?php
    try
    {
        // On se connecte � MySQL
        $pdo = new PDO('mysql:host=172.24.0.71; dbname=PHP; charset=utf8', 'python','python');
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        $pdo->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_OBJ);
    }
    catch(Exception $e)
    {
        // En cas d'erreur, on affiche un message et on arr�te tout
        die('Erreur : '.$e->getMessage());
    }

?>