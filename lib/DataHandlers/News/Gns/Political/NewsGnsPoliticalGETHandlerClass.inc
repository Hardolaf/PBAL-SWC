<?php
/**
 * @author Joseph 'Hardolaf' Warner <hardolaf@gmail.com>
 */
class NewsGnsPoliticalGETHandler extends NewsGnsHandlerAbstract {

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'news-gns-political';
        $this->method = 'GET';

        $this->__constructData($response['gns-political']);
    }
}

?>
