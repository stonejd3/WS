      <?php 
        include "database.connection.php";
        if(empty($_GET)){
        
          $query = "SELECT name, nodeid FROM nodes WHERE active=1";
          $nodeInfo = $conn->getArrayFrom($query);
          $form = 'outputconditions.selectnode.php';
        
        } elseif(count($_GET)>=2){
          $node = $_GET["nodeSelect"];
          $output = $_GET["outputSelect"];
          $query = "SELECT inputname, low_threshold, high_threshold, prim_id inputid FROM thresholds WHERE outputid='$output' ORDER BY inputid";
          $thresholds = $conn->getArrayFrom($query);
          
          $query = "SELECT name FROM peripherals WHERE type='output' and prim_id=$output LIMIT 1";
          $result = $conn->getArrayFrom($query);
          $outputName = $result[0][0];
          
          $form = 'outputconditions.setthresholds.php';
          /*echo "<pre>";
          var_dump($thresholds);
          echo "<pre>";*/
          
        } elseif($_GET['nodeSelect'] != ""){
          $node = $_GET["nodeSelect"];
          $query = "SELECT name, prim_id FROM peripherals WHERE nodeid = $node AND type = 'output' AND active = '1'";
          $outputInfo = $conn->getArrayFrom($query);
          $form = 'outputconditions.selectoutput.php';
     
        }
        
      ?>
      <div class="main-panel">
        <div class="content-wrapper">
          
          <?php include $form; ?>
          
        </div>
        <!-- content-wrapper ends -->
        <? include "partials/footer.php"; ?>
      </div>
      <!-- main-panel ends -->