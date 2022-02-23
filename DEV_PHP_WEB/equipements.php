<link rel="stylesheet" href="css/equipements.css"/>

<?php session_start();
    
    require 'inc/header.php';
    include("inc/db.php");
        
    $sqladm = "SELECT id_objet,nom_groupe, nom_type
        FROM utilisateur as US
        INNER JOIN groupe_utilisateur as GU ON GU.id_utilisateur = US.id
        INNER JOIN groupe as GR ON GR.id = GU.id_groupe
        INNER JOIN objet_groupe as OG ON OG.id_groupe = GR.id
        INNER JOIN objet as OB ON OB.id = OG.id_objet
        INNER JOIN type as TY ON TY.id = OB.type_id
        
        WHERE US.id =".$_SESSION['auth']->id;
    
    $sqladm = "SELECT id_objet, nom_groupe, nom_type FROM objet as OB
                    INNER JOIN type as TY ON TY.id = OB.type_id
                    INNER JOIN objet_groupe as OG ON OG.id_objet = OB.id
                    INNER JOIN groupe as GR ON GR.id = OG.id_groupe";
    
    $reqadm = $pdo->prepare($sqladm);
    $reqadm->execute();
    $result = $reqadm->fetchAll(PDO::FETCH_ASSOC);
    
    $sqlgrpuser ="SELECT id_groupe FROM utilisateur AS UT
        INNER JOIN groupe_utilisateur AS GU ON GU.id_utilisateur = UT.id
        WHERE UT.id =".$_SESSION['auth']->id;
    $req = $pdo->prepare($sqlgrpuser);
    $req->execute();
    $count = $req->rowCount();
    if ($count != 0) {
        $resultats = $req->fetchAll(PDO::FETCH_ASSOC);
    }
    else {
        $resultats = (object) [
            'id_groupe' => 0
        ];
    }
?>

  <div class="mesobjets">
  <div class="user_ban">
  <h1>Tous les equipements</h1>
  </div>
  <div class="artic">
      
      <?php foreach($result as $key => $value) { ?>
      <article class="card">
          <div class="card_thumb">
          <?php
          foreach($resultats as $key2 => $groupe) {
              if($groupe['id_groupe'] != 1){
                  if ($value['id_objet'] == 7){ ?>
                        <img  src="img/blurry.jpg">
                    <?php } 
                    if ($value['id_objet'] == 10){ ?>
                        <img src="img/blurry.jpg">
                    <?php }
                    if ($value['id_objet'] == 11){ ?>
                        <img src="img/blurry.jpg">
              		<?php }
              		if ($value['id_objet'] == 14){ ?>
                        <img src="img/blurry.jpg">
              		<?php }
              		if ($value['id_objet'] == 16){ ?>
                        <img src="img/blurry.jpg">
              		<?php }
              }
              if($groupe['id_groupe'] == 1){
                  if ($value['id_objet'] == 7){ ?>
                        <img  src="img/volet_roulant1.jpg">
                    <?php } 
                    if ($value['id_objet'] == 10){ ?>
                        <img src="img/ventilateur.jpg">
                    <?php }
                    if ($value['id_objet'] == 11){ ?>
                        <img src="img/detecteur_chute.jpg">
              		<?php }
              		if ($value['id_objet'] == 14){ ?>
                        <img src="img/slider_lcd.jpg">
              		<?php }
              		if ($value['id_objet'] == 16){ ?>
                        <img src="img/matrice_led.jpg">
              		<?php }
              }
              if($groupe['id_groupe'] != 2){
              	    if ($value['id_objet'] == 9){ ?>
                       <img src="img/blurry.jpg">
                    <?php } 
                    if ($value['id_objet'] == 15){ ?>
                        <img src="img/blurry.jpg">
                    <?php }
              } 
              if($groupe['id_groupe'] == 2){
                  if ($value['id_objet'] == 9){ ?>
                        <img  src="img/detecteur_incendie.jpg">
                    <?php } 
                    if ($value['id_objet'] == 15){ ?>
                        <img src="img/ecran_tactile.jpg">
                    <?php }
              	}
              	if($groupe['id_groupe'] != 3){
              	    if ($value['id_objet'] == 1){ ?>
                        <img src="img/blurry.jpg">
                    <?php } 
                    if ($value['id_objet'] == 3){ ?>
                        <img src="img/blurry.jpg">
                    <?php }
                    if ($value['id_objet'] == 4){ ?>
                        <img src="img/blurry.jpg">
                    <?php } 
                    if ($value['id_objet'] == 5){ ?>
                        <img src="img/blurry.jpg">
                    <?php }
                    if ($value['id_objet'] == 8){ ?>
                        <img src="img/blurry.jpg">
                    <?php }
              	} 
              	if($groupe['id_groupe'] == 3){
              	    if ($value['id_objet'] == 1){ ?>
                        <img src="img/light1.jpg">
                    <?php } 
                    if ($value['id_objet'] == 3){ ?>
                        <img  src="img/prise_connectee.jpg">
                    <?php }
                    if ($value['id_objet'] == 4){ ?>
                        <img  src="img/light3.jpg">
              		<?php }
              		if ($value['id_objet'] == 5){ ?>
                        <img  src="img/meteo1.jpg">
              		<?php }
                    if ($value['id_objet'] == 8){ ?>
                        <img  src="img/alarme.jpg">
                    <?php } 
              	} 
              	if($groupe['id_groupe'] != 4){
              	    if ($value['id_objet'] == 2){ ?>
                        <img src="img/blurry.jpg">
                    <?php } 
                    if ($value['id_objet'] == 6){ ?>
                        <img src="img/blurry.jpg">
              		<?php }
              		if ($value['id_objet'] == 12){ ?>
                        <img src="img/blurry.jpg">
              		<?php }
              		if ($value['id_objet'] == 13){ ?>
                        <img src="img/blurry.jpg">
              		<?php }
              	} 
              	if($groupe['id_groupe'] == 4){
              	    if ($value['id_objet'] == 2){ ?>
                        <img  src="img/light2.jpg">
                    <?php } 
                    if ($value['id_objet'] == 13){ ?>
                        <img  src="img/capteur_air.jpg">
              		<?php }
              		if ($value['id_objet'] == 12){ ?>
                        <img src="img/niveau_cuve.jpg">
              		<?php }
              		if ($value['id_objet'] == 6){ ?>
                        <img src="img/meteo2.jpg">
              		<?php }
              	}
            }
           ?>
          </div>
          <div class="card_body">
              <div class="card_cagtegory"><a><?php echo $value['nom_groupe'] ?></a></div>
              <h2 class="card_title"><?php echo $value['nom_type'];?></h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#"><?php echo "Idententifiant de l'objet : ".$value['id_objet'];?></a></br>
                  <?php 
                  if($groupe['id_groupe'] != 1){
                      if ($value['id_objet'] == 7){ ?>
                        <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                        <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
                    <?php } 
                    if ($value['id_objet'] == 10){ ?>
                        <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                        <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
                    <?php }
                    if ($value['id_objet'] == 11){ ?>
                        <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                        <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
              		<?php }
              		if ($value['id_objet'] == 14){ ?>
                        <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                        <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
              		<?php }
              		if ($value['id_objet'] == 16){ ?>
                        <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                        <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
              		<?php }
                  } 
                  if($groupe['id_groupe'] == 1){
                      if ($value['id_objet'] == 7){ ?>
                        <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
                    <?php } 
                    if ($value['id_objet'] == 10){ ?>
                        <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
                    <?php }
                    if ($value['id_objet'] == 11){ ?>
                        <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
              		<?php }
              		if ($value['id_objet'] == 14){ ?>
                        <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
              		<?php }
              		if ($value['id_objet'] == 16){ ?>
                        <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
              		<?php }
                  } 
                  if($groupe['id_groupe'] != 2){
                      if ($value['id_objet'] == 9){ ?>
                       <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                       <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
                    <?php } 
                    if ($value['id_objet'] == 15){ ?>
                        <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                        <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
                    <?php }
                  }
                  if($groupe['id_groupe'] == 2){
                      if ($value['id_objet'] == 9){ ?>
                       <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
                    <?php } 
                    if ($value['id_objet'] == 15){ ?>
                       <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
                    <?php }
                  }
                  if($groupe['id_groupe'] != 3){
                      if ($value['id_objet'] == 1){ ?>
                        <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                        <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
                    <?php } 
                    if ($value['id_objet'] == 3){ ?>
                        <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                        <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
                    <?php }
                    if ($value['id_objet'] == 4){ ?>
                        <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                        <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
              		<?php } 
                    if ($value['id_objet'] == 5){ ?>
                        <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                        <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
                    <?php } 
                    if ($value['id_objet'] == 8){ ?>
                        <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                        <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
                    <?php } 
                  }
                  if($groupe['id_groupe'] == 3){
                      if ($value['id_objet'] == 1){ ?>
                        <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
                    <?php } 
                    if ($value['id_objet'] == 3){ ?>
                        <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
                    <?php }
                    if ($value['id_objet'] == 4){ ?>
                        <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
              		<?php }
                    if ($value['id_objet'] == 5){ ?>
                        <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
                    <?php } 
                    if ($value['id_objet'] == 8){ ?>
                        <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
                    <?php } 
                  }
                  if($groupe['id_groupe'] != 4){
                      if ($value['id_objet'] == 2){ ?>
                        <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                        <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
                    <?php } 
                    if ($value['id_objet'] == 13){ ?>
                        <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                        <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
              		<?php }
              		if ($value['id_objet'] == 12){ ?>
                        <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                        <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
              		<?php }
              		if ($value['id_objet'] == 6){ ?>
                        <a href="#"><?php echo 'Vous n avez pas acces a cet objet!';?></a></br>
                        <form>
                          <input class="button" type="button" value="Je demande acces">
                        </form>
              		<?php }
                  }
                  if($groupe['id_groupe'] == 4){
                      if ($value['id_objet'] == 2){ ?>
                        <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
                    <?php } 
                    if ($value['id_objet'] == 13){ ?>
                        <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
              		<?php }
              		if ($value['id_objet'] == 12){ ?>
                        <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
              		<?php }
              		if ($value['id_objet'] == 6){ ?>
                        <a href="ficheobjet.php?param=<?php echo $value['id_objet'];?>">CLIQUEZ ICI</a>
              		<?php }
                  }
                  ?>
              </div>          
          </div>
      </article>
      <?php } ?>
  </div>
</div>

<?php require 'inc/footer.php';?>