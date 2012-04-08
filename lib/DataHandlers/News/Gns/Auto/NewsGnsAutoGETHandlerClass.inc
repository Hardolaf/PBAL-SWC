<?php
/**
 * @author Joseph 'Hardolaf' Warner <hardolaf@gmail.com>
 */
class NewsGnsAutoGETHandler extends NewsGnsHandlerAbstract {

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'news-gns-auto';
        $this->method = 'GET';

        $this->__constructData($response['gns-auto']);
    }
}

?>
