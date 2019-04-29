<?php
  // Require login first
  require 'authentication.check.php';
  
  // Build Template
  require 'partials/wrapper_begin.php';
    require 'partials/navbar.php';
    require 'partials/page_begin.php';
      require 'partials/sidebar.php';
      require 'payloads.main.php';
    require 'partials/page_end.php';
  require 'partials/wrapper_end.php';