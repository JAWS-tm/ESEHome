<?php
  require 'inc/header.php';
  require 'inc/db.php';
    
	$object_id = $_GET['id'];

    // TODO : check if user is in object group

    $req = $pdo->prepare("SELECT OB.name, OB.state, OT.name type_name
        FROM object OB
        INNER JOIN object_type OT on OB.type_id = OT.id
        WHERE OB.id = ?");
    $req->execute([$object_id]);

    $object = $req->fetch(PDO::FETCH_OBJ);


    $req = $pdo->prepare("SELECT 
                param.id, 
                param.name, 
                param.value, 
                param.unit, 
                param.param_type_id type_id,
                pt.hex_value type_hex, 
                it.id interface_id                 
            FROM parameters param
            INNER JOIN param_types pt on param.param_type_id = pt.id
            INNER JOIN interface_type it on pt.interface_type_id = it.id
            WHERE param.object_id = ? 
            ORDER BY it.id ASC");
    $req->execute([$object_id]);

    $parameters = $req->fetchAll(PDO::FETCH_ASSOC);

    /**
     * return the font awesome icon corresponding to the type of param
     * @param $type_id id of the param_type
     * @return string|void
     */
    function getRelatedIcon($type_id) {
        switch ($type_id)
        {
            case 2: return "fa-arrows-to-circle"; // base station
            case 7: return "fa-temperature-high"; // temperature
            case 8: return "fa-droplet"; // humidité
            case 10: return "fa-percent"; // pression
            case 12: return "fa-wind"; // vent
            case 13: return "fa-cloud-rain"; // pluie
            default: return "";
        }
    }


    foreach ($parameters as $i=>$param)
    {
        // On ajoute les modes pour les sélecteurs
        if ($param['interface_id'] == 5) // sélecteur de mode
        {
            $req = $pdo->prepare("SELECT name, value, id
                FROM parameter_modes
                WHERE parameter_id = ?");
            $req->execute([$param['id']]);

            $parameters[$i]['modes'] = $req->fetchAll(PDO::FETCH_ASSOC);
        }
    }

    /**
     * Génère le name pour les input en fonction du type d'interface
     * @param $param_type type de l'interface du paramètre
     * @return string name
     */
    function getParamInputName($param_type) {
        switch ($param_type) {
            case 1: return "param_threshold_";
            case 3: return "param_switch_";
            case 4: return "param_slider_";
            case 5: return "param_mode_";
            case 6: return "param_color_";
            default: return "";
        }
    }

    // traitement formulaire
    if (isset($_POST['update_params']))
    {
        $changed_params = [];

        foreach ($parameters as $param)
        {
            $param_form_name = getParamInputName($param['interface_id']).$param['id'];

            if ($param['interface_id'] == 6) // input color => remove # because it's value doesn't have one
                $_POST[$param_form_name] = substr($_POST[$param_form_name], 1);

            if (isset($_POST[$param_form_name]) && strtoupper($_POST[$param_form_name]) != strtoupper($param['value']))
            {
                $changed_params[$param_form_name]["value"] = $_POST[$param_form_name];
                $changed_params[$param_form_name]["id"] = $param['id'];
            }
        }

        if (!empty($changed_params)) {
            // Insert new message for each parameter change
            foreach ($changed_params as $key=>$param ) {

                $req = $pdo->prepare("INSERT INTO message(recipient, type_message, parameter_id, data) 
                        VALUES(:recipient, (SELECT id FROM message_type where name='PARAMETER_WRITE'), :param_id, :data)");

                $req->bindParam(':recipient', $object_id);
                $req->bindParam(':param_id', $param['id']);
                $req->bindParam(':data', $param['value']);

                $req->execute();

            }
        }
    }

    $base_sql = "SELECT ot.physical_id emitter_uid, 
            ot.physical_id emitter_uid,  
            ot.name emitter_name,
            ot.id emitter_id,
            ore.physical_id recipient_uid,  
            ore.name recipient_name,
            ore.id recipient_id,
            mt.name msg_type_name,
            mt.hex_value msg_type_hex,
            p.name param_name,
            msg.data,
            msg.date,
            msg.history,
            msg.permanent
        FROM message msg
        INNER JOIN message_type mt ON mt.id = msg.type_message
        INNER JOIN object ore on msg.recipient = ore.id
        LEFT JOIN object ot on msg.transmitter = ot.id
        LEFT JOIN parameters p on msg.parameter_id = p.id";
    
    $req = $pdo->prepare($base_sql." WHERE msg.recipient = ? ORDER BY history ASC, date DESC");
    $req->execute([$object_id]);

    $received_messages = $req->fetchAll(PDO::FETCH_ASSOC);

    $req = $pdo->prepare($base_sql." WHERE msg.transmitter = ? ORDER BY history ASC, date DESC");
    $req->execute([$object_id]);

    $transmitted_messages = $req->fetchAll(PDO::FETCH_ASSOC);
?>

<link rel="stylesheet" href="css/objet.css">
<link rel="stylesheet" href="css/ficheobjet.css">
<link rel="stylesheet" href="css/colors.css">
 <div class="object-sections">
    <h2 class="section-title"><?= $object->name ?></h2>
	<form method="post" class="object-card">
		<div class="object-actions">
			<img class="object-img" src="img/<?= $object->type_name ?>.jpg">

            <div class="actions <?= empty($parameters) ? "center" : "" ?>">

                <?php
                if (empty($parameters)):
                ?>
                <p>L'objet n'a pas de paramètres</p>
                <?php
                else:
                    $double_row_container = false;
                    foreach ($parameters as $param):
                        // Si un container double est crée et que le param est pas un double on inverse l'état et on ferme l'ancienne dive
                        if ($double_row_container && $param['interface_id'] != 2) {
                            $double_row_container = false;
                            echo '</div>';
                        }
                        ?>

                <?php if(!$double_row_container): ?>
                <div class="action-card-container <?= $param['interface_id'] == 2 ? "two-actions-card" : "" ?>">
                    <?php if($param['interface_id'] != 2): ?><span class="card-title"><?= $param['name'] ?></span><?php endif; ?>
                <?php endif; ?>

                    <?php switch ($param['interface_id']):
                        case (1): ?>
					<div class="level-card action-card">
						<i class="fa-solid fa-angle-up up-down-arrow" id="upValue"></i>
						<div>
                            <input class="value value-input" id="value" type="text" min="10" max="30" value="<?= $param['value'] ?>" name="<?= getParamInputName($param['interface_id']).$param['id'] ?>">
						    <span class="value"><?= $param['unit'] ?></span>
                        </div>
						<i class="fa-solid fa-angle-down up-down-arrow" id="downValue"></i>
					</div>
                    <?php break;
                    case (2):
                        $double_row_container = !$double_row_container;?>
					<div>
						<span class="card-title"><?= $param['name'] ?></span>
						<div class="display-card action-card">
							<i class="fa-solid <?= getRelatedIcon($param['type_id']) ?>"></i>
							<span class="value"><?= $param['value']." ".($param['unit'] ?? "") ?></span>
						</div>
					</div>
                    <?php break;
                    case (3): ?>
                    <label for="checkbox" class="switch-card action-card">
                        <!-- To always get a value for checkboxes in form -->
                        <input type="hidden" name="<?= getParamInputName($param['interface_id']).$param['id'] ?>" value="0">
                        <input type="checkbox" id="checkbox" class="param_checkbox" name="<?= getParamInputName($param['interface_id']).$param['id'] ?>" value="<?= $param['value'] ?>" checked="<?= $param['value'] ?>">
                        <div class="power-button">
                            <i class="fa-solid fa-power-off"></i>
                        </div>
                    </label>
                    <?php break;
                    case (4): ?>
					<div class="brightness-card action-card">
						<div class="brightness">
							<input id="brightnessRange" type="range" min="0" max="100" step="1" value="<?= $param['value'] ?>" onchange="showVal(this.value)" name="<?= getParamInputName($param['interface_id']).$param['id'] ?>">
						</div>
						<img src="img/brightness.png" alt="">
					</div>
                    <?php break;
                    case (5):
                        if (!isset($param['modes'])) break;
                        ?>
					<div class="selector-card action-card">
                        <?php foreach ($param['modes'] as $mode): ?>
						<input type="radio" id="param_mode_<?= $param['id'].$mode['id'] ?>" name="<?= getParamInputName($param['interface_id']).$param['id'] ?>" value="<?= $mode['value'] ?>" <?= $param['value'] == $mode['value'] ? "checked" : "" ?>>
						<label class="item-selector" for="<?= getParamInputName($param['interface_id']).$param['id'].$mode['id'] ?>">
							<span><?= $mode['name'] ?></span>
						</label>
                        <?php endforeach; ?>
					</div>
                    <?php break;
                    case (6): ?>
					<div class="color-card action-card">
						<div id="color-border">
                            <input type="color" value="#<?= $param['value'] ?>" name="<?= getParamInputName($param['interface_id']).$param['id'] ?>">
						</div>
					</div>
                    <?php break;
                    endswitch; ?>

                    <?php if(!$double_row_container): ?>
                    </div>
                    <?php endif; ?>

                <?php endforeach;
                endif; ?>
			</div>
		</div>
		<div class="object-status-container">
			<p>Gestion de l'objet</p>

            <?php if ($object->state ) : ?>
                <p class="object-status connected">Objet connecté</p>
            <?php else: ?>
                <p class="object-status disconnected">Objet déconnecté</p>
            <?php endif; ?>
		</div>

        <?php if (!empty($parameters)): ?>
		<input type="submit" value="Valider les modifications" name="update_params">
        <?php endif; ?>

	</form>
	<h2 class="section-title">Messages reçus</h2>
	<div class="object-card table object-received-msg">
		<table class="table">
            <tr class="table-first-collum">
                <th>Emetteur</th>
                <th>Type</th>
                <th>Paramètre</th>
                <th>Données</th>
                <th>Permanent</th>
                <th>Date</th>
            </tr>
            <?php
            if (empty($received_messages)) :
            ?>
                <tr class="table-collums" >
                    <td colspan="6"> Aucun message reçu</td>
                </tr>
            <?php
            else:
                foreach ($received_messages as $msg):
                ?>
                <tr class="table-collums">
                    <?php
                        if (empty($msg['emitter_id'])): // msg serveur
                    ?>
                    <td>Serveur Web</td>
                    <?php
                        else:
                    ?>
                    <td><?= $msg['emitter_name'].'(0x'.$msg['emitter_uid'].')' ?></td>
                    <?php
                        endif;
                    ?>
                    <td><?= $msg['msg_type_name'].'(0x'.$msg['msg_type_hex'].')' ?></td>
                    <td><?= $msg['param_name'] ?? "Aucun" ?></td>
                    <td><?= $msg['data'] ?? "Vide" ?></td>
                    <td><?= $msg['permanent'] ? "TRUE": "FALSE"?></td>
                    <td><?= date('Y-m-d H:i:s', strtotime($msg['date'])); ?></td>
    <!--                <td>5 janvier 2023 10:52</td>-->
                </tr>
                <?php
                endforeach;
            endif;
            ?>

		</table>
	</div>
	<h2 class="section-title">Messages envoyés</h2>
	<div class="object-card table object-sent-msg">
	<table class="table">
			<tr class="table-first-collum">
				<th>Récepteur</th>
                <th>Type</th>
                <th>Paramètre</th>
				<th>Données</th>
				<th>Permanent</th>
				<th>Date</th>
			</tr>
            <?php
            if (empty($transmitted_messages)) :
            ?>
                <tr class="table-collums" >
                    <td colspan="6"> Aucun message envoyé</td>
                </tr>
            <?php
            else:
                foreach ($transmitted_messages as $msg):
                    ?>
                    <tr class="table-collums">
                        <?php
                        if (empty($msg['recipient_id'])): // msg serveur
                            ?>
                            <td>Serveur Web</td>
                        <?php
                        else:
                            ?>
                            <td><?= $msg['recipient_name'].'(0x'.$msg['recipient_uid'].')' ?></td>
                        <?php
                        endif;
                        ?>
                        <td><?= $msg['msg_type_name'].'(0x'.$msg['msg_type_hex'].')' ?></td>
                        <td><?= $msg['param_name'] ?? "Aucun" ?></td>
                        <td><?= $msg['data'] ?? "Vide" ?></td>
                        <td><?= $msg['permanent'] ? "TRUE": "FALSE"?></td>
                        <td><?= date('Y-m-d H:i:s', strtotime($msg['date'])); ?></td>
                        <!--                <td>5 janvier 2023 10:52</td>-->
                    </tr>
                <?php
                endforeach;
            endif;
            ?>
		</table>
	</div>
</div>

<script type="text/javascript" src="js/message.js"></script>
<script type="text/javascript" src="js/object.js"></script>
<?php require 'inc/footer.php';?>