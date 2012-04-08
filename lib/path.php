<?php
/**
 * Prints the item nicely. Useful for debugging.
 *
 * @param mixed $object - What you wanted printed
 */
function printObject($object) {
    print '<pre>';
    print_r($object);
    print '</pre>';
}


/* WEB API Configuration */
//Provided by the Registration process with the Combine
define('WEB_API_CONFIG_NAME', '');
define('WEB_API_CONFIG_ID', '');
define('WEB_API_CONFIG_SECRET', '');

//Your time zone
define('WEB_API_CONFIG_TIMEZONE', '');

//Do not change unless you know what you are doing. Most people should be pointing to http://ws.swcombine.com/
define('WEB_API_CONFIG_SERVER', 'http://dev.swcombine.net/');

//WEB API versions currently available:
define('WEB_API_VERSION_0_1', '0.1');

//Choose your WEB API version
define('WEB_API_CONFIG_VERSION', WEB_API_VERSION_0_1);


/* Service Configurations */
//Newsbine Release Specific
define('SERVICE_CONFIG_NEWSBINE_VERSION', 0.2);
define('SERVICE_CONFIG_NEWSBINE_LIBRARY_URL', '');

//Bug Tracker
define('SERVICE_CONFIG_BUGTRACKER', '');

//Piwik Tracker
define('SERVICE_CONFIG_PIWIK', FALSE);
define('SERVICE_CONFIG_PIWIK_URL', '');
define('SERVICE_CONFIG_PIWIK_URL_SECURE', '');
define('SERVICE_CONFIG_PIWIK_SITE_ID');

//Database settings
define('SERVICE_CONFIG_DB_DATABASE', '');
define('SERVICE_CONFIG_DB_USER', '');
define('SERVICE_CONFIG_DB_PASSWORD', '');
define('SERVICE_CONFIG_DB_SERVER', '');


/* Autoloader */
//From here on out, all classes will be called by the autoloader.
require_once 'AutoloaderClass.inc';

?>
