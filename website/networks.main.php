      
      <div class="main-panel">
        <div class="content-wrapper">
          <div class = "content-header">
            <h3>Manage My Networks</h3>
          </div>
          <br/>
          <div class = "alert alert-info">
            <b>Note: </b>A network should only be created for multiple facilities or cases where one network cannot handle all connected nodes.
          </div>
          <div class="row">
            <div class="col-md-6 d-flex align-items-stretch grid-margin">
              <div class="row flex-grow">
                <div class="col-12">
                  <div class="card">
                    <div class="card-body">
                      <h4 class="card-title">My Networks:</h4>
                        <ul class="list-group">
                          <li class="list-group-item active">"nickname": ID# 8bc76d2fbb965b8d843eee068aa30135</li>
                          <li class="list-group-item">Node 1</li>
                          <li class="list-group-item">Node 2</li>
                          <li class="list-group-item">...</li>
                          <li class="list-group-item">Node "n"</li>
                        </ul>
                    </div>
                  </div>
                </div>
              </div>
            </div>
            <div class="col-md-6 d-flex align-items-stretch grid-margin">
              <div class="row flex-grow">
                <div class="col-12">
                  <div class="card">
                    <div class="card-body">
                      <h4 class="card-title">Create a Network</h4>
                      <p class="card-description">
                        This creates an unrelated network for another group of nodes.
                      </p>
                      <form class="forms-sample">
                        <div class="form-group">
                          <label for="name">Network Name</label>
                          <input type="text" class="form-control" placeholder="Enter Network Name" required>
                        </div>
                        <div class="form-group">
                          <label for="description">Network Description</label>
                          <textarea class="form-control" id="description" placeholder="Network Description" required></textarea>
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
        </div>
        <!-- content-wrapper ends -->
		<? include "partials/footer.php"; ?>
        <!-- partial -->
      </div>
      <!-- main-panel ends -->