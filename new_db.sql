CREATE DATABASE IF NOT EXISTS `esehome` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `esehome`;

--
-- Structure de la table `users`
--

CREATE TABLE IF NOT EXISTS `users` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `pseudo` varchar(255) NOT NULL,
    `password` varchar(255) NOT NULL,
    `creation_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `admin` bit NOT NULL DEFAULT '0',

    PRIMARY KEY (id)
);

--
-- Contenu de la table `users`
--

INSERT INTO `users` (`pseudo`, `password`, `admin`)
VALUES ('admin', '$2y$10$U/c/T274gPF1oVwnhqoYqufSdsriRpOdV4yzVupVo.GPRcJ5vubxS', 1),
    ('hugo', '$2y$10$z7TXhHGh.pdzQ.D5CS2SEOFzcYPEI2IE3Yrko71i2dt949dzUVTOe', 0),
    ('laura', '$2y$10$2MYuiR5OMg64vanZeNqfseiHhWrdkQVLpQDfJEk/I2UBsnu5Uv8Va', 0);

--
-- Structure de la table `groups`
--

CREATE TABLE IF NOT EXISTS `groups` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `name` varchar(100) NOT NULL,

    PRIMARY KEY (id)
);

--
-- Contenu de la table `groups`
--

INSERT INTO `groups` (`id`, `name`)
VALUES (1, 'Chambre'),
    (2, 'Cuisine'),
    (3, 'Salon'),
    (4, 'Exterieur');

--
-- Structure de la table `users_groups`
--

CREATE TABLE IF NOT EXISTS `users_groups` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `id_user` int NOT NULL,
    `id_group` int NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (id_user) REFERENCES users(id),
    FOREIGN KEY (id_group) REFERENCES `groups`(id)
);

--
-- Contenu de la table `users_groups`
--

INSERT INTO `users_groups` (`id_user`, `id_group`)
VALUES (3, 4),
    (3, 1),
    (2, 3),
    (1, 3);

--
-- Structure de la table `object_type`
--

CREATE TABLE IF NOT EXISTS `object_type` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `name` varchar(100) NOT NULL,

    PRIMARY KEY (id)
);

--
-- Contenu de la table `object_type`
--

INSERT INTO `object_type` (`name`)
VALUES ('OBJECT_BASE_STATION'),
       ('OBJECT_SMART_LIGHT'),
       ('OBJECT_NIGHT_LIGHT'),
       ('OBJECT_SMART_SOCKET'),
       ('OBJECT_BRIGHTNESS_SENSOR'),
       ('OBJECT_STATION_METEO_INT'),
       ('OBJECT_OUT_WEATHER_STATION'),
       ('OBJECT_ROLLER_SHUTTER'),
       ('OBJECT_ALARM'),
       ('OBJECT_FIRE_DETECTOR'),
       ('OBJECT_WINE_DEGUSTATION'),
       ('OBJECT_VENTILATOR'),
       ('OBJECT_GSM'),
       ('OBJECT_FALL_SENSOR'),
       ('OBJECT_WATER_LEVEL_DETECTOR'),
       ('OBJECT_AIR_SENSOR'),
       ('OBJECT_TRACKER_GPS'),
       ('OBJECT_RFID'),
       ('OBJECT_LCD_SLIDER'),
       ('OBJECT_VOICE_CONTROL'),
       ('OBJECT_TOUCH_SCREEN'),
       ('OBJECT_E_PAPER'),
       ('OBJECT_MATRIX_LEDS');

--
-- Structure de la table `object`
--

CREATE TABLE IF NOT EXISTS `object` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `physical_id` varchar(8) NOT NULL UNIQUE,
    `type_id` int(11) NOT NULL,
    `name` varchar(30) NOT NULL,
    `creation_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `state` bit NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (type_id) REFERENCES object_type(`id`)
);

--
-- Contenu de la table `object`
--

INSERT INTO `object` (`physical_id`, `type_id`, `name`, `state`)
VALUES ('00000000', 1, 'Station de base', 1),
       ('00000001', 2, 'Lumière', 0),
       ('00000002', 3, 'Lumière de nuit', 0),
       ('00000003', 4, 'Prise', 0),
       ('00000004', 5, 'Capteur de lumière', 0),
       ('00000005', 6, 'Station météo', 0),
       ('00000006', 7, 'Station météo exterieur', 1),
       ('00000007', 8, 'Volet roulant', 0),
       ('00000008', 9, 'Alarme', 0),
       ('00000009', 10, 'Détecteur incendie', 1),
       ('00000011', 12, 'Ventilateur', 0),
       ('00000012', 13, 'GSM', 0),
       ('00000013', 14, 'Détecteur de chute', 0),
       ('00000014', 15, 'Détecteur de niveau d\'eau', 0),
       ('00000015', 16, 'Capteur d\'air', 0),
       ('00000016', 17, 'Tracker GPS', 0);

--
-- Structure de la table `group_objects`
--

CREATE TABLE IF NOT EXISTS `group_objects` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `id_group` int(11) NOT NULL,
    `id_object` int(11) NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (id_group) REFERENCES `groups`(`id`),
    FOREIGN KEY (id_object) REFERENCES `object`(`id`)
);

--
-- Contenu de la table `group_objects`
--

INSERT INTO `group_objects` (`id_object`, `id_group`)
VALUES (1, 3),
       (2, 4),
       (3, 3),
       (4, 3),
       (5, 3),
       (6, 4),
       (7, 1),
       (8, 3),
       (9, 2),
       (10, 1),
       (11, 4),
       (12, 4),
       (13, 1),
       (14, 2),
       (15, 1);

--
-- Structure de la table `message_admin`
--

CREATE TABLE IF NOT EXISTS `message_admin` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `id_user` int(11) NOT NULL,
    `message_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `message` text NOT NULL,
    `object` varchar(100) NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (id_user) REFERENCES users(`id`)
);

--
-- Contenu de la table `message_admin`
--

INSERT INTO `message_admin` (`id_user`, `object`, `message`)
VALUES (2, 'Demande de grade', 'Bonjour, je souhaiterais devenir admin.');

--
-- Structure de la table `interface_type`
--

CREATE TABLE IF NOT EXISTS `interface_type` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `name` varchar(30) NOT NULL,

    PRIMARY KEY (id)
);

--
-- Contenu de la table `interface_type`
--

INSERT INTO `interface_type` (`name`)
VALUES ('Seuil'),
       ('Affichage'),
       ('Switch'),
       ('Luminosité'),
       ('Selecteur'),
       ('Couleur');

--
-- Structure de la table `param_types`
--

CREATE TABLE IF NOT EXISTS `param_types` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `name` varchar(100) NOT NULL,
    `hex_value` varchar(2) NOT NULL,
    `interface_type_id` int(11),

    PRIMARY KEY (id),
    FOREIGN KEY (interface_type_id) REFERENCES interface_type(id)
);

--
-- Contenu de la table `param_types`
--

INSERT INTO `param_types` (`name`, `hex_value`, `interface_type_id`)
VALUES ('PARAM_UNKNOW', '00', NULL),
       ('PARAM_MY_BASE_STATION_ID', '01', 2),
       ('PARAM_ACTUATOR_STATE', '02', 3),
       ('PARAM_SENSOR_VALUE', '03', 1),
       ('PARAM_ALARM_TRESHOLD', '04', 1),
       ('PARAM_ALARM_WAY', '05', 5),
       ('PARAM_TEMPERATURE', '06', 2),
       ('PARAM_HYGROMETRY', '07', 2),
       ('PARAM_REFRESH_PERIOD', '08', 1),
       ('PARAM_PRESSURE', '09', 2),
       ('PARAM_BRIGHTNESS', '10', 4),
       ('PARAM_WINDSPEED', '11', 2),
       ('PARAM_PLUVIOMETRY', '12', 2),
       ('PARAM_SCREEN_COLOR', '13', 6),
       ('PARAM_MODE', '14', 5),
       ('PARAM_DURATION', '19', 1),
       ('PARAM_START_TIME', '16', 1),
       ('PARAM_STOP_TIME', '17', 1),
       ('PARAM_CURRENT_TIME', '18', 2),
       ('PARAM_TRESHOLD', '19', 1),
       ('PARAM_PM1_0', '20', NULL),
       ('PARAM_PM2_5', '21', NULL),
       ('PARAM_PM10', '22', NULL),
       ('PARAM_TEXT_PART0', '64', NULL),
       ('PARAM_TEXT_PART1', '65', NULL),
       ('PARAM_TEXT_PART2', '66', NULL),
       ('PARAM_TEXT_PART3', '67', NULL),
       ('PARAM_TEXT_PART4', '68', NULL),
       ('PARAM_TEXT_PART5', '69', NULL),
       ('PARAM_TEXT_PART6', '70', NULL),
       ('PARAM_TEXT_PART7', '71', NULL);

--
-- Structure de la table `parameters`
--

CREATE TABLE IF NOT EXISTS `parameters` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `param_type_id` int(11) NOT NULL,
    `object_id` int(11) NOT NULL,
    `name` varchar(30) NOT NULL,
    `value` varchar(30) NOT NULL,
    `unit` varchar(30),

    PRIMARY KEY (id),
    FOREIGN KEY (param_type_id) REFERENCES param_types(id),
    FOREIGN KEY (object_id) REFERENCES object(id)
);

--
-- Contenu de la table `parameters`
--

INSERT INTO `parameters` (`name`, `param_type_id`, `object_id`, `value`, `unit`)
VALUES ('Température', 7, 6, '15', '°C'),
       ('Mode', 15, 9, '15', NULL);

--
-- Structure de la table `parameter_modes`
--

CREATE TABLE IF NOT EXISTS `parameter_modes` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `parameter_id` int(11) NOT NULL,
    `name` varchar(30) NOT NULL,
    `value` varchar(100),

    PRIMARY KEY (id),
    FOREIGN KEY (parameter_id) REFERENCES parameters(id)
);

--
-- Contenu de la table `parameter_modes`
--

INSERT INTO `parameter_modes` (`name`, `parameter_id`, `value`)
VALUES ('Mode veille', 2, '02'),
       ('Activé', 2, '01'),
       ('Désactivé', 2, '00');

--
-- Structure de la table `message_type`
--

CREATE TABLE IF NOT EXISTS `message_type` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `name` varchar(100) NOT NULL,
    `hex_value` varchar(2),

    PRIMARY KEY (id)
);

--
-- Contenu de la table `message_type`
--

INSERT INTO `message_type` (`name`, `hex_value`)
VALUES ('RECENT_RESET', '02'),
       ('ASK_FOR_SOFTWARE_RESET', '03'),
       ('PING', '16'),
       ('PONG', '06'),
       ('EVENT_OCCURED', '30'),
       ('PARAMETER_IS', '40'),
       ('PARAMETER_ASK', '41'),
       ('PARAMETER_WRITE', '42'),
       ('I_HAVE_NO_SERVER_ID', 'FD'),
       ('YOUR_SERVER_ID_IS', 'FE');

--
-- Structure de la table `message`
--

CREATE TABLE IF NOT EXISTS `message` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `recipient` int(11) NOT NULL,
    `transmitter` int(11) NOT NULL,
    `type_message` int(11) NOT NULL,
    `parameter_id` int(11),
    `data` varchar(20) NOT NULL, # Taille max d`une trame : 20bits
    `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `permanent` bit NOT NULL DEFAULT 0,
    `history` bit NOT NULL DEFAULT 0,

    PRIMARY KEY (id),
    FOREIGN KEY (recipient) REFERENCES object(id),
    FOREIGN KEY (transmitter) REFERENCES object(id)

);

--
-- Contenu de la table `message`
--

INSERT INTO `message` (`recipient`, `transmitter`, `type_message`, `parameter_id`, `data`)
VALUES (9, 1, 8, 2, '01'); # Message d'exemple : Message de la base station vers l'alarme (met le paramètre mode à 01 soit Activé)

