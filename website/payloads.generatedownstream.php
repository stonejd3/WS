<h3>Generation Results:</h3>
<?php

	for($i = 0; $i < $_GET["nodes"]; $i++){
		
		for($j = 0; $j < $_GET["outputs"]; $j++){
		
			for($k = 0; $k < $_GET["inputs"]; $k++){
				$l = "node".$i."output".$j."input".$k."L";
				$h = "node".$i."output".$j."input".$k."H";
				$str = $i+1 . "," . $j . "," . $k . ",";
				$str .= $_GET[$l] . "," . $_GET[$h];
				echo $str."<br/>";
			}
		
		}
	
	}

?>