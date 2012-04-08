<?php
require_once('path.php');

if(isset($_GET['page'])) {
    $page = $_GET['page'];
} else {
    $page = 'default';
}

$GUIDrawer = new GUIDraw($page);
?>
