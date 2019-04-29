<?php
  include "database.connection.php";
  require "network.class.php";
  
  // Define some variables
  $netObj = new Network(
                        "name",
                        "desc",
                        "owner",
                        $conn
  );
  
  echo $netObj->add();