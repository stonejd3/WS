<?php

session_start();
session_destroy();
header("Location: authentication.php?message=2");