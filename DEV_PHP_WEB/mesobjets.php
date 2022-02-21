
<?php 
  session_start();

  if(isset($_SESSION['auth']->id)){ 

    require 'inc/header.php';
    require 'inc/db.php';

    if ($_SESSION['auth']->Admin == 1) {
      $admin = true;
      $resultats = (object) [
          'id_groupe' => 0
      ];
    }
    else{

      $admin = false;
      $sqlgrpuser ="SELECT id_groupe FROM utilisateur AS UT
        INNER JOIN groupe_utilisateur AS GU ON GU.id_utilisateur = UT.id
        WHERE UT.id =".$_SESSION['auth']->id;
      $req = $pdo->prepare($sqlgrpuser);
      $req->execute();

      $resultats = $req->fetch();
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
    <h1>Mes Objets</h1>
  </div>
 
 

  <div class="artic">

    <?php if($resultats->id_groupe == 1 || $admin == true):?>
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
    <?php endif ?>

    <?php if ($resultats->id_groupe == 2 || $admin == true): ?>
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
    <?php endif ?>
  
    <?php if($resultats->id_groupe == 3 || $admin == true):?>
    
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
    <?php endif ?>

    <?php if ($resultats->id_groupe == 4 || $admin == true): ?>
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
    <?php endif ?>

 
    
  </div>
</div>

<?php require 'inc/footer.php';?>
