<?php session_start(); 
require 'head.php'; ?>

<body>
	<div class="site-container">
		<header class="header">
			<a href="#" class="header_icon" id="header_icon"></a>
			<a class="header_logo" href="index.php"><img src="img/Logo_ESEHome.PNG"></a>
			<?php 
			if (isset($_SESSION['loggedin']) && $_SESSION['loggedin'] == true)  {
			    if($_SESSION['Admin'] == 0) {?>
				<nav class="menu">
					<a class="header_active" href="equipement.php">Les équipements</a>
					<a class="header_active" href="admin.php">Le coin de l'admin</a>
					<a class="header_active" href="compte.php">Mon compte</a>
					<a class="header_active" href="deconnexion.php">Me d�connecter</a>
				</nav>	
			<?php } else {?>
				<nav class="menu">
					<a class="header_active" href="equipement.php">Les équipements</a>
					<a class="header_active" href="connexion.php">Mon compte</a>
					<a class="header_active" href="deconnexion.php">Me d�connecter</a>
				</nav>
			<?php
			    }
			} else { ?>
				<nav class="menu">
					<a class="header_active" href="inscription.php">Inscription</a>
					<a class="header_active" href="connexion.php">Connexion</a>
				</nav>
			<?php } ?>
		</header>
		<div class="site-pusher">
			<div class="site-cache" id="site-cache"></div>
			<div class="site-content">