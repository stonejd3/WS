<?php

class Database extends mysqli
{
  public function __construct($host, $user, $pass, $db){
    parent::__construct($host, $user, $pass, $db);
    if (mysqli_connect_error()) {
        die('Connect Error (' . mysqli_connect_errno() . ') '
                . mysqli_connect_error());
    }
  }

  private function getColumnsFrom($query){
    // Set up search keywords to get columns
    $ls = "SELECT";
    $rs = "FROM";
    $lpos = strpos($query,$ls) + strlen($ls);
    $rpos = strpos($query,$rs);
    $strColumns = trim(substr($query,$lpos,-(strlen($query)-$rpos)));

    if(substr_count($strColumns,',') > 0)
      return explode(', ', $strColumns);
    else
      return array($strColumns);

  }

  public function getArrayFrom($query){

    // $testQuery = "SELECT text, category, id FROM skills WHERE 1 LIMIT 2";

    // RESULT
    // array (size=3)
    //   0 =>
    //     array (size=2)
    //       0 => string 'Solid Modeling' (length=14)
    //       1 => string 'Java' (length=4)
    //   1 =>
    //     array (size=2)
    //       0 => string 'Engineering' (length=11)
    //       1 => string 'Computer Science' (length=16)
    //   2 =>
    //     array (size=2)
    //       0 => string '1' (length=1)
    //       1 => string '2' (length=1)

    // Defining array
    $resultSet = array();

    // Parse columns from $query
    $columns = $this->getColumnsFrom($query);

    // Set up empty templates
    for($i = 0; $i < count($columns); $i++)
      $resultSet[] = array();

    // Executing orignal query
    $res = $this::query($query);

    // Putting data from query results into new format
    while($row = $res->fetch_row())
      for($i = 0; $i < count($row); $i++)
        $resultSet[$i][] = $row[$i];
    // end while

    // Return value
    return $resultSet;
  } // end getArrayFrom()

} // end class

?>
