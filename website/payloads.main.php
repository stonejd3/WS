      
      <div class="main-panel">
        <div class="content-wrapper">
		
		<?php
	
		if($_GET["nodes"] == "" && $_GET["outputs"] == "" && $_GET["inputs"] == ""){
			include "payloads.infoform.php";
		} else {
			if($_GET["node0output0input0L"] == ""){
				include "payloads.dataform.php";
			} else {
				include "payloads.generatedownstream.php";
			}
			
		}
		
		?>
		
		</div>
		<!-- content-wrapper ends -->
		<? include "partials/footer.php"; ?>
	   </div>
		<!-- main-panel ends -->