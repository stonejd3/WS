<?php
  include 'database.connection.php';
  require 'authentication.class.php';

  // Get variables from form:
  $inputEmail =$_POST["inputEmail"];
  $inputPassword =$_POST["inputPassword"];

  $authentication = new Authentication($inputEmail,$inputPassword,$conn);
  $authentication->validate();

  if(isset($_SESSION["username"])){
    header("Location: index.php");
  } else {
    header("Location: authentication.php?message=1");
  }

