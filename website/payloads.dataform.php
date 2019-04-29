			<h3>Generate Downstream Payload:</h3>
			<form action = "" method="GET">	
				<? for($i = 0; $i < $_GET[nodes]; $i++): ?>
					<h5 style="font-weight:bold">Node <?=$i+1?>:</h5>
					<? for($j = 0; $j < $_GET[outputs]; $j++): ?>
						<h6>Output <?=$j?> Conditions:</h6>
						<? for($k = 0; $k < $_GET[inputs]; $k++): ?>
							<input type="text" name = "node<?=$i?>output<?=$j?>input<?=$k?>L" placeholder="input<?=$k?>L" style="width:45%"/>
							<input type="text" name = "node<?=$i?>output<?=$j?>input<?=$k?>H" placeholder="input<?=$k?>H" style="width:45%"/>
							<br/>
						<? endfor ?>
					<? endfor ?>
				<? endfor ?>
				<br/>
				<input type="hidden" name = "nodes" value="<?=$_GET['nodes']?>"		/>
				<input type="hidden" name = "outputs" value="<?=$_GET['outputs']?>"	/>
				<input type="hidden" name = "inputs" value="<?=$_GET['inputs']?>"	/>
				
				<input type="submit" class="btn btn-success mr-2" value="Generate!">
			</form>