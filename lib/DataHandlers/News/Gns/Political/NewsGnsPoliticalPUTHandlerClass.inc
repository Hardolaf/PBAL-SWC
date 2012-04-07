<?php
require_once('path.php');
require_once('../NewsGnsHandlerAbstractClass.inc');

/**
 * @author Hardolaf
 */
class NewsGnsPoliticalPUTHandler extends NewsGnsHandlerAbstract {

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'news-gns-political';
        $this->method = 'PUT';

        $this->__constructData($response['result']);
    }
}

?>
