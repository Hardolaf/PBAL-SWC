<?php
require_once('NewsGnsHandlerAbstractClass.inc');

/**
 * @author Hardolaf
 */
class NewsGnsGETHandler extends NewsGnsHandlerAbstract {

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'news-gns';
        $this->method = 'GET';

        $this->__constructData($response['gns']);
    }
}

?>
