-- phpMyAdmin SQL Dump
-- version 4.4.15.10
-- https://www.phpmyadmin.net
--
-- Client :  localhost
-- Généré le :  Mar 17 Janvier 2023 à 10:24
-- Version du serveur :  5.5.68-MariaDB
-- Version de PHP :  5.4.16

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `PHP`
--

-- --------------------------------------------------------

--
-- Structure de la table `groupe`
--

CREATE TABLE IF NOT EXISTS `groupe` (
  `id` int(11) NOT NULL,
  `nom_groupe` varchar(255) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;

--
-- Contenu de la table `groupe`
--

INSERT INTO `groupe` (`id`, `nom_groupe`) VALUES
(1, 'CHAMBRE'),
(2, 'CUISINE'),
(3, 'SALON'),
(4, 'EXTERIEUR');

-- --------------------------------------------------------

--
-- Structure de la table `groupe_utilisateur`
--

CREATE TABLE IF NOT EXISTS `groupe_utilisateur` (
  `id` int(11) NOT NULL,
  `id_utilisateur` int(11) NOT NULL,
  `id_groupe` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=utf8mb4;

--
-- Contenu de la table `groupe_utilisateur`
--

INSERT INTO `groupe_utilisateur` (`id`, `id_utilisateur`, `id_groupe`) VALUES
(5, 4, 2),
(6, 3, 4),
(7, 3, 1),
(8, 2, 3),
(11, 1, 3),
(13, 65, 4),
(14, 65, 1);

-- --------------------------------------------------------

--
-- Structure de la table `historiques`
--

CREATE TABLE IF NOT EXISTS `historiques` (
  `id` int(11) NOT NULL,
  `message` varchar(255) NOT NULL,
  `type_message_id` int(11) NOT NULL,
  `date` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Structure de la table `messages`
--

CREATE TABLE IF NOT EXISTS `messages` (
  `id` int(11) NOT NULL,
  `destinataire` varchar(8) NOT NULL,
  `emetteur` varchar(8) NOT NULL,
  `parametre_id` varchar(2) NOT NULL,
  `message` varchar(255) NOT NULL,
  `date` datetime NOT NULL,
  `permanent` int(11) NOT NULL,
  `type_messages` varchar(255) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=79 DEFAULT CHARSET=utf8mb4;

--
-- Contenu de la table `messages`
--

INSERT INTO `messages` (`id`, `destinataire`, `emetteur`, `parametre_id`, `message`, `date`, `permanent`, `type_messages`) VALUES
(1, 'DDDDDD07', 'EEEEEE00', '01', '', '2022-02-23 16:01:16', 1, '30'),
(2, 'DDDDDD07', 'EEEEEE00', '01', '', '2022-02-23 16:01:16', 1, '30'),
(3, 'DDDDDD07', 'EEEEEE00', '01', '', '2022-02-23 16:01:16', 1, '30'),
(4, 'DDDDDD07', 'EEEEEE00', '01', '', '2022-02-23 16:01:16', 1, '30'),
(5, 'DDDDDD07', 'EEEEEE00', '01', '02', '2022-02-23 16:01:16', 1, '30'),
(6, 'DDDDDD10', 'EEEEEE00', '01', '02', '2022-02-23 22:19:32', 1, '30'),
(7, 'DDDDDD10', 'EEEEEE00', '01', '02', '2022-02-23 22:19:32', 1, '30'),
(8, 'DDDDDD01', 'EEEEEE00', '01', '02', '2022-02-24 01:27:20', 1, '30'),
(9, 'DDDDDD01', 'EEEEEE00', '01', '02', '2022-02-24 01:27:20', 1, '30'),
(10, 'DDDDDD01', 'EEEEEE00', '01', '02', '2022-02-24 01:27:20', 1, '30'),
(34, 'DDDDDD11', 'EEEEEE00', '01', '02', '2022-02-26 20:15:20', 1, '30'),
(35, 'DDDDDD11', 'EEEEEE00', '01', '02', '2022-02-26 20:15:20', 1, '30'),
(36, 'DDDDDD11', 'EEEEEE00', '01', '02', '2022-02-26 20:15:20', 1, '30'),
(37, 'DDDDDD10', 'EEEEEE00', '01', '02', '2022-02-26 20:57:12', 1, 'PARAMETER_WRITE'),
(38, 'DDDDDD10', 'EEEEEE00', '01', '02', '2022-02-26 20:57:12', 1, 'PARAMETER_WRITE'),
(39, 'DDDDDD10', 'EEEEEE00', '01', '02', '2022-02-26 20:57:12', 1, 'PARAMETER_WRITE'),
(40, 'DDDDDD09', 'EEEEEE00', '01', '02', '2022-02-27 08:27:59', 1, 'PARAMETER_WRITE'),
(41, 'DDDDDD09', 'EEEEEE00', '01', '02', '2022-02-27 08:27:59', 1, 'PARAMETER_WRITE'),
(42, 'DDDDDD10', 'EEEEEE00', '01', '02', '2022-02-27 11:20:43', 1, 'PARAMETER_WRITE'),
(43, 'DDDDDD10', 'EEEEEE00', '01', '02', '2022-02-27 11:20:43', 1, 'PARAMETER_WRITE'),
(44, 'DDDDDD10', 'EEEEEE00', '01', '02', '2022-02-27 11:20:43', 1, 'PARAMETER_WRITE'),
(45, 'DDDDDD10', 'EEEEEE00', '01', '02', '2022-02-27 11:20:43', 1, 'PARAMETER_WRITE'),
(46, 'DDDDDD10', 'EEEEEE00', '01', '02', '2022-02-27 11:20:43', 1, 'PARAMETER_WRITE'),
(47, 'DDDDDD03', 'EEEEEE00', '01', '02', '2023-01-11 10:20:33', 1, 'PARAMETER_WRITE'),
(48, 'DDDDDD03', 'EEEEEE00', '01', '02', '2023-01-11 10:20:33', 1, 'PARAMETER_WRITE'),
(49, 'DDDDDD03', 'EEEEEE00', '01', '02', '2023-01-11 10:20:33', 1, 'PARAMETER_WRITE'),
(50, 'DDDDDD03', 'EEEEEE00', '01', '02', '2023-01-11 10:20:33', 1, 'PARAMETER_WRITE'),
(51, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:27:16', 1, 'PARAMETER_WRITE'),
(52, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:27:16', 1, 'PARAMETER_WRITE'),
(53, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:27:16', 1, 'PARAMETER_WRITE'),
(54, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:27:16', 1, 'PARAMETER_WRITE'),
(55, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:27:16', 1, 'PARAMETER_WRITE'),
(56, 'DDDDDD01', 'EEEEEE00', '01', '02', '2023-01-11 10:30:10', 1, 'PARAMETER_WRITE'),
(57, 'DDDDDD01', 'EEEEEE00', '01', '02', '2023-01-11 10:30:10', 1, 'PARAMETER_WRITE'),
(58, 'DDDDDD01', 'EEEEEE00', '01', '02', '2023-01-11 10:30:10', 1, 'PARAMETER_WRITE'),
(59, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:35:47', 1, 'PARAMETER_WRITE'),
(60, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:35:47', 1, 'PARAMETER_WRITE'),
(61, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:35:47', 1, 'PARAMETER_WRITE'),
(62, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:35:47', 1, 'PARAMETER_WRITE'),
(63, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:35:47', 1, 'PARAMETER_WRITE'),
(64, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:35:47', 1, 'PARAMETER_WRITE'),
(65, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:35:47', 1, 'PARAMETER_WRITE'),
(66, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:35:47', 1, 'PARAMETER_WRITE'),
(67, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:35:47', 1, 'PARAMETER_WRITE'),
(68, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:35:47', 1, 'PARAMETER_WRITE'),
(69, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:35:47', 1, 'PARAMETER_WRITE'),
(70, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:35:47', 1, 'PARAMETER_WRITE'),
(71, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-11 10:35:47', 1, 'PARAMETER_WRITE'),
(72, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-16 09:40:58', 1, 'PARAMETER_WRITE'),
(73, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-16 09:40:58', 1, 'PARAMETER_WRITE'),
(74, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-16 09:40:58', 1, 'PARAMETER_WRITE'),
(75, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-16 09:40:58', 1, 'PARAMETER_WRITE'),
(76, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-16 09:40:58', 1, 'PARAMETER_WRITE'),
(77, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-16 09:40:58', 1, 'PARAMETER_WRITE'),
(78, 'DDDDDD07', 'EEEEEE00', '01', '02', '2023-01-16 09:40:58', 1, 'PARAMETER_WRITE');

-- --------------------------------------------------------

--
-- Structure de la table `messages_admin`
--

CREATE TABLE IF NOT EXISTS `messages_admin` (
  `id` int(10) NOT NULL,
  `pseudo` int(11) NOT NULL,
  `date_m` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `message` text NOT NULL,
  `objet` varchar(300) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Structure de la table `objet`
--

CREATE TABLE IF NOT EXISTS `objet` (
  `id` int(11) NOT NULL,
  `type_id` int(11) NOT NULL,
  `date_creation` date NOT NULL,
  `state` tinyint(1) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb4;

--
-- Contenu de la table `objet`
--

INSERT INTO `objet` (`id`, `type_id`, `date_creation`, `state`) VALUES
(1, 1, '2022-02-02', 1),
(2, 2, '2022-02-02', 0),
(3, 3, '2022-02-02', 0),
(4, 4, '2022-02-02', 0),
(5, 5, '2022-02-02', 0),
(6, 6, '2022-02-02', 0),
(7, 7, '2022-02-02', 1),
(8, 8, '2022-02-02', 0),
(9, 9, '2022-02-02', 0),
(10, 10, '2022-02-02', 1),
(11, 11, '2022-02-02', 0),
(12, 12, '2022-02-02', 0),
(13, 13, '2022-02-02', 0),
(14, 14, '2022-02-02', 0),
(15, 15, '2022-02-02', 0),
(16, 16, '2022-02-01', 0);

-- --------------------------------------------------------

--
-- Structure de la table `objet_groupe`
--

CREATE TABLE IF NOT EXISTS `objet_groupe` (
  `id` int(11) NOT NULL,
  `id_objet` int(11) NOT NULL,
  `id_groupe` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb4;

--
-- Contenu de la table `objet_groupe`
--

INSERT INTO `objet_groupe` (`id`, `id_objet`, `id_groupe`) VALUES
(1, 1, 3),
(2, 2, 4),
(3, 3, 3),
(4, 4, 3),
(5, 5, 3),
(6, 6, 4),
(7, 7, 1),
(8, 8, 3),
(9, 9, 2),
(10, 10, 1),
(11, 11, 1),
(12, 12, 4),
(13, 13, 4),
(14, 14, 1),
(15, 15, 2),
(16, 16, 1);

-- --------------------------------------------------------

--
-- Structure de la table `parametres`
--

CREATE TABLE IF NOT EXISTS `parametres` (
  `id` int(11) NOT NULL,
  `type_id` int(11) NOT NULL,
  `nom` varchar(255) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb4;

--
-- Contenu de la table `parametres`
--

INSERT INTO `parametres` (`id`, `type_id`, `nom`) VALUES
(1, 1, 'Eclairage intelligent'),
(2, 1, 'Eclairage nocturne'),
(3, 1, 'Prise électrique'),
(4, 1, 'Capteur de luminosité'),
(5, 1, 'Capteur station météo intérieure'),
(6, 1, 'Capteur station météo extérieure'),
(7, 1, 'Volet roulant'),
(8, 1, 'Alarme'),
(9, 1, 'Détecteur d’incendie'),
(10, 1, 'Ventilateur miniature'),
(11, 1, 'Collier détecteur de chute'),
(12, 1, 'Détecteur de niveau de cuve'),
(13, 1, 'Capteur de qualité de l’air'),
(14, 1, 'Bouton + potentiomètre + LCD (slider)'),
(15, 1, 'Ecran tactile'),
(16, 1, 'Matrice Led 16x8 (WS2812)');

-- --------------------------------------------------------

--
-- Structure de la table `type`
--

CREATE TABLE IF NOT EXISTS `type` (
  `id` int(11) NOT NULL,
  `nom_type` varchar(255) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb4;

--
-- Contenu de la table `type`
--

INSERT INTO `type` (`id`, `nom_type`) VALUES
(1, 'Eclairage_Intelligent'),
(2, 'Eclairage_Nocturne'),
(3, 'Prise_Connectée'),
(4, 'Capteur_Luminosité'),
(5, 'Météo_Intérieur'),
(6, 'Météo_Exterieur'),
(7, 'Volet_Roulant'),
(8, 'Alarme'),
(9, 'Detecteur_Incendie'),
(10, 'Ventilateur_Miniature'),
(11, 'Detecteur_de_Chute'),
(12, 'Detecteur_Niveau_Cuve'),
(13, 'Capteur_Qualité_Air'),
(14, 'Slider_LCD'),
(15, 'Ecran_Tactile'),
(16, 'Matrice_led');

-- --------------------------------------------------------

--
-- Structure de la table `type_messages`
--

CREATE TABLE IF NOT EXISTS `type_messages` (
  `id` int(2) NOT NULL,
  `nom_type_message` varchar(255) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4;

--
-- Contenu de la table `type_messages`
--

INSERT INTO `type_messages` (`id`, `nom_type_message`) VALUES
(1, 'RECENT_RESET'),
(2, 'ASK_FOR_SOFTWARE_RESET'),
(3, 'PONG'),
(4, 'PING'),
(5, 'EVENT_OCCURED'),
(6, 'PARAMETER_IS'),
(7, 'PARAMETER_ASK'),
(8, 'PARAMETER_WRITE'),
(9, 'I_HAVE_NO_SERVER_ID'),
(10, 'YOUR_SERVER_ID_IS');

-- --------------------------------------------------------

--
-- Structure de la table `utilisateur`
--

CREATE TABLE IF NOT EXISTS `utilisateur` (
  `id` int(11) NOT NULL,
  `Pseudo` varchar(255) NOT NULL,
  `MotDePasse` varchar(255) NOT NULL,
  `Admin` int(11) NOT NULL DEFAULT '0'
) ENGINE=InnoDB AUTO_INCREMENT=72 DEFAULT CHARSET=latin1;

--
-- Contenu de la table `utilisateur`
--

INSERT INTO `utilisateur` (`id`, `Pseudo`, `MotDePasse`, `Admin`) VALUES
(1, 'admin', '$2y$10$U/c/T274gPF1oVwnhqoYqufSdsriRpOdV4yzVupVo.GPRcJ5vubxS', 1),
(2, 'hugo', '$2y$10$z7TXhHGh.pdzQ.D5CS2SEOFzcYPEI2IE3Yrko71i2dt949dzUVTOe', 0),
(3, 'pilou', '$2y$10$HG860/akbRQvyAEE4CDYAen9P7LBZ/4vniXeoIFHiTaxBZCsZtO1K', 0),
(4, 'laura', '$2y$10$2MYuiR5OMg64vanZeNqfseiHhWrdkQVLpQDfJEk/I2UBsnu5Uv8Va', 0),
(64, 'momo', '$2y$10$PdMsMsolopqFJ2.pp2SmpekPL2x2GULIv6SFKgdGKkKQuccWziZaC', 0),
(65, 'QQ', '$2y$10$cqHVUNPtJ13tJTOBHgVwlOngMvJMX4MBodp.kJW4kR/E7RLpxDN1.', 1),
(66, 'lol', '$2y$10$p8moWa3o03VDmx/Pt4slG.iNfRlK5qnr58H.M8vSWllHW8FLlA4xO', 0),
(67, 'jiji', '$2y$10$Nr0FmuDyl2bOeOJ18I/GVOPDoMhNzLmOPagpfkg3Vti7v.eYxNJn2', 0),
(69, 'john', '$2y$10$Ol4HQpvDK9NnFa1OzqjIQuY1H6BoJI2/pBg3sGV6ohzoQAMdDv..6', 0),
(70, 'hey', '$2y$10$H5PazBrfwqjUGiMyUtawp.rECif7fsUS1vKDqSFlZxbYVbiFn9HTC', 0),
(71, 'hello', '$2y$10$9r.ODsdWc8Tkyaf3X.0WD.yAjyxoGYa7KMDx6efN1Rm5rusRf4D0u', 0);

-- --------------------------------------------------------

--
-- Structure de la table `valeur`
--

CREATE TABLE IF NOT EXISTS `valeur` (
  `id` int(11) NOT NULL,
  `parametre_id` int(11) NOT NULL,
  `objet_id` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb4;

--
-- Contenu de la table `valeur`
--

INSERT INTO `valeur` (`id`, `parametre_id`, `objet_id`) VALUES
(1, 1, 1),
(2, 2, 2),
(3, 3, 3),
(4, 4, 4),
(5, 5, 5),
(6, 6, 6),
(7, 7, 7),
(8, 8, 8),
(9, 9, 9),
(10, 10, 10),
(11, 11, 11),
(12, 12, 12),
(13, 13, 13),
(14, 14, 14),
(15, 15, 15),
(16, 16, 16);

--
-- Index pour les tables exportées
--

--
-- Index pour la table `groupe`
--
ALTER TABLE `groupe`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `groupe_utilisateur`
--
ALTER TABLE `groupe_utilisateur`
  ADD PRIMARY KEY (`id`),
  ADD KEY `fkey` (`id_utilisateur`),
  ADD KEY `fgkey` (`id_groupe`);

--
-- Index pour la table `historiques`
--
ALTER TABLE `historiques`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `messages`
--
ALTER TABLE `messages`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `messages_admin`
--
ALTER TABLE `messages_admin`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `objet`
--
ALTER TABLE `objet`
  ADD PRIMARY KEY (`id`),
  ADD KEY `cle_type_id_table_objet` (`type_id`);

--
-- Index pour la table `objet_groupe`
--
ALTER TABLE `objet_groupe`
  ADD PRIMARY KEY (`id`),
  ADD KEY `cle_id_objet_table_objet_groupe` (`id_objet`),
  ADD KEY `cle_id_groupe_table_objet_groupe` (`id_groupe`);

--
-- Index pour la table `parametres`
--
ALTER TABLE `parametres`
  ADD PRIMARY KEY (`id`),
  ADD KEY `cle_type_id_table_parametres` (`type_id`);

--
-- Index pour la table `type`
--
ALTER TABLE `type`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `type_messages`
--
ALTER TABLE `type_messages`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `utilisateur`
--
ALTER TABLE `utilisateur`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `valeur`
--
ALTER TABLE `valeur`
  ADD PRIMARY KEY (`id`),
  ADD KEY `cle_parametre_id_table_valeur` (`parametre_id`),
  ADD KEY `cle_objet_id_table_valeur` (`objet_id`);

--
-- AUTO_INCREMENT pour les tables exportées
--

--
-- AUTO_INCREMENT pour la table `groupe`
--
ALTER TABLE `groupe`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=5;
--
-- AUTO_INCREMENT pour la table `groupe_utilisateur`
--
ALTER TABLE `groupe_utilisateur`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=15;
--
-- AUTO_INCREMENT pour la table `historiques`
--
ALTER TABLE `historiques`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT pour la table `messages`
--
ALTER TABLE `messages`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=79;
--
-- AUTO_INCREMENT pour la table `messages_admin`
--
ALTER TABLE `messages_admin`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT pour la table `objet`
--
ALTER TABLE `objet`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=17;
--
-- AUTO_INCREMENT pour la table `objet_groupe`
--
ALTER TABLE `objet_groupe`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=17;
--
-- AUTO_INCREMENT pour la table `parametres`
--
ALTER TABLE `parametres`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=17;
--
-- AUTO_INCREMENT pour la table `type`
--
ALTER TABLE `type`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=17;
--
-- AUTO_INCREMENT pour la table `type_messages`
--
ALTER TABLE `type_messages`
  MODIFY `id` int(2) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=11;
--
-- AUTO_INCREMENT pour la table `utilisateur`
--
ALTER TABLE `utilisateur`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=72;
--
-- AUTO_INCREMENT pour la table `valeur`
--
ALTER TABLE `valeur`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=17;
--
-- Contraintes pour les tables exportées
--

--
-- Contraintes pour la table `groupe_utilisateur`
--
ALTER TABLE `groupe_utilisateur`
  ADD CONSTRAINT `fgkey` FOREIGN KEY (`id_groupe`) REFERENCES `groupe` (`id`),
  ADD CONSTRAINT `fkey` FOREIGN KEY (`id_utilisateur`) REFERENCES `utilisateur` (`id`);

--
-- Contraintes pour la table `historiques`
--
ALTER TABLE `historiques`
  ADD CONSTRAINT `type_message_id` FOREIGN KEY (`id`) REFERENCES `type_messages` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Contraintes pour la table `objet`
--
ALTER TABLE `objet`
  ADD CONSTRAINT `cle_type_id_table_objet` FOREIGN KEY (`type_id`) REFERENCES `type` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Contraintes pour la table `objet_groupe`
--
ALTER TABLE `objet_groupe`
  ADD CONSTRAINT `cle_id_groupe_table_objet_groupe` FOREIGN KEY (`id_groupe`) REFERENCES `groupe` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `cle_id_objet_table_objet_groupe` FOREIGN KEY (`id_objet`) REFERENCES `objet` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Contraintes pour la table `parametres`
--
ALTER TABLE `parametres`
  ADD CONSTRAINT `cle_type_id_table_parametre` FOREIGN KEY (`type_id`) REFERENCES `parametres` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Contraintes pour la table `valeur`
--
ALTER TABLE `valeur`
  ADD CONSTRAINT `cle_objet_id_table_valeur` FOREIGN KEY (`objet_id`) REFERENCES `objet` (`id`),
  ADD CONSTRAINT `cle_parametre_id_table_valeur` FOREIGN KEY (`parametre_id`) REFERENCES `parametres` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
