          <div class = "content-header">
            <h3>Manage Output Conditions</h3>
          </div>
          <br/>
          <div class="row">
            <div class="col-lg-12 d-flex align-items-stretch grid-margin">
              <div class="row">
                <div class="col-lg-12" style="">
                  <div class="card">
                    <div class="card-body">
                      <h4 class="card-title">Change Thresholds for <b><?="$outputName"?></b>: </h4>
                      <p class="card-description">
                      </p>
                        <div class="form-group">
                        <div class="table-responsive">
                          <table class = "table-responsive table-striped">
                            <? for($i=0; $i < count($thresholds[0]); $i++):?>
                            
                            <form action = "outputconditions.update.php" method="post">
                            <tr>
                              <td><input class ="form-control form-control-lg" type="text" name="threshold_min" value="<?=$thresholds[1][$i]?>"></td>
                              <td><?=$thresholds[0][$i]?></td>
                              <td><input class ="form-control form-control-lg" type="text" name="threshold_max" value="<?=$thresholds[2][$i]?>"></td>
                              <td>
                                <input type="hidden" name="url" value='<?="http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]"?>'>
                                <input type="hidden" name="id" value='<?=$thresholds[3][$i]?>'>
                                <input class ="btn btn-success btn-block" type="submit" name="submit"/></td>
                            </tr>
                            </form>
                            <? endfor; ?>
                          </table>
                        </div>
                        </div>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>