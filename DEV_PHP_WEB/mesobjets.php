
<?php 

  session_start();

  if(isset($_SESSION['auth']->id)){ 

    require 'inc/header.php';
    include("inc/db.php");

    if ($_SESSION['auth']->Admin == 0) {
      
      $sqladm = "SELECT id_objet,nom_groupe, nom_type
            FROM utilisateur as US
            INNER JOIN groupe_utilisateur as GU ON GU.id_utilisateur = US.id
            INNER JOIN groupe as GR ON GR.id = GU.id_groupe
            INNER JOIN objet_groupe as OG ON OG.id_groupe = GR.id
            INNER JOIN objet as OB ON OB.id = OG.id_objet
            INNER JOIN type as TY ON TY.id = OB.type_id

            WHERE US.id =".$_SESSION['auth']->id;

    }
    else{
      $sqladm = "SELECT id_objet, nom_groupe, nom_type FROM objet as OB
                        INNER JOIN type as TY ON TY.id = OB.type_id
                        INNER JOIN objet_groupe as OG ON OG.id_objet = OB.id
                        INNER JOIN groupe as GR ON GR.id = OG.id_groupe";
    }

    $reqadm = $pdo->prepare($sqladm);
    $reqadm->execute();

    $result = $reqadm->fetchAll(PDO::FETCH_ASSOC);

    
   

    
  }else{
    header("Location: index.php");
  }

?>


<link rel="stylesheet" type="text/css" href="css/mesobjets.css">
<div class="mesobjets">
<div class="user_ban">
    <h1>Mes Objets</h1>
  </div>
  <div class="artic">
    <?php
      $chambre = 0;
      foreach ($result as $value){
          if ($value['nom_groupe'] == 'CHAMBRE'){
              $chambre++;
          }
      }
          if($chambre >= 1){?>
              <article class="card">
                  <div class="card_thumb">
                    <img src="img/chambre.jpg">
                  </div>
                  <div class="card_body">
                      <div class="card_cagtegory">Chambre</div>
                      <h2 class="card_title">Gerer les elements de ma chambre</h2>
                      <div class="card_subtitle">Voir les diferents elements</div> 
                      <div class="card_element">
                        <?php foreach ($result as $value){
                            if ($value['nom_groupe'] == 'CHAMBRE'){
                                echo '<a href="ficheobjet.php?id_objet="'.$value['id_objet'].'>CLIQUER ICI  '.$value['id_objet'].'</a>';
                                echo "<br />"; 
                            }?> 	
                        <?php }?>
                      </div>
                  </div>
                  <div class="card_footer">
                   <?php
                   $i = 0;
                   foreach ($result as $value){
                       if ($value['nom_groupe'] == 'CHAMBRE'){
                           $i++;
                       }
                   }
                   
                   echo '<span class="icon icon--nombre"></span>'.$i.' elements';
                   ?>
                  </div>
              </article>
      <?php }?>

     <?php
          $cuisine = 0;
          foreach ($result as $value){
              if ($value['nom_groupe'] == 'CUISINE'){
                  $cuisine++;
              }
          }
          if($cuisine >= 1){?>
              <article class="card">
                  <div class="card_thumb">
                    <img src="img/cuisine.jpg">
                  </div>
                  <div class="card_body">
                      <div class="card_cagtegory">Cuisine</div>
                      <h2 class="card_title">Gerer les elements de ma cuisine</h2>
                      <div class="card_subtitle">Voir les diferents elements</div> 
                      <div class="card_element">
                        <?php foreach ($result as $value){
                            if ($value['nom_groupe'] == 'CUISINE'){
                                echo '<a href="ficheobjet.php?id_objet="'.$value['id_objet'].'>CLIQUER ICI  '.$value['id_objet'].'</a>';
                                echo "<br />"; 
                            }?> 
                        <?php }?>
                      </div>
                  </div>
                  <div class="card_footer">
                       <?php
                           $i = 0;
                           foreach ($result as $value){
                               if ($value['nom_groupe'] == 'CUISINE'){
                                   $i++;
                               }
                           }
                           
                           echo '<span class="icon icon--nombre"></span>'.$i.' elements';
                       ?>
                  </div>
              </article>
            <?php }?>
         <?php
              $salon = 0;
              foreach ($result as $value){
                  if ($value['nom_groupe'] == 'SALON'){
                      $salon++;
                  }
              }
              if($salon >= 1){?>
                   <article class="card">
                      <div class="card_thumb">
                        <img src="img/salon.jpg">
                      </div>
                      <div class="card_body">
                          <div class="card_cagtegory">Salon</div>
                          <h2 class="card_title">Gerer les elements de mon salon</h2>
                          <div class="card_subtitle">Voir les diferents elements</div> 
                          <div class="card_element">
                          	<?php foreach ($result as $value){
                                if ($value['nom_groupe'] == 'SALON'){
                                    echo '<a href="ficheobjet.php?id_objet="'.$value['id_objet'].'>CLIQUER ICI  '.$value['id_objet'].'</a>';
                                    echo "<br />"; 
                                }?> 
                            <?php }?>
                          </div>
                      </div>
                      <div class="card_footer">
                           <?php
                               $i = 0;
                               foreach ($result as $value){
                                   if ($value['nom_groupe'] == 'SALON'){
                                       $i++;
                                   }
                               }
                               
                               echo '<span class="icon icon--nombre"></span>'.$i.' elements';
                           ?>
                      </div>
                  </article>
               <?php }?>
                <?php
                  $exterieur = 0;
                  foreach ($result as $value){
                      if ($value['nom_groupe'] == 'EXTERIEUR'){
                          $exterieur++;
                      }
                  }
                  if($exterieur >= 1){?>
                      <article class="card">
                          <div class="card_thumb">
                            <img src="img/exetieur.jpg">
                          </div>
                          <div class="card_body">
                              <div class="card_cagtegory">Exterieur</div>
                              <h2 class="card_title">Gerer les elements exterieur</h2>
                              <div class="card_subtitle">Voir les diferent elements</div> 
                              <div class="card_element">
                				<?php foreach ($result as $value){
                                    if ($value['nom_groupe'] == 'EXTERIEUR'){
                                        echo '<a href="ficheobjet.php?id_objet="'.$value['id_objet'].'>CLIQUER ICI  '.$value['id_objet'].'</a>';
                                        echo "<br />"; 
                                    }?> 
                                <?php }?>
                              </div>
                          </div>
                          <div class="card_footer">
                               <?php
                                   $i = 0;
                                   foreach ($result as $value){
                                       if ($value['nom_groupe'] == 'SALON'){
                                           $i++;
                                       }
                                   }
                                   
                                   echo '<span class="icon icon--nombre"></span>'.$i.' elements';
                               ?>
                          </div>
                      </article> 
              <?php }?>

         
  </div>
</div>

<?php require 'inc/footer.php';?>
