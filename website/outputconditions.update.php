<?php
include "database.connection.php";
if(count($_POST) > 0){
  $thresholdMin = $_POST["threshold_min"];
  $thresholdMax = $_POST["threshold_max"];
  $url = $_POST["url"];
  $id = $_POST["id"];  
  
  $query = "UPDATE thresholds SET low_threshold=$thresholdMin, high_threshold=$thresholdMax WHERE prim_id=$id";
  $conn->query($query);
  
  $newhash = md5(uniqid(rand()));
  $query = "UPDATE hash SET value='$newhash' WHERE id='1'";
  $conn->query($query);
  
  header("Location: $url");
  
}