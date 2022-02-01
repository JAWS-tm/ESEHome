<?php require 'head.php'; ?>
<body>
	<div class="site-container">
		<header class="header">
			<?php 
			if (isset($_SESSION['auth']) && $_SESSION['loggedin'] == true)  {?>
    		    <a href="#" class="header_icon" id="header_icon"></a>
    		    <a class="header_logo" href="mesobjets.php"><img src="img/Logo_ESEHome.PNG"></a>
			<?php if($_SESSION['auth']->Admin == 1) {?>
				<nav class="menu">
					<a class="header_active" href="equipements.php">Les equipements</a>
					<a class="header_active" href="admin.php">Le coin de l'admin</a>
					<a class="header_active" href="moncompte.php">Mon compte</a>
					<a class="header_active" href="deconnexion.php">Me deconnecter</a>
				</nav>	
			<?php } else {?>
				<nav class="menu">
					<a class="header_active" href="equipements.php">Les equipements</a>
					<a class="header_active" href="moncompte.php">Mon compte</a>
					<a class="header_active" href="deconnexion.php">Me deconnecter</a>
				</nav>
			<?php
			    }
			} else { ?>
    			<a href="#" class="header_icon" id="header_icon"></a>
    			<a class="header_logo" href="index.php"><img src="img/Logo_ESEHome.PNG"></a>
				<nav class="menu">
					<a class="header_active" href="inscription.php">Inscription</a>
					<a class="header_active" href="connexion.php">Connexion</a>
				</nav>
			<?php } ?>
			    
		</header>
		<div class="site-pusher">
			<div class="site-cache" id="site-cache"></div>
			<div class="site-content">