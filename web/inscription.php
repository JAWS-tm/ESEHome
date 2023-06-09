<!-- Author: Raimbault PL  -->
 
<?php 

require 'inc/header.php';

$page = "inscription.php";

if(!empty($_POST)){
    $errors = array();
    require_once 'inc/db.php';

    if(empty($_POST['username']) || !preg_match('/^[a-zA-Z0-9_]+$/',$_POST['username'])){
        $errors['username'] = "Votre pseudo n'est pas valide (charactères autorisés : minuscules, majuscules, nombres et _)";
    }else{
        $req = $pdo->prepare('SELECT id FROM users WHERE pseudo = ?');
        $username = htmlspecialchars($_POST['username']);
        $req->execute([$username]) or exit(print_r($req->errorInfo()));;
        $user = $req->fetch();
        if($user){
            $errors['username'] = 'Ce pseudo est déjà pris !!';
        }
    }
    
    if(empty($_POST['password']) || $_POST['password'] != $_POST['password_confirm']){
        $errors['password'] = "Vous devez entrer un mot de passe valide";
    }

    if(empty($_POST['email'])){
        $errors['mail'] = "Vous devez entrer un mail valide";
    }


    if(empty($errors)){
        $req = $pdo->prepare("INSERT INTO users SET pseudo = ?, password = ?, admin = 0");
        $password = password_hash($_POST['password'], PASSWORD_BCRYPT);
        $username = htmlspecialchars($_POST['username']);
        $req->execute([$username, $password]);

        $errors = array();
		require_once 'inc/db.php';
		$req = $pdo->prepare('SELECT * FROM users WHERE pseudo = :username');
		$req->execute([':username' => $_POST['username']]);
		$user = $req->fetch();

        $_SESSION['auth'] = $user;
        $_SESSION['loggedin'] = true;
        header('Location: mesobjets.php');
        exit();

        // header("Location: connexion.php");


    }
}

?>

<!-- PARTIE HTML -->
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
    <h1>S'inscrire</h1>

    <div class="container">
        <div class="contact-form">
			<div class="left"><img class="logo" src="css/img/logo.PNG"></div>
			<div class="right">
				<h2>Inscription</h2>
                <form action="" method="POST">
                    <input type="text" name="username" placeholder="Nom d'utilisateur " class="champ" require/>
                    <input type="email" name="email" placeholder="Adresse e-mail" class="champ" require/>
                    <div class="password-eye">
                        <input type="password" name="password" placeholder="Mot De Passe" class="champ password" require/>
                        <div class="password-icon">
                            <i class="fa-solid fa-eye eye"></i>
                            <i class="fa-solid fa-eye-slash eye-slash"></i>
                        </div>
                    </div>
                    <input type="password" name="password_confirm" placeholder="Confirmez votre mot de passe" class="champ" require/>
					
                    <button type="submit" class="btn">M'inscrire</button>
                </form>
            </div>    
        </div>
    </div>


<?php require 'inc/footer.php';?>