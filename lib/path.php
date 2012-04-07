<?php
function printObject($object) {
    print '<pre>';
    print_r($object);
    print '</pre>';
}

//Provided by the Registration process with the Combine
define('WEB_API_CONFIG_NAME', '');
define('WEB_API_CONFIG_ID', '');
define('WEB_API_CONFIG_SECRET', '');

//Your time zone
define('WEB_API_CONFIG_TIMEZONE', 'America/New_York');

//Do not change unless you know what you are doing. Most people should be pointing to http://ws.swcombine.com/
define('WEB_API_CONFIG_SERVER', 'http://dev.swcombine.net/');

//WEB API versions currently available:
define('WEB_API_VERSION_0_1', '0.1');

//Choose your WEB API version
define('WEB_API_CONFIG_VERSION', WEB_API_VERSION_0_1);

//Call other necessary files
require_once 'RestRequestClass.inc';
require_once 'RequestHandlerClass.inc';
require_once 'DataHandlerClass.inc';
require_once 'GUIDrawClass.inc';

$GUIDrawer = new GUIDraw();
?>
