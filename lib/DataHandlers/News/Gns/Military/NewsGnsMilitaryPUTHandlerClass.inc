<?php
require_once('../NewsGnsHandlerAbstractClass.inc');

/**
 * @author Hardolaf
 */
class NewsGnsMilitaryPUTHandler extends NewsGnsHandlerAbstract {

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'news-gns-military';
        $this->method = 'PUT';

        $this->__constructData($response['result']);
    }
}

?>
