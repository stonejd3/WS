<?php
error_reporting(E_ALL);

require_once "database.class.php";
$conn = NULL;
if($_SERVER["SERVER_NAME"] == "localhost")
  $conn = new Database("localhost","root","","jacob_weatherstation");
else
  $conn = new Database("localhost","jacob_ws","weatherstation","jacob_weatherstation");
  //echo '<script>alert("Database connection not set up!");</script>';

?>
