<?php require 'inc/header.php';?>

<?php

if(!empty($_POST)){
    $errors = array();
    require_once 'inc/db.php';

    if(empty($_POST['username']) || !preg_match('/^[a-zA-Z0-9_]+$/',$_POST['username'])){
        $errors['username'] = "Votre pseudo n'est pas valide";
    }else{
        $req = $pdo->prepare('SELECT id FROM users WHERE username = ?');
        $username = htmlspecialchars($_POST['username']);
        $req->execute([$username]);
        $user = $req->fetch();
        if($user){
            $errors['username'] = 'Ce pseudo est déjà pris !!';
        }
    }

    if(empty($_POST['email'])){
        $errors['email'] = "Votre email n'est pas valide";
    }else{
        $req = $pdo->prepare('SELECT id FROM users WHERE email = ?');
        $email = htmlspecialchars($_POST['email']);
        $req->execute([$email]);
        $user = $req->fetch();
        if($user){
            $errors['email'] = 'Cet email est déjà pris !!';
        }
    }

    if(empty($_POST['password']) || $_POST['password'] != $_POST['password_confirm']){
        $errors['password'] = "Vous devez entrer un mot de passe valide";
    }

    if(empty($errors)){
        $req = $pdo->prepare("INSERT INTO users SET username = ?, email = ?, mdp = ?");
        $password = password_hash($_POST['password'], PASSWORD_BCRYPT);
        $email = htmlspecialchars($_POST['email']);
        $username = htmlspecialchars($_POST['username']);
        $req->execute([$username, $email, $password]);
    }
}
?>

<!-- PARTI HTML -->
<link rel="stylesheet" href="css/register.css"/>
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
			<div class="left"></div>
			<div class="right">
                <h2>Inscription</h2>
                <form action="" method="POST">
                    <input type="text" name="username" placeholder="Pseudo" class="champ" require/>
                    <input type="email" name="email" placeholder="Email" class="champ" require/>
                    <input type="password" name="password" placeholder="Mot De Passe" class="champ" require/>
                    <input type="password" name="password_confirm" placeholder="Confirmez votre mot de passe" class="champ" require/>

                    <button type="submit" class="btn">M'inscrire</button>
                </form>
            </div>    
        </div>
    </div>


<?php require 'inc/footer.php';?>