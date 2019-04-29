<?
include "database.connection.php";
$query = "SELECT value FROM hash WHERE id='1'";
$result = $conn->query($query);
$hash = $result->fetch_assoc()["value"];
echo $hash;
