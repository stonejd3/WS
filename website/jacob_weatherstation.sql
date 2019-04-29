-- phpMyAdmin SQL Dump
-- version 4.8.3
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Apr 29, 2019 at 12:52 PM
-- Server version: 5.6.43
-- PHP Version: 7.2.7

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `jacob_weatherstation`
--
CREATE DATABASE IF NOT EXISTS `jacob_weatherstation` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `jacob_weatherstation`;

-- --------------------------------------------------------

--
-- Table structure for table `hash`
--

CREATE TABLE `hash` (
  `id` int(11) NOT NULL,
  `date_created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `value` varchar(32) NOT NULL,
  `active` tinyint(1) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `hash`
--

INSERT INTO `hash` (`id`, `date_created`, `value`, `active`) VALUES
(1, '2018-09-04 17:35:46', 'b8b7861e727e8eb29b1182fe584afc9b', 1);

-- --------------------------------------------------------

--
-- Table structure for table `networks`
--

CREATE TABLE `networks` (
  `id` int(11) NOT NULL,
  `hashId` varchar(32) NOT NULL,
  `nickname` varchar(32) NOT NULL,
  `description` varchar(255) NOT NULL,
  `owner` varchar(32) NOT NULL,
  `dateCreated` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `networks`
--

INSERT INTO `networks` (`id`, `hashId`, `nickname`, `description`, `owner`, `dateCreated`) VALUES
(1, '94a425445db5aeafb89108e536be205b', 'TestNet1', 'Powered by: Raspberry Pi 3B', 'jacob', '2018-12-01 17:58:55'),
(2, '82721da1307bc04a4fed8301e99b39eb', 'TestNet2', 'Powered by: Raspberry Pi Zero W', 'patrick', '2018-12-01 18:00:16'),
(3, '$this->hashId', '$this->name', '$this->desc', '$this->owner', '2018-12-01 20:24:16'),
(4, 'hashId', 'name', 'desc', 'owner', '2018-12-01 20:29:18'),
(5, 'hashId', 'nam', 'desc', 'owner', '2018-12-01 20:32:44'),
(6, 'bc798512c0cae54956d7dec0311e69ce', 'name', 'desc', 'owner', '2018-12-01 20:51:03');

-- --------------------------------------------------------

--
-- Table structure for table `nodes`
--

CREATE TABLE `nodes` (
  `prim_id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `nodeid` int(11) NOT NULL,
  `owner` varchar(255) NOT NULL,
  `active` tinyint(1) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `nodes`
--

INSERT INTO `nodes` (`prim_id`, `name`, `nodeid`, `owner`, `active`) VALUES
(1, 'Node 1', 1, 'jacob', 1),
(2, 'Node 2', 2, 'jacob', 1),
(3, 'Patrick Node 1', 1, 'jacob', 0),
(4, 'Patrick Node (ESP32)', 2, 'jacob', 0);

-- --------------------------------------------------------

--
-- Table structure for table `peripherals`
--

CREATE TABLE `peripherals` (
  `prim_id` int(11) NOT NULL,
  `nodeid` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `type` varchar(255) NOT NULL,
  `hardware_index` int(255) NOT NULL,
  `active` tinyint(1) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `peripherals`
--

INSERT INTO `peripherals` (`prim_id`, `nodeid`, `name`, `type`, `hardware_index`, `active`) VALUES
(1, 1, 'blue', 'output', 0, 1),
(2, 1, 'red', 'output', 1, 1),
(3, 2, 'Relay 1', 'output', 0, 1),
(4, 2, 'Relay 2', 'output', 1, 1),
(5, 1, 'potL', 'input', 0, 1),
(6, 1, 'potR', 'input', 1, 1),
(7, 2, 'temp', 'input', 0, 1),
(8, 2, 'hum', 'input', 1, 1),
(9, 2, 'PIN1', 'output', 0, 0),
(10, 2, 'PIN2', 'output', 1, 0),
(11, 2, 'PIN3', 'output', 2, 0),
(12, 2, 'PIN4', 'output', 3, 0),
(13, 2, 'temp', 'input', 0, 0),
(14, 2, 'barometric pressure', 'input', 1, 0),
(15, 2, 'humidity', 'input', 2, 0),
(16, 2, 'gas/air quality', 'input', 3, 0),
(17, 2, 'altitude', 'input', 4, 0),
(18, 2, 'UVB', 'input', 5, 0),
(19, 2, 'UVA', 'input', 6, 0),
(20, 2, 'UV Index', 'input', 7, 0),
(21, 2, 'Violet (mW)', 'input', 8, 0),
(22, 2, 'Blue (mW)', 'input', 9, 0),
(23, 2, 'Green (mW)', 'input', 10, 0),
(24, 2, 'Yellow (mW)', 'input', 11, 0),
(25, 2, 'Orange (mW)', 'input', 12, 0),
(26, 2, 'Red (mW)', 'input', 13, 0),
(27, 2, 'IR (mW)', 'input', 14, 0),
(28, 2, 'LUX', 'input', 15, 0),
(29, 2, 'full', 'input', 2, 1),
(30, 2, 'ir', 'input', 3, 1),
(31, 2, 'Relay 3', 'output', 2, 1),
(32, 2, 'Relay 4', 'output', 3, 1);

-- --------------------------------------------------------

--
-- Table structure for table `thresholds`
--

CREATE TABLE `thresholds` (
  `prim_id` int(11) NOT NULL,
  `nodeid` int(11) NOT NULL,
  `outputid` int(11) NOT NULL,
  `low_threshold` int(11) NOT NULL,
  `high_threshold` int(11) NOT NULL,
  `inputid` int(11) NOT NULL,
  `inputname` varchar(255) NOT NULL,
  `active` tinyint(1) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `thresholds`
--

INSERT INTO `thresholds` (`prim_id`, `nodeid`, `outputid`, `low_threshold`, `high_threshold`, `inputid`, `inputname`, `active`) VALUES
(1, 1, 1, 0, 1023, 5, 'potL', 1),
(2, 1, 2, 0, 1023, 5, 'potL', 1),
(3, 1, 1, 0, 1023, 6, 'potR', 1),
(4, 1, 2, 0, 1023, 6, 'potR', 1),
(5, 2, 9, 0, 65000, 13, 'temp', 0),
(6, 2, 9, 0, 65000, 14, 'barometric pressure', 0),
(7, 2, 9, 0, 65000, 15, 'humidity', 0),
(8, 2, 9, 0, 65000, 16, 'gas/air quality', 0),
(9, 2, 9, 0, 65000, 17, 'altitude', 0),
(10, 2, 9, 0, 65000, 18, 'UVB', 0),
(11, 2, 9, 0, 65000, 19, 'UVA', 0),
(12, 2, 9, 0, 65000, 20, 'UV Index', 0),
(13, 2, 9, 0, 65000, 21, 'Violet (mW)', 0),
(14, 2, 9, 0, 65000, 22, 'Blue (mW)', 0),
(15, 2, 9, 0, 65000, 23, 'Green (mW)', 0),
(16, 2, 9, 0, 65000, 24, 'Yellow (mW)', 0),
(17, 2, 9, 0, 65000, 25, 'Orange (mW)', 0),
(18, 2, 9, 0, 65000, 26, 'Red (mW)', 0),
(19, 2, 9, 0, 65000, 27, 'IR (mW)', 0),
(20, 2, 9, 0, 65000, 28, 'LUX', 0),
(21, 2, 10, 0, 65000, 13, 'temp', 0),
(22, 2, 10, 0, 65000, 14, 'barometric pressure', 0),
(23, 2, 10, 0, 65000, 15, 'humidity', 0),
(24, 2, 10, 0, 65000, 16, 'gas/air quality', 0),
(25, 2, 10, 0, 65000, 17, 'altitude', 0),
(26, 2, 10, 0, 65000, 18, 'UVB', 0),
(27, 2, 10, 0, 65000, 19, 'UVA', 0),
(28, 2, 10, 0, 65000, 20, 'UV Index', 0),
(29, 2, 10, 0, 65000, 21, 'Violet (mW)', 0),
(30, 2, 10, 0, 65000, 22, 'Blue (mW)', 0),
(31, 2, 10, 0, 65000, 23, 'Green (mW)', 0),
(32, 2, 10, 0, 65000, 24, 'Yellow (mW)', 0),
(33, 2, 10, 0, 65000, 25, 'Orange (mW)', 0),
(34, 2, 10, 0, 65000, 26, 'Red (mW)', 0),
(35, 2, 10, 0, 65000, 27, 'IR (mW)', 0),
(36, 2, 10, 0, 65000, 28, 'LUX', 0),
(37, 2, 11, 0, 65000, 13, 'temp', 0),
(38, 2, 11, 0, 65000, 14, 'barometric pressure', 0),
(39, 2, 11, 0, 65000, 15, 'humidity', 0),
(40, 2, 11, 0, 65000, 16, 'gas/air quality', 0),
(41, 2, 11, 0, 65000, 17, 'altitude', 0),
(42, 2, 11, 0, 65000, 18, 'UVB', 0),
(43, 2, 11, 0, 65000, 19, 'UVA', 0),
(44, 2, 11, 0, 65000, 20, 'UV Index', 0),
(45, 2, 11, 0, 65000, 21, 'Violet (mW)', 0),
(46, 2, 11, 0, 65000, 22, 'Blue (mW)', 0),
(47, 2, 11, 0, 65000, 23, 'Green (mW)', 0),
(48, 2, 11, 0, 65000, 24, 'Yellow (mW)', 0),
(49, 2, 11, 0, 65000, 25, 'Orange (mW)', 0),
(50, 2, 11, 0, 65000, 26, 'Red (mW)', 0),
(51, 2, 11, 0, 65000, 27, 'IR (mW)', 0),
(52, 2, 11, 0, 65000, 28, 'LUX', 0),
(53, 2, 12, 0, 65000, 13, 'temp', 0),
(54, 2, 12, 0, 65000, 14, 'barometric pressure', 0),
(55, 2, 12, 0, 65000, 15, 'humidity', 0),
(56, 2, 12, 0, 65000, 16, 'gas/air quality', 0),
(57, 2, 12, 0, 65000, 17, 'altitude', 0),
(58, 2, 12, 0, 65000, 18, 'UVB', 0),
(59, 2, 12, 0, 65000, 19, 'UVA', 0),
(60, 2, 12, 0, 65000, 20, 'UV Index', 0),
(61, 2, 12, 0, 65000, 21, 'Violet (mW)', 0),
(62, 2, 12, 0, 65000, 22, 'Blue (mW)', 0),
(63, 2, 12, 0, 65000, 23, 'Green (mW)', 0),
(64, 2, 12, 0, 65000, 24, 'Yellow (mW)', 0),
(65, 2, 12, 0, 65000, 25, 'Orange (mW)', 0),
(66, 2, 12, 0, 65000, 26, 'Red (mW)', 0),
(67, 2, 12, 0, 65000, 27, 'IR (mW)', 0),
(68, 2, 12, 0, 65000, 28, 'LUX', 0),
(73, 2, 3, 0, 2000, 29, 'full', 1),
(69, 2, 3, 0, 65535, 7, 'temp', 1),
(70, 2, 3, 0, 65535, 8, 'hum', 1),
(71, 2, 4, 0, 70, 8, 'hum', 1),
(72, 2, 4, 0, 65535, 7, 'temp', 1),
(77, 2, 31, 0, 100, 8, 'hum', 1),
(74, 2, 3, 0, 65535, 30, 'ir', 1),
(75, 2, 4, 0, 65535, 29, 'full', 1),
(76, 2, 4, 0, 65535, 30, 'ir', 1),
(78, 2, 31, 50, 78, 7, 'temp', 1),
(79, 2, 31, 0, 65535, 29, 'full', 1),
(80, 2, 31, 0, 65535, 30, 'ir', 1),
(81, 2, 32, 0, 65535, 8, 'hum', 1),
(82, 2, 32, 0, 65535, 7, 'temp', 1),
(83, 2, 32, 0, 1500, 29, 'full', 1),
(84, 2, 32, 0, 65535, 30, 'ir', 1);

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `username` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL,
  `active` tinyint(1) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `username`, `password`, `active`) VALUES
(1, 'jacob', '912ec803b2ce49e4a541068d495ab570', 1),
(2, 'patrick', '912ec803b2ce49e4a541068d495ab570', 1),
(3, 'erin', '912ec803b2ce49e4a541068d495ab570', 1);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `hash`
--
ALTER TABLE `hash`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `networks`
--
ALTER TABLE `networks`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `nodes`
--
ALTER TABLE `nodes`
  ADD PRIMARY KEY (`prim_id`);

--
-- Indexes for table `peripherals`
--
ALTER TABLE `peripherals`
  ADD PRIMARY KEY (`prim_id`);

--
-- Indexes for table `thresholds`
--
ALTER TABLE `thresholds`
  ADD PRIMARY KEY (`prim_id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `hash`
--
ALTER TABLE `hash`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `networks`
--
ALTER TABLE `networks`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT for table `nodes`
--
ALTER TABLE `nodes`
  MODIFY `prim_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `peripherals`
--
ALTER TABLE `peripherals`
  MODIFY `prim_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=33;

--
-- AUTO_INCREMENT for table `thresholds`
--
ALTER TABLE `thresholds`
  MODIFY `prim_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=85;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
