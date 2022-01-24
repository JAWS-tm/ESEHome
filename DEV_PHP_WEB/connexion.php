<?php require 'inc/header.php';?>
<?php
if(!empty($_POST)){
    $errors = array();
    require_once 'inc/db.php';
    $req = $pdo->prepare('SELECT * FROM utilisateur WHERE Pseudo = :username');
    $req->execute(['username' => $_POST['username']]);
    $user = $req->fetch();

    if(password_verify($_POST['password'], $user->MotDePasse)){
        $_SESSION['auth'] = $user;
        $_SESSION['flash']['success'] = 'Vous êtes maintenant connecté';
        $errors['username'] = 'Vous êtes maintenant connecté';
        header('Location: index.php');
        exit();
    }else{
        $_SESSION['flash']['danger'] = 'Identifiant ou mot de passe incorrecte';
        $errors['username'] = 'Identifiant ou mot de passe incorrecte';
    }
}

$page = "connexion.php";
?>

<link rel="stylesheet" href="css/inscription.css"/>
</head>
<body>
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

    <h1>Je me connecte</h1>

    <div class="container">
        <div class="contact-form">
			<div class="left"><img class="logo" src="css/img/logo.PNG">
     </div>
			<div class="right">
                <h2>Se Connecter</h2>
                <form action="" method="POST">
                    <input type="text" name="username" placeholder="Nom d'utilisateur ou adresse e-mail" class="champ" require/>
                    <input type="password" name="password" placeholder="Mot De Passe" class="champ" require/>
                    <button type="submit" class="btn">Login</button>
                </form>
            </div>    
        </div>
    </div>

<?php require 'inc/footer.php';?>