<?include 'partials/wrapper_begin.php';?>
    <div class="container-fluid page-body-wrapper full-page-wrapper auth-page">
      <div class="content-wrapper d-flex align-items-center auth auth-bg-1 theme-one">
        <div class="row w-100">
          <div class="col-lg-4 mx-auto">
            <div class="auto-form-wrapper">
              <form action="authentication.login.php" method="post">
                <? if($_GET["message"]==1): ?>
                <div class="alert alert-danger" role="alert">
                  <strong>Oh snap!</strong> Invalid Login!
                </div>
                <? elseif($_GET["message"]==2): ?>
                <div class="alert alert-info" role="alert">
                  <strong>Cool beans!</strong> You were succesfully logged out.
                </div>
                <? endif; ?>
                <div class="form-group">
                  <label class="label">Username</label>
                  <div class="input-group">
                    <input type="text" name="inputEmail" class="form-control" placeholder="Username">
                    <div class="input-group-append">
                      <span class="input-group-text">
                        <i class="mdi mdi-check-circle-outline"></i>
                      </span>
                    </div>
                  </div>
                </div>
                <div class="form-group">
                  <label class="label">Password</label>
                  <div class="input-group">
                    <input type="password" name="inputPassword" class="form-control" placeholder="*********">
                    <div class="input-group-append">
                      <span class="input-group-text">
                        <i class="mdi mdi-check-circle-outline"></i>
                      </span>
                    </div>
                  </div>
                </div>
                <div class="form-group">
                  <button class="btn btn-primary submit-btn btn-block">Login</button>
                </div>
              </form>
            </div>
            <p class="footer-text text-center">copyright © <?=date('Y')?> Jacob D. Stone. All rights reserved.</p>
          </div>
        </div>
      </div>
      <!-- content-wrapper ends -->
    </div>
    <!-- page-body-wrapper ends -->
  </div>
<? include 'partials/wrapper_end.php';?>
