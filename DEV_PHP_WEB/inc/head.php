<?php
  if(session_status() == PHP_SESSION_NONE){
    session_start();
  }
  $url= $_SERVER['REQUEST_URI'];    
 //on défini les url ou l'on a acces en tant que user non connecté    
  $authPath = ["/","/connexion.php","/index.php","/inscription.php"];
if((!isset($_SESSION["loggedin"]) || !$_SESSION["loggedin"] ) && !in_array($_SERVER['REQUEST_URI'], $authPath)){

    echo 'not logged in';
    header("Location: index.php");
    exit;
}
?>

<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>ESEhome</title>
	<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.6.1/font/bootstrap-icons.css">
	<link rel="stylesheet" type="text/css" href="css/styles.css">
	<link rel="stylesheet" type="text/css" href="css/header.css">
	<link rel="stylesheet" type="text/css" href="css/ban.css">
	<link rel="stylesheet" type="text/css" href="css/compte.css">
	<link rel="stylesheet" href="css/respadmin.css"/>
	<link rel="stylesheet" href="css/inscription.css"/>
	<link rel="stylesheet" href="css/admin.css"/>
	<link rel="stylesheet" type="text/css" href="css/mesobjets.css">
	<link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Exo:wght@300&display=swap" rel="stylesheet"> 
    <link href="https://fonts.googleapis.com/css2?family=Architects+Daughter&family=Exo:wght@300&display=swap" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css2?family=Architects+Daughter&family=Exo:wght@300&family=Reenie+Beanie&display=swap" rel="stylesheet">  
	<script src="https://kit.fontawesome.com/d944b11724.js" crossorigin="anonymous"></script>
</head>