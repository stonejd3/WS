          <div class = "content-header">
            <h3>Manage Output Conditions</h3>
          </div>
          <br/>
          <div class="row">
            <div class="col-md-6 d-flex align-items-stretch grid-margin">
              <div class="row flex-grow">
                <div class="col-12">
                  <div class="card">
                    <div class="card-body">
                      <h4 class="card-title">Select a node: </h4>
                      <p class="card-description">
                        Settings will be displayed for each node
                      </p>
                      <form class="forms-sample">
                        <div class="form-group">
                          <label for="selectnode">Select Node</label>
                          <select class="form-control form-control-lg" id="exampleFormControlSelect1" name="nodeSelect">
                            <? for($i = 0; $i < count($nodeInfo[0]); $i++): ?>
                            <option value="<?=$nodeInfo[1][$i]?>"><?=$nodeInfo[0][$i]?></option>
                            <? endfor; ?>
                          </select>
                        </div>
                        <button type="submit" class="btn btn-success mr-2">Submit</button>
                        <button class="btn btn-light">Cancel</button>
                      </form>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>