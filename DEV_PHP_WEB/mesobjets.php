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
?>

<div class="mesobjets">
<div class="user_ban">
    <h1>Gardez la main sur votre maison</h1>
  </div>
  <div class="artic">
    <?php  /*     foreach($result as $value) {
          echo "Identifiant de l'objet : ".$value['id_objet'];
          echo "( ".$value['nom_groupe']." : ".$value['nom_type']." )";
        
        echo '<a href="ficheobjet.php?id_objet="'.$value['id_objet'].'>CLIQUER ICI</a>';
          echo "<br />";
      
      } */?>
      <article class="card">
          <div class="card_thumb">
            <img src="img/chambre.jpg">
          </div>

          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Gerer les elements de ma chambre</h2>
              <div class="card_subtitle">Voir les differents elements</div> 
              <div class="card_element">
                  <a href="#">Lumiere</a></br>
                  <a href="#">Alarme</a></br>
                  <a href="#">Horloge connectee</a></br>
              </div>
          </div>
          <div class="card_footer">
              <span class="icon icon--nombre"></span>3 elements
          </div>
      </article>

      <article class="card">
          <div class="card_thumb">
            <img src="img/cuisine.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Cuisine</div>
              <h2 class="card_title">Gerer les elements de ma cuisine</h2>
              <div class="card_subtitle">Voir les differents elements</div> 
              <div class="card_element">
                  <a href="#">Niveau eau</a></br>
                  <a href="#">Ventilateur</a></br>
                  <a href="#">Detecteur Incendie</a></br>
                  <a href="#">Prise connectee</a></br>
              </div>
          </div>
          <div class="card_footer">
              <span class="icon icon--nombre"></span>4 elements
          </div>
      </article>

       <article class="card">
          <div class="card_thumb">
            <img src="img/salon.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Salon</div>
              <h2 class="card_title">Gerer les elements de mon salon</h2>
              <div class="card_subtitle">Voir les differents elements</div> 
              <div class="card_element">
                  <a href="#">Eclairage intelligent</a></br>
                  <a href="#">Capteur de Luminosite</a></br>
                  <a href="#">Volet roulant</a></br>
                  <a href="#">Alarme</a></br>
                  <a href="#">Meteo Interieur</a>
              </div>
          </div>
          <div class="card_footer">
              <span class="icon icon--nombre"></span>4 elements
          </div>
      </article>

      <article class="card">
          <div class="card_thumb">
            <img src="img/exetieur.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Exterieur</div>
              <h2 class="card_title">Gerer les elements extereur</h2>
              <div class="card_subtitle">Voir les differents elements</div> 
              <div class="card_element">
                  <a href="#">Eclairage nocturne</a></br>
                  <a href="#">Meteo Exterieur</a></br>
                  <a href="#">Detecteur de chute</a></br>
              </div>
          </div>
          <div class="card_footer">
              <span class="icon icon--nombre"></span>3 elements
          </div>
      </article> 
         
  </div>
</div>

<?php require 'inc/footer.php';?>
