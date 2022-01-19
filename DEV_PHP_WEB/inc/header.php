<?php require 'head.php';?>
<body>
	<div class="site-container">
		<header class="header">
			<a href="#" class="header_icon" id="header_icon"></a>
			<a class="header_logo" href="index.php"><img src="img/Logo_ESEHome.PNG"></a>
			<nav class="menu">
				<a <?php if($page=="connexion.php")?> href="inscription.php">Inscription</a>
				<a <?php if($page=="connexion.php")?> href="connexion.php">Connexion</a>
			</nav>
		</header>
		<div class="site-pusher">
			<div class="site-cache" id="site-cache"></div>


			<div class="site-content">
				<div class="container">
					
				