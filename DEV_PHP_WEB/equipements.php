<?php session_start();
    
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
?>

  <div class="mesobjets">
  <div class="user_ban">
  <h1>Tous les équipements</h1>
  </div>
  <div class="artic">
  <?php       foreach($result as $value) {
      echo "Identifiant de l'objet : ".$value['id_objet'];
      echo "( ".$value['nom_groupe']." : ".$value['nom_type']." )";
      
      echo '<a href="ficheobjet.php?id_objet="'.$value['id_objet'].'>CLIQUER ICI</a>';
      echo "<br />";
      
  } ?>
      <article class="card">
          <div class="card_thumb">
            <img src="img/chambre.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Lumiere intelligente</h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#">Lumieres tamisees et froides</a></br>
                  <a href="#">S'accorde avec un timer</a></br>
                  <a href="#">Reveillez-vous en douceur</a></br>
              </div>
          </div>
      </article>
      
      <article class="card">
          <div class="card_thumb">
            <img src="img/cuisine.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Eclairage nocturne</h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#">Capte le taux de luminosité</a></br>
                  <a href="#">Le transmet a votre systeme de lumiere intelligente</a></br>
              </div>
          </div>
      </article>
      
      <article class="card">
          <div class="card_thumb">
            <img src="img/cuisine.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Prise connectée</h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#">Capte le taux de luminosité</a></br>
                  <a href="#">Le transmet a votre systeme de lumiere intelligente</a></br>
              </div>
          </div>
      </article>

      <article class="card">
          <div class="card_thumb">
            <img src="img/cuisine.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Capteur de luminosite</h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#">Capte le taux de luminosité</a></br>
                  <a href="#">Le transmet a votre systeme de lumiere intelligente</a></br>
              </div>
          </div>
      </article>
      
      <article class="card">
          <div class="card_thumb">
            <img src="img/cuisine.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Météo Intérieur</h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#">Capte le taux de luminosité</a></br>
                  <a href="#">Le transmet a votre systeme de lumiere intelligente</a></br>
              </div>
          </div>
      </article>
      
      <article class="card">
          <div class="card_thumb">
            <img src="img/cuisine.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Météo Extérieur</h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#">Capte le taux de luminosité</a></br>
                  <a href="#">Le transmet a votre systeme de lumiere intelligente</a></br>
              </div>
          </div>
      </article>
      
      <article class="card">
          <div class="card_thumb">
            <img src="img/cuisine.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Volet roulant</h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#">Capte le taux de luminosité</a></br>
                  <a href="#">Le transmet a votre systeme de lumiere intelligente</a></br>
              </div>
          </div>
      </article>
      
      <article class="card">
          <div class="card_thumb">
            <img src="img/cuisine.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Alarme</h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#">Capte le taux de luminosité</a></br>
                  <a href="#">Le transmet a votre systeme de lumiere intelligente</a></br>
              </div>
          </div>
      </article>
      
      <article class="card">
          <div class="card_thumb">
            <img src="img/cuisine.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Détecteur incendie</h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#">Capte le taux de luminosité</a></br>
                  <a href="#">Le transmet a votre systeme de lumiere intelligente</a></br>
              </div>
          </div>
      </article>
      
      <article class="card">
          <div class="card_thumb">
            <img src="img/cuisine.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Ventilateur</h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#">Capte le taux de luminosité</a></br>
                  <a href="#">Le transmet a votre systeme de lumiere intelligente</a></br>
              </div>
          </div>
      </article>
      
      <article class="card">
          <div class="card_thumb">
            <img src="img/cuisine.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Détecteur de chute</h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#">Capte le taux de luminosité</a></br>
                  <a href="#">Le transmet a votre systeme de lumiere intelligente</a></br>
              </div>
          </div>
      </article>
      
      <article class="card">
          <div class="card_thumb">
            <img src="img/cuisine.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Détecteur niveau cuve</h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#">Capte le taux de luminosité</a></br>
                  <a href="#">Le transmet a votre systeme de lumiere intelligente</a></br>
              </div>
          </div>
      </article>
      
      <article class="card">
          <div class="card_thumb">
            <img src="img/cuisine.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Qualite de l'air</h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#">Capte le taux de luminosité</a></br>
                  <a href="#">Le transmet a votre systeme de lumiere intelligente</a></br>
              </div>
          </div>
      </article>
      
      <article class="card">
          <div class="card_thumb">
            <img src="img/cuisine.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Slider LCD</h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#">Capte le taux de luminosité</a></br>
                  <a href="#">Le transmet a votre systeme de lumiere intelligente</a></br>
              </div>
          </div>
      </article>

      <article class="card">
          <div class="card_thumb">
            <img src="img/salon.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Chambre</div>
              <h2 class="card_title">Ecran tactile</h2>
              <div class="card_subtitle">En savoir +</div> 
              <div class="card_element">
                  <a href="#">Capte le taux de luminosité</a></br>
                  <a href="#">Le transmet a votre systeme de lumiere intelligente</a></br>
              </div>
          </div>
      </article>

      <article class="card">
          <div class="card_thumb">
            <img src="img/exetieur.jpg">
          </div>
          <div class="card_body">
              <div class="card_cagtegory">Exterieur</div>
              <h2 class="card_title">Horloge connectée</h2>
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