<!-- Author: Laura TRACZYK -->

<link rel="stylesheet" href="css/equipements.css"/>

<?php session_start();
    
    require 'inc/header.php';
    include("inc/db.php");
        
    //recuprer les objets propres  chaque groupe et leurs paramtres    
    $sqladm = "SELECT id_objet, nom_groupe, nom_type, id_groupe FROM objet as OB
                    INNER JOIN type as TY ON TY.id = OB.type_id
                    INNER JOIN objet_groupe as OG ON OG.id_objet = OB.id
                    INNER JOIN groupe as GR ON GR.id = OG.id_groupe";
    
    $reqadm = $pdo->prepare($sqladm);
    $reqadm->execute();
    $result = $reqadm->fetchAll(PDO::FETCH_ASSOC);



    $sqladmin = "SELECT admin FROM utilisateur as US WHERE US.id =".$_SESSION['auth']->id;;

    $reqadmin = $pdo->prepare($sqladmin);
    $reqadmin->execute();
    $adminresult = $reqadmin->fetchAll(PDO::FETCH_ASSOC);
    $adminresult = array_column($adminresult, 'admin');
    $isadmin = $adminresult[0];//si l'utilisateur est admin

    
    //rcuprer les groupes d'objets auxquels l'utilisateur a accs
    $sqlgrpuser ="SELECT id_groupe,pseudo,nom_groupe  FROM utilisateur AS UT
        INNER JOIN groupe_utilisateur AS GU ON GU.id_utilisateur = UT.id
        INNER JOIN groupe AS GR ON GR.id = GU.id_groupe
        WHERE UT.id =".$_SESSION['auth']->id;
    $req = $pdo->prepare($sqlgrpuser);
    $req->execute();
    $resultats = $req->fetchAll(PDO::FETCH_ASSOC);
    //print_r($resultats); //retourne bien toutes les groupes associs  l'utilisateur
    $groupe = array_column($resultats, 'id_groupe'); //met dans un tableau simple
    //$groupe = [1]; test
    //print_r($groupe); //[0]=>4, [1]=>1; // c'est bien ce qu'on veut
    $equipements = [];
    //mettre en premier les equipement disponibles
    foreach($result as $key => $equipment){
        if (array_search($equipment['id_groupe'], $groupe) != ""){
            array_push($equipements,$equipment);
        }
    }
    foreach($result as $key => $equipment){
        if (array_search($equipment['id_groupe'], $groupe) == ""){
            array_push($equipements,$equipment);
        }
    }
     
?>

  <div class="mesobjets">
  <div class="user_ban">
  <h1>Tous les equipements</h1>
  </div>
  <div class="artic">
      

      <!-- Pour chaque objet on a une carte avec image, nom de groupe, nom objet, id et lien pour cliquer ou mention pas accs -->
      <?php  
      foreach($equipements as $key => $value) {

        if(!$resultats){?>
            <p>Vous n'�tes associ� � aucun groupe.</p>
        <?php } ?>
        
        <article class="card">
            <div class="card_thumb">
            <?php
            if ($isadmin == true){
                ?>
                <img src=<?= "img/" . $value['nom_type'] . ".jpg"?>>
            <?php
            }
            else{

                if (array_search($value['id_groupe'], $groupe) != ""){
                    ?>
                    <img src=<?= "img/" . $value['nom_type'] . ".jpg"?>>
                    <?php
                }
                else{
                    ?>
                    <img  src="img/blurry.jpg">
                    <?php
                }
                
            }
            //pour chaque objet on retourne une carte en fonction de la valeur de la case $i du tableau
            
            ?>
            </div>
            <div class="card_body">
                <div class="card_cagtegory"><a><?php echo $value['nom_groupe'] ?></a></div>
                <h2 class="card_title"><?php echo $value['nom_type'];?></h2>
                <div class="card_subtitle">En savoir +</div> 
                <div class="card_element">
                    <?php
                        if ($isadmin == 1){
                            ?>
                            <a href="#"><?php echo "Idententifiant de l'objet : ".$value['id_objet'];?></a></br>
                            <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a> 
                            <?php   
                        }
                        
                        else{
                            if (array_search($value['id_groupe'], $groupe) != ""){
                                ?>
                                <a href="#"><?php echo "Idententifiant de l'objet : ".$value['id_objet'];?></a></br>
                                <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a> 
                            <?php 
                            }
                            else{
                                ?>
                                <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                                <form>
                                <input class="button" type="button" value="Je demande acces">
                                </form>
                                <?php 
                            }
                            
                        }
                    
                        ?>
                </div>          
            </div>
        </article>
      <?php } ?>
  </div>
</div>

<?php require 'inc/footer.php';?>
