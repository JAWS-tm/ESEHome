<?php require 'inc/header.php';?>

<?php

if(!empty($_POST)){
    $errors = array();
    require_once 'inc/db.php';

    if(empty($_POST['username']) || !preg_match('/^[a-zA-Z0-9_]+$/',$_POST['username'])){
        $errors['username'] = "Votre pseudo n'est pas valide";
    }else{
        $req = $pdo->prepare('SELECT id FROM utilisateur WHERE Pseudo = ?');
        $username = htmlspecialchars($_POST['username']);
        $req->execute([$username]);
        $user = $req->fetch();
        if($user){
            $errors['username'] = 'Ce pseudo est déjà pris !!';
        }
    }
    
    if(empty($_POST['password']) || $_POST['password'] != $_POST['password_confirm']){
        $errors['password'] = "Vous devez entrer un mot de passe valide";
    }

    if(empty($errors)){
        $req = $pdo->prepare("INSERT INTO utilisateur SET Pseudo = ?, MotDePasse = ?, Admin = ?");
        $password = password_hash($_POST['password'], PASSWORD_BCRYPT);
        $username = htmlspecialchars($_POST['username']);
        $admin = htmlspecialchars($_POST['admin']);
        $req->execute([$username, $password, $admin]);
    }
}
$page = "inscription.php";
?>

<!-- PARTI HTML -->
<link rel="stylesheet" href="css/inscription.css"/>
</head>
<body>
    <h1>S'inscrire</h1>
    
    <?php if(!empty($errors)): ?>
        <div class="alert">
            <p>Vous n'avez pas rempli le formulaire correctement</p>
            <ul>
                <?php foreach($errors as $error): ?>
                    <li><?= $error; ?></li>
                <?php endforeach; ?>
            </ul>
        </div>
    <?php endif; ?>

    <div class="container">
        <div class="contact-form">
			<div class="left"><img class="logo" src="css/img/logo.PNG"></div>
			<div class="right">
				<h2>Inscription</h2>
                <form action="" method="POST">
                    <input type="text" name="username" placeholder="Pseudo" class="champ" require/>
                    <input type="password" name="password" placeholder="Mot De Passe" class="champ" require/>
                    <input type="password" name="password_confirm" placeholder="Confirmez votre mot de passe" class="champ" require/>
					<?php 
					require_once 'inc/db.php';
					$req = $pdo->prepare('SELECT * FROM utilisateur WHERE Admin = 1');
					$req->execute();
					$admin = $req->fetchAll();
					if(empty($admin)):?>
                        <input name="admin"  type="hidden" value="1" require/>
                    <?php else: ?>
                     	<input name="admin"  type="hidden" value="0" require/>
					<?php endif; ?>
                    <button type="submit" class="btn">M'inscrire</button>
                </form>
            </div>    
        </div>
    </div>


<?php require 'inc/footer.php';?>