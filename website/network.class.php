<?php

class Network {
  
  private $dbObj;
  
  private $name;
  private $desc;
  private $hashId;
  private $owner;
  
  public function __construct($name, $desc, $owner, $dbObj){
    
    // Created by program
    $this->dbObj = $dbObj;
    $this->owner = $owner;
    $this->hashId = md5(uniqid(rand()));
    
    // Created by user: format
    $this->name = $this->formatText($name);
    $this->desc = $this->formatText($desc);
    
  }
  
  public function setHashId($hashId){
    $this->hashId = $hashId;
  }
  
  public function add(){
    // Build Query:
    $query = "INSERT INTO networks
                (nickname, description, hashId, owner) 
              VALUES 
                ('$this->name', '$this->desc', '$this->hashId', '$this->owner')";
    if($this->dbObj->query($query))
      return true;
    else  
    return false;
    
  
  }
  
  private function formatText($text){
    
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
    
    return str_replace($restrictedChars,"_",$text);
    
  }
  
}