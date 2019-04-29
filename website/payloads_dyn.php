<?php
header('Content-Type: text/html; charset=utf-8');
include "database.connection.php";
$nodeQuery = "SELECT nodeid FROM nodes WHERE active=1";
$nodeResult = $conn->query($nodeQuery);
$numNodes  = $nodeResult->num_rows;


while($nodeRow = $nodeResult->fetch_assoc()){
  $nodeid = $nodeRow['nodeid'];
  $outputsQuery = "SELECT * FROM peripherals WHERE nodeid='$nodeid' AND active=1";
  $outputsQuery .= " AND type='output'";
  $outputsResult = $conn->query($outputsQuery);
  while($outputsRow = $outputsResult->fetch_assoc()){
    $outputid = $outputsRow["prim_id"];
    $output_hw_index = $outputsRow["hardware_index"];
    $thresholdQuery = "SELECT * FROM thresholds WHERE nodeid='$nodeid' AND outputid='$outputid' AND active=1";
    $thresholdResult = $conn->query($thresholdQuery);
    while($thresholdRow = $thresholdResult->fetch_assoc()){
      $tLow = $thresholdRow['low_threshold'];
      $tHigh = $thresholdRow['high_threshold'];
      $inputid = $thresholdRow['inputid'];
      
      $inputsQuery = "SELECT * FROM peripherals WHERE prim_id='$inputid' AND active=1";
      $input_hw_index = $conn->query($inputsQuery)->fetch_assoc()["hardware_index"];
      
      echo "$nodeid,$output_hw_index,$input_hw_index,$tLow,$tHigh\n";
    }
  }
}