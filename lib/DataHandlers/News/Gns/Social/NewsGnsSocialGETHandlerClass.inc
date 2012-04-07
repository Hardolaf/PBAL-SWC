<?php
require_once('path.php');
require_once('../NewsGnsHandlerAbstractClass.inc');

/**
 * @author Hardolaf
 */
class NewsGnsSocialGETHandler extends NewsGnsHandlerAbstract {

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'news-gns-social';
        $this->method = 'GET';

        $this->__constructData($response['gns-social']);
    }
}

?>
