<!-- Author: Raimbault PL - MORIN HUGO -->

<?php 
  session_start();

  if(isset($_SESSION['auth']->id)){ 
    require 'inc/header.php';
    require 'inc/db.php';

    if ($_SESSION['auth']->Admin == 1) {
      $admin = true;
      $sqlgrpuser ="SELECT * FROM groupe_utilisateur WHERE id_utilisateur =1";
      $req = $pdo->prepare($sqlgrpuser);
      $req->execute();
      $resultat = $req->fetchAll(PDO::FETCH_ASSOC);


    }
    else{

      $admin = false;
      $sqlgrpuser ="SELECT * FROM groupe_utilisateur WHERE id_utilisateur =".$_SESSION['auth']->id;
      $req = $pdo->prepare($sqlgrpuser);
      $req->execute();
      $resultat = $req->fetchAll(PDO::FETCH_ASSOC);
    }

    $sqladm = "SELECT id_objet, nom_groupe, nom_type FROM objet as OB
        INNER JOIN type as TY ON TY.id = OB.type_id
        INNER JOIN objet_groupe as OG ON OG.id_objet = OB.id
        INNER JOIN groupe as GR ON GR.id = OG.id_groupe";      


    $reqadm = $pdo->prepare($sqladm);
    $reqadm->execute();

    $result = $reqadm->fetchAll(PDO::FETCH_ASSOC);
    
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
 
   <div class="artic">

    <?php if(!$resultat && $admin == false):?>
      
        <p>Vous n'êtes associé à aucun groupe.</p>
  
    <?php endif ?>
    <?php 
    foreach ($resultat as $value) {
        if($value['id_groupe'] == '1' || $admin == true){?>
      <article class="card">
        <div class="card_thumb"><img src="img/chambre.jpg"></div>
        <div class="card_body">
          <div class="card_cagtegory">Chambre</div>
          <h2 class="card_title">Gerer les elements de ma chambre</h2>
          <div class="card_subtitle">Voir les differents elements</div> 
          <div class="card_element">
            <?php 
            foreach($result as $value){
              if($value['nom_groupe'] == 'CHAMBRE'):?>
                <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>"><?php echo $value['nom_type']."<br>"?></a>
              <?php endif;
            }?>    
          </div>
          <div class="card_footer"></div>
        </div>
      </article>
    <?php }
    } ?>

    <?php
    foreach ($resultat as $value) {
        if ($value['id_groupe'] == '2' || $admin == true){ ?>
          <article class="card">
            <div class="card_thumb"><img src="img/cuisine.jpg"></div>
            <div class="card_body">
              <div class="card_cagtegory">Cuisine</div>
              <h2 class="card_title">Gerer les elements de la cuisine</h2>
              <div class="card_subtitle">Voir les differents elements</div> 
              <div class="card_element">
                <?php 
                foreach($result as $value){
                  if($value['nom_groupe'] == 'CUISINE'):?>
                    <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>"><?php echo $value['nom_type']."<br>"?></a>
                  <?php endif;
                }?>    
              </div>
              <div class="card_footer"></div>
            </div>
          </article>
    <?php }} ?>
  
    <?php
    foreach ($resultat as $value) {
        if($value['id_groupe'] == '3' || $admin == true){?>
      <article class="card">
        <div class="card_thumb"><img src="img/salon.jpg"></div>
        <div class="card_body">
          <div class="card_cagtegory">Salon</div>
          <h2 class="card_title">Gerer les elements du salon</h2>
          <div class="card_subtitle">Voir les differents elements</div> 
          <div class="card_element">
            <?php 
            foreach($result as $value){
              if($value['nom_groupe'] == 'SALON'):?>
                <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>"><?php echo $value['nom_type']."<br>"?></a>
              <?php endif;
            }?>    
          </div>
          <div class="card_footer"></div>
        </div>
      </article>
    <?php }} ?>

    <?php 
    foreach ($resultat as $value) {
        if ($value['id_groupe'] == '4' || $admin == true){ ?>
          <article class="card">
            <div class="card_thumb"><img src="img/exetieur.jpg"></div>
            <div class="card_body">
              <div class="card_cagtegory">Exterieur</div>
              <h2 class="card_title">Gerer les elements de l'exterieur</h2>
              <div class="card_subtitle">Voir les differents elements</div> 
              <div class="card_element">
                <?php 
                foreach($result as $value){
                  if($value['nom_groupe'] == 'EXTERIEUR'):?>
                    <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>"><?php echo $value['nom_type']."<br>"?></a>
                  <?php endif;
                }?>    
              </div>
              <div class="card_footer"></div>
            </div>
          </article>
    <?php }} ?>

 
    
  </div>
</div>

<?php require 'inc/footer.php';?>
