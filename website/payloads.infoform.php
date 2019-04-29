			<?
			$action = "";
			if($_SERVER['REQUEST_URI'] == "/ws/index.php")
				$action = "payloads.php";
			?>
			
			<h3>Enter some information to build the payload form:</h3>
			<form action = "<?=$action?>" method="GET">	
				<input type="text" name="nodes" placeholder="number of nodes"/>
				<br/>
				<input type="text" name="outputs" placeholder="number of outputs"/>
				<br/>
				<input type="text" name="inputs" placeholder="number of inputs"/>
				<br/>
				<input type="submit" class="btn btn-success mr-2" value="Generate!">
			</form>