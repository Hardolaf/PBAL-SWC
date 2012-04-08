<?php
require_once('DataHandler/News/Gns/NewsGnsHandlerAbstractClass.inc');

/**
 * @author Hardolaf
 */
class NewsGnsPUTHandler extends NewsGnsHandlerAbstract {

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'news-gns';
        $this->method = 'PUT';

        $this->__constructData($response['result']);
    }
}

?>
