<!-- Author: Raimbault PL - MORIN HUGO -->


<?php 
  session_start();

  if(isset($_SESSION['auth']->id)){ 
    require 'inc/header.php';
    require 'inc/db.php';
//si c'est un utilisateur qui est admin alors on affiche tout les groupes 
    if ($_SESSION['auth']->admin == 1) {
      $admin = true;
      $sqlgrpuser ="SELECT id, name AS nom_groupe FROM groups";
      $req = $pdo->prepare($sqlgrpuser);
      $req->execute();
      $resultat = $req->fetchAll(PDO::FETCH_ASSOC);
    }
  //sinon on recupere les groupes associés a l'id de l'utilisateur pour les afficher
    else{
      
      $admin = false;
      $sqlgrpuser ="SELECT GR.id,GR.name AS nom_groupe  FROM users AS UT
      INNER JOIN users_groups AS UG ON UG.id_user = UT.id
      INNER JOIN groups AS GR ON GR.id = UG.id_group
      WHERE UT.id =".$_SESSION['auth']->id;
      $req = $pdo->prepare($sqlgrpuser);
      $req->execute();
      $resultat = $req->fetchAll(PDO::FETCH_ASSOC);
    }

    $sqladm = "SELECT id_object, GR.name as group_name, TY.name as type_name, GR.id FROM object as OB
        INNER JOIN object_type as TY ON TY.id = OB.type_id
        INNER JOIN group_objects as OG ON OG.id_object = OB.id
        INNER JOIN groups as GR ON GR.id = OG.id_group";


    $reqadm = $pdo->prepare($sqladm);
    $reqadm->execute();

    $obj = $reqadm->fetchAll(PDO::FETCH_ASSOC);
    
    $sqlgrpuser ="SELECT * FROM groups";
    $req = $pdo->prepare($sqlgrpuser);
    $req->execute();
    $allGrp = $req->fetchAll(PDO::FETCH_ASSOC);
  }
  
  else{
    header("Location: index.php");
  }

 
?>


<!--<link rel="stylesheet" type="text/css" href="css/mesobjets.css">-->
<div class="mesobjets">
  <div class="user_ban">
    <h1>Mes Groupes</h1>
  </div>
  <?php if(empty($resultat) && !$admin ){?>
      
      <p>Vous n'êtes associé à aucun groupe.</p>

  <?php } else { ?>
    <h1 class="subtitle">Groupes disponibles :</h1>
  
   <div class="artic">
    <?php
    foreach ($resultat as $value) {
        ?>
      <article class="card">
        <div class="card_thumb"><img src=<?= "img/" . $value['nom_groupe'] . ".jpg"?> ></div>
        <div class="card_body">
          <div class="card_cagtegory"><?=$value['nom_groupe']?></div>
          <h2 class="card_title">Gerer les elements: <?=$value['nom_groupe']?></h2>
          <div class="card_subtitle">Voir les differents elements</div> 
          <div class="card_element">
            <?php 
            foreach($obj as $val_obj){
              if($val_obj['id'] == $value['id'] ):?>
                <a href="ficheobjet.php?param=<?php echo $val_obj['id_object'];?>"><?php echo $val_obj['type_name']."<br>"?></a>
              <?php endif;
            }?> 
          </div>
          <div class="card_footer"></div>
        </div>

      </article>
      
    <?php }
     ?>
  <?php }?>
          </div>
  
  <!-- pour les demandes d'acces -->
  <div>
    <h1 class="subtitle">Groupes indisponibles :</h1>
   <div class="artic">
    <?php
    foreach ($allGrp as $value) {

        if(array_search($value['id'],array_column($resultat,'id')) == ""){
          ?>
       
      <article class="card">
        <div class="card_thumb"><img src=<?= "img/" . $value['name'] . ".jpg"?> ></div>
        <div class="card_body">
          <div class="card_cagtegory"><?=$value['name']?></div>
          <h2 class="card_title"> <?=$value['name']?></h2>
          <div class="card_subtitle">Vous n'avez pas acces a ce groupe</div> 
          
          <div class="card_element">
          <input class="button" type="button" value="Je demande acces">
          </div>
          <div class="card_footer"></div>
        </div>
      </article>
    <?php }
     ?>
  <?php }?>
</div>
</div>

<?php require 'inc/footer.php';?>
