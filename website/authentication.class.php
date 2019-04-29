<?php

class Authentication {
  private $query;
  private $result;
  private $num_rows;
  private $user;
  private $pass;
  private $dbObj;
  
  public function __construct($user, $pass, $dbObj){
    
    $this->user = $this->formatUsername($user);
    $this->pass = md5($pass);
    $this->dbObj = $dbObj;
    
    // Passwords md5()'d before checking
    $this->query = "SELECT * FROM users WHERE active=1 AND username = '$this->user' AND password = '$this->pass'";
    
    // Database connection
    if(!$this->result = $dbObj->query($this->query))
      echo 'Error connecting to DB';
    
    $this->num_rows = $this->result->num_rows;
    
  }
 
  public function validate(){
    // start session
    if($this->result->num_rows == 1){
      session_start();
      $_SESSION['username'] = $this->user;
      $_SESSION['password']=$this->pass;
    } else {
      //do nothing
    }
	
  }
  
  private function formatUsername($user){
    
    $restrictedChars = array(
                                  '\'',
                                  '"',
                                  '\\',
                                  '/',
                                  '|',
                                  '[',
                                  ']',
                                  '{',
                                  '}',
                                  '<',
                                  '>',
                                  ':',
                                  ';',
                                  '&',
                                  '*',
                                  '(',
                                  ')'
    );
    
    return str_replace($restrictedChars,"_",$user);
    
  }
  
}
