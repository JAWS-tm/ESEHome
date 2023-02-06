<!-- Author: Laura TRACZYK -->

<link rel="stylesheet" href="css/equipements.css"/>
<link rel="stylesheet" href="https://unpkg.com/@lottiefiles/lottie-player@latest/dist/lottie-player.js"/>


<?php session_start();
    
    require 'inc/header.php';
    include("inc/db.php");

    
    $sqladmin = "SELECT admin FROM users as US WHERE US.id =".$_SESSION['auth']->id;;

    $reqadmin = $pdo->prepare($sqladmin);
    $reqadmin->execute();
    $adminresult = $reqadmin->fetchAll(PDO::FETCH_ASSOC);
    $adminresult = array_column($adminresult, 'admin');
    $isadmin = $adminresult[0];//si l'utilisateur est admin
      
    if ($isadmin == 0){
    //recuprer les objets propres  chaque groupe et leurs paramtres    
        $sqlitemuser = "SELECT id_object, GR.id as id_group, GR.name as group_name, TY.name as type_name
        FROM users as US
        INNER JOIN users_groups as GU ON GU.id_user = US.id
        INNER JOIN groups as GR ON GR.id = GU.id_group
        INNER JOIN group_objects as OG ON OG.id_group = GR.id
        INNER JOIN object as OB ON OB.id = OG.id_object
        INNER JOIN object_type as TY ON TY.id = OB.type_id
        WHERE US.id =".$_SESSION['auth']->id;

        $requser = $pdo->prepare($sqlitemuser);
        $requser->execute();
        $resultats_item = $requser->fetchAll(PDO::FETCH_ASSOC);
    //rcuprer les groupes d'objets auxquels l'utilisateur a accs
        $sqlgrpuser = "SELECT GR.id, GR.name FROM users AS UT
        INNER JOIN users_groups AS GU ON GU.id_user = UT.id
        INNER JOIN groups AS GR ON GR.id = GU.id_group
        WHERE UT.id =".$_SESSION['auth']->id;

        $req = $pdo->prepare($sqlgrpuser);
        $req->execute();
        $resultats_groupes = $req->fetchAll(PDO::FETCH_ASSOC);
    }
    else{
        //recuprer les objets propres  chaque groupe et leurs paramtres    
        $sqlitemuser = "SELECT id_object, GR.id as id_group, GR.name as group_name, TY.name as type_name, OB.name as object_name FROM object as OB
        INNER JOIN object_type as TY ON TY.id = OB.type_id
        INNER JOIN group_objects as OG ON OG.id_object = OB.id
        INNER JOIN groups as GR ON GR.id = OG.id_group";

        $requser = $pdo->prepare($sqlitemuser);
        $requser->execute();
        $resultats_item = $requser->fetchAll(PDO::FETCH_ASSOC);

        $sqlgrpuser ="SELECT name,id FROM groups";
        $req = $pdo->prepare($sqlgrpuser);
        $req->execute();
        $resultats_groupes = $req->fetchAll(PDO::FETCH_ASSOC);
    }
    

    //fonction recherche
    if (isset($_GET["cancel"])){}
    if (isset($_GET["filter"]))
    {
        //$url = parse_url($_SERVER['REQUEST_URI']);
        //parse_str($url['query'], $q);

        $_GET["filter"] = htmlspecialchars($_GET["filter"]); //pour sécuriser le formulaire contre les intrusions html
        $filter = $_GET["filter"];
        $filter = trim($filter); //pour supprimer les espaces dans la requête de l'internaute
        $filter = strip_tags($filter); //pour supprimer les balises html dans la requête

        if (isset($filter))
        {
            $new_resultats_item = [];
            foreach($resultats_item as $key => $value_resultats_item) {
                if ($isadmin == 0){
                    if ($value_resultats_item['id'] == $filter)
                    array_push($new_resultats_item, $value_resultats_item);
                }
                else{
                    if ($value_resultats_item['id_group'] == $filter)
                    array_push($new_resultats_item, $value_resultats_item);
                }
            }
            if (!empty($new_resultats_item))
                $resultats_item = $new_resultats_item;
        }
        else
        {
            $message = "Vous devez entrer votre requete dans la barre de recherche";
        }
        
        // remove search params
        //unset($q["terme"]);
        //unset($q["s"]);
        //$new_url = $url['path'] . '?' . http_build_query($q);
        // redirect to new url
        //header("Location: ".$new_url);
    }
     
?>
<script src="https://unpkg.com/@lottiefiles/lottie-player@latest/dist/lottie-player.js"></script>
  <div class="mesobjets">
  <div class="user_ban">
  <?php 
    if (empty($resultats_item)){?>

        <h1 class="title">Vous êtes associé à aucun groupe</h1>
        <h1 class="subtitle">Veuillez vous <a class="lien_mesobject" href="mesobjets.php" >inscrire</a> à un groupe pour visualiser vos equipements ici</h1>
        <lottie-player src="https://assets6.lottiefiles.com/private_files/lf30_zncbuxbi.json" background="transparent"  speed="1" loop controls autoplay></lottie-player>
        <?php
    }
    else{?>
    <h1>
    <?php 
    if (isset($_GET["filter"])){
        if($_GET["filter"] != ""){
            echo $resultats_groupes[array_search($_GET["filter"], array_column($resultats_groupes, 'id'))]['name'];
        }
        else{
            echo "Tous les équipements";
            }
    }
    else{
        echo "Tous les équipements";
    }

    ?>
    </h1>
    <div class="box-filter">
        <?php if (count($resultats_groupes) > 1){?>
            <form action="" method = "get">
                <div class="filter-first-row">
                    <select name="filter" class="filter-select sources" placeholder="GROUPES" >
                            <option value="" selected>TOUS</option>
                            <?php
                            foreach($resultats_groupes as $key => $value_groupes) {
                            ?>
                            <option value=<?php echo $value_groupes['id']?>><?php echo $value_groupes['name']?></option>
                        <?php } ?>
                    </select>
                    <div class="submit-search">
                        <button type="submit" class="search">
                        <i class="fas fa-search icon-search"></i>

                    </div>
                </div>
                <?php if (isset($_GET["filter"])){
                    if($_GET["filter"] != ""){?>
                        <div class="filter-second-row">
                            <a href="equipements.php" class="stop-filter filter-second-row" >
                            <i class="fa-solid fa-trash icon-filter"></i> <?php echo $resultats_groupes[array_search($_GET["filter"], array_column($resultats_groupes, 'id'))]['name'];
                            ?></a>
                        </div>
                        <?php
                    }
                }?>
            </form>
        <?php
        }?>
        
    </div>
  </div>
  <div>
    
  <div class="artic">
      <!-- Pour chaque objet on a une carte avec image, nom de groupe, nom objet, id et lien pour cliquer ou mention pas accs -->
      <?php  
      foreach($resultats_item as $key => $value) {
        ?>
        <article class="card">
            <div class="card_thumb">
                <img src=<?= "img/" . $value['type_name'] . ".jpg"?>>
            </div>
            <div class="card_body">
                <div class="card_cagtegory"><a><?php echo $value['group_name'] ?></a></div>
                <h2 class="card_title"><?php echo $value['object_name'];?></h2>
                <div class="card_subtitle">En savoir +</div> 
                <div class="card_element">
                    <a href="#"><?php echo "Idententifiant de l'objet : ".$value['id_object'];?></a></br>
                    <a href="ficheobjet.php?param=<?php echo $value['id_object'];?>">CLIQUEZ ICI</a> 
                </div>          
            </div>
        </article>
      <?php } 
    }?>
  
  </div>
</div>

<?php require 'inc/footer.php';?>