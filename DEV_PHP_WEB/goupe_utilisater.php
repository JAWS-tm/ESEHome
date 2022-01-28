<?php 
   /* $servername = 'localhost';
    $username = 'root';
    $password = '';
    
    //On établit la connexion
    $conn = new mysqli($servername, $username, $password);
    
    if(isset($_POST['lumiere'])){
        $sql = "SELECT MAX(id) FROM username" ;
        $res = mysqli_query($conn,$sql);

        if($res){
            $req = $pdo->prepare("INSERT INTO groupe_utilisateur SET id_utilisateur = ?, id_groupe = ?");
            $id_groupe = htmlspecialchars($_POST['lumiere']);
            $id_utilisateur = $res;
            $req->execute([$id_utilisateur, $id_groupe]);
        }else{
            $errors['username'] = 'Une erreur est survenue !!';
        }
        
    }
    if(isset($_POST['Cuisine'])){
        $droits = $droits + $_POST['Cuisine'];
    }
    if(isset($_POST['SalleDeBain'])){
        $droits = $droits + $_POST['SalleDeBain'];
    }
    */
    include("inc/db.php");
    $lastinsertajouter = $pdo->lastInsertId();
    echo $lastinsertajouter ;

                            
    $reqinsertgrpajouter = $pdo->prepare("INSERT INTO groupe_utilisateur SET id_utilisateur = ?, id_groupe = ?, edition = ?");
    $reqinsertgrpajouter->execute(array($lastinsertajouter,0, false));


?>