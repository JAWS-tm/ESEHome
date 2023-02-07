<!-- Author: MORIN HUGO - Raimbault PL  -->

<?php
    $pdo = null;
    try
    {
        // On se connecte a MySQL
        $pdo = new PDO('mysql:host=localhost:3306; dbname=esehome; charset=utf8', 'root','');
        // $pdo = new PDO('mysql:host=172.24.0.71; dbname=PHP; charset=utf8', 'python','python');
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        $pdo->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_OBJ);
    }
    catch(Exception $e)
    {
        // En cas d'erreur, on affiche un message et on arrete tout
        die('Erreur : '.$e->getMessage());
    }

?>