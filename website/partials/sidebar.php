      
      <!-- partial:partials/_sidebar.html -->
      <nav class="sidebar sidebar-offcanvas" id="sidebar">
        <ul class="nav">
          <li class="nav-item nav-profile">
            <div class="nav-link">
              <div class="user-wrapper">
                <div class="profile-image">
                  <img src="images/faces/noProfilePic.png" alt="profile image">
                </div>
                <div class="text-wrapper">
                  <p class="profile-name"><?=$name?></p>
                  <div>
                    <small class="designation text-muted">you're online</small>
                    <span class="status-indicator online"></span>
                  </div>
                </div>
              </div>
              <button class="btn btn-success btn-block">Add New Device
                <i class="mdi mdi-plus"></i>
              </button>
            </div>
          </li>
          <li class="nav-item">
            <a class="nav-link" href="index.php">
              <i class="menu-icon mdi mdi-television"></i>
              <span class="menu-title">Dashboard</span>
            </a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href="payloads.php">
              <i class="menu-icon mdi"></i>
              <span class="menu-title">Payloads</span>
            </a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href="outputconditions.php">
              <i class="menu-icon mdi"></i>
              <span class="menu-title">Output Conditions</span>
            </a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href="authentication.logout.php">
              <i class="menu-icon mdi"></i>
              <span class="menu-title">Log Out</span>
            </a>
          </li>
        </ul>
      </nav>